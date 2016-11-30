#ifndef _LFC_H_
#define _LFC_H_

#include <vector>
#include <map>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define FAILURE -1
#define SUCCESS 0

#define NUM_FRAMING_IMAGES 6

#define IMAGE_RESOLUTION_X 480
#define IMAGE_RESOLUTION_Y 640

#define POSE_RESOLUTION_X 120
#define POSE_RESOLUTION_Y 160

//essentially defines a ray bundle
//have to calculate dimensions of the patch
typedef pair<Point2f, int> pointAndPixel;
typedef map<Point2f, pointAndPixel> lightfieldStruct;

class LightFieldClass {

public:

	lightfieldStruct lightfield;
	vector <Mat *> frameImages;
	vector <Mat> homographiesOfFrameImages;
	vector <Mat> posesOfFrameImages;

	vector <Mat *> samplingPath;

	//dimensions- (s,t)-poses; (u,v)-points
	int s;
	int t;
	int u;
	int v;
	//tolerance thresholds
	int tMin;
	int tMax;


};

//int calculateHomography(Mat* img_object, Mat* img_scene, Mat & H);
//
//int getTheData(LightFieldClass * currField);
//
//int makeTheFrame(LightFieldClass * currField);
//
//int poseFromHomography(const Mat& H, Mat& pose);

#endif