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
int LightFieldClass::calculateHomography(Mat& img_object, Mat& img_scene, Mat& H) {

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

	std::vector<std::vector<cv::DMatch>> matches;
	cv::BFMatcher matcher;
	matcher.knnMatch(descriptors_1, descriptors_2, matches, 2);  // Find two nearest matches
																 //look whether the match is inside a defined area of the image
																 //only 25% of maximum of possible distance
	double tresholdDist = 0.25 * 
		sqrt(double(img_object.size().height*img_object.size().height +
					img_object.size().width*img_object.size().width));

	vector< DMatch > good_matches;
	good_matches.reserve(matches.size());
	for (size_t i = 0; i < matches.size(); ++i)
	{
		for (int j = 0; j < matches[i].size(); j++)
		{
			Point2f from = keypoints_1[matches[i][j].queryIdx].pt;
			Point2f to = keypoints_2[matches[i][j].trainIdx].pt;

			//calculate local distance for each possible match
			double dist = sqrt((from.x - to.x) * (from.x - to.x) + (from.y - to.y) * (from.y - to.y));

			//save as best match if local distance is in specified area and on same height
			if (dist < tresholdDist && abs(from.y - to.y)<5)
			{
				good_matches.push_back(matches[i][j]);
				j = matches[i].size();
			}
		}
	}
	
	Mat img_matches;
	drawMatches(img_object, keypoints_1, img_scene, keypoints_2,
		good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
		vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	/*for (int i = 0; i < (int)good_matches.size(); i++)
	{
		printf("-- Good Match [%d] Keypoint 1: %d  -- Keypoint 2: %d  \n", i, good_matches[i].queryIdx, good_matches[i].trainIdx);
	}

	cout << "height: "<< img_matches.size().height << endl;
	cout << "width: " << img_matches.size().width << endl;

	//-- Show detected matches
	imshow("Good Matches", img_matches);
	waitKey(0);

	*/

	//-- Localize the object
	vector<Point2f> obj;
	vector<Point2f> scene;

	for (size_t i = 0; i < good_matches.size(); i++) {
		//-- Get the keypoints from the good matches
		obj.push_back(keypoints_1[good_matches[i].queryIdx].pt);
		scene.push_back(keypoints_2[good_matches[i].trainIdx].pt);
	}
	H = (findHomography(obj, scene, RANSAC));
	cout << H << endl;
	
	return 0;

}



