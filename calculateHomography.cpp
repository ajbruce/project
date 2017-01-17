#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>

#include "LightfieldClass.h"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/calib3d.hpp"

using namespace std;
using namespace cv;


/**
 * Function that calculates the homography from the first image to the second.
 * 
 * TODO- when there is no match, need to return FAILURE
 **/
int LightFieldClass::calculateHomography(Mat& img_object, Mat& img_scene, Mat & H) {

	//-- Step 1: Detect the keypoints using ORB Detector, compute the descriptors
	int minHessian = 400;

	std::vector<KeyPoint> keypoints_1, keypoints_2;
	Mat descriptors_1, descriptors_2;

	// Initiate ORB detector
	Ptr<FeatureDetector> detector = ORB::create(minHessian);

	// find the keypoints and descriptors with ORB
	detector->detect(img_object, keypoints_1);
	detector->detect(img_scene, keypoints_2);

	Ptr<DescriptorExtractor> extractor = ORB::create();
	extractor->compute(img_object, keypoints_1, descriptors_1);
	extractor->compute(img_object, keypoints_1, descriptors_2);

	// Flann needs the descriptors to be of type CV_32F
	descriptors_1.convertTo(descriptors_1, CV_32F);
	descriptors_2.convertTo(descriptors_2, CV_32F);

	//-- Step 2: Matching descriptor vectors using FLANN matcher
	BFMatcher matcher(NORM_L2);
	std::vector< DMatch > matches;

	matcher.match(descriptors_1, descriptors_2, matches);

	double max_dist = 0; double min_dist = 100;
	//-- Quick calculation of max and min distances between keypoints
	for (int i = 0; i < descriptors_1.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}
	printf("-- Max dist : %f \n", max_dist);
	printf("-- Min dist : %f \n", min_dist);

	//-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist,
	//-- or a small arbitary value ( 0.02 ) in the event that min_dist is very
	//-- small)
	//-- PS.- radiusMatch can also be used here.
	std::vector< DMatch > good_matches;
	for (int i = 0; i < descriptors_1.rows; i++)
	{
		if (matches[i].distance <= max(2 * min_dist, 0.02))
		{
			good_matches.push_back(matches[i]);
		}
	}
	//-- Draw "good" matches
	Mat img_matches;
	drawMatches(img_object, keypoints_1, img_scene, keypoints_2,
		good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
		vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	//-- Show detected matches
	imshow("Good Matches", img_matches);
	for (int i = 0; i < (int)good_matches.size(); i++)
	{
		printf("-- Good Match [%d] Keypoint 1: %d  -- Keypoint 2: %d  \n", 
			   i, good_matches[i].queryIdx, good_matches[i].trainIdx);
	}


	//-- Localize the object
	vector<Point2f> obj;
	vector<Point2f> scene;

	for (size_t i = 0; i < good_matches.size(); i++) {
		//-- Get the keypoints from the good matches
		obj.push_back(keypoints_1[good_matches[i].queryIdx].pt);
		scene.push_back(keypoints_2[good_matches[i].trainIdx].pt);
	}

	H = (findHomography(obj, scene, RANSAC));


	return 0;


}



