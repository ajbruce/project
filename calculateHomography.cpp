#include <vector>
#include <string>
#include <iostream>
#include "LightfieldClass.h"


#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/xfeatures2d.hpp"

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;


/**
 * Function that calculates the homography from the first image to the second.
 * 
 * TODO- when there is no match, need to return FAILURE
 **/
int LightFieldClass::calculateHomography(Mat* img_object, Mat* img_scene, Mat & H) {

	//-- Step 1: Detect the keypoints and extract descriptors using SURF
	int minHessian = 400;
	Ptr<SURF> detector = SURF::create( minHessian );
	vector<KeyPoint> keypoints_object, keypoints_scene;
	Mat descriptors_object, descriptors_scene;
	detector->detectAndCompute( *img_object, Mat(), keypoints_object, descriptors_object );
	detector->detectAndCompute( *img_scene, Mat(), keypoints_scene, descriptors_scene );

	//-- Step 2: Matching descriptor vectors using FLANN matcher
	FlannBasedMatcher matcher;
	vector< DMatch > matches;
	matcher.match( descriptors_object, descriptors_scene, matches );
	double max_dist = 0; 
	double min_dist = 100; 

	//-- Quick calculation of max and min distances between keypoints
	for( int i = 0; i < descriptors_object.rows; i++ ){ 
		double dist = matches[i].distance;
		if( dist < min_dist ) min_dist = dist;
		if( dist > max_dist ) max_dist = dist;
	}

	//-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
	vector< DMatch > good_matches;
	for( int i = 0; i < descriptors_object.rows; i++ ){ 
		if( matches[i].distance <= 3*min_dist ){ 
			good_matches.push_back( matches[i]); 
		}
	}

	//-- Localize the object
	vector<Point2f> obj;
	vector<Point2f> scene;

	for( size_t i = 0; i < good_matches.size(); i++ ){
		//-- Get the keypoints from the good matches
		obj.push_back(keypoints_object[ good_matches[i].queryIdx ].pt);
		scene.push_back(keypoints_scene[ good_matches[i].trainIdx ].pt);
	}
	H = (findHomography( obj, scene, RANSAC));

	return SUCCESS;

}