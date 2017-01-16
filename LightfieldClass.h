#ifndef _LFC_H_
#define _LFC_H_

#include <vector>
#include <map>
#include <string>
#include <iostream>

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/calib3d.hpp"


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
//typedef pair<Point2f, int> pointAndPixel;
//typedef map<Point2f, pointAndPixel> lightfieldStruct;

struct lightfieldStructUnit {

	Point2f position;
	Mat * image;
	Mat * homography;
	vector<Point2f> corners;

};

class LightFieldClass {

public:

	vector<lightfieldStructUnit> lightfield;
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

	int calculateHomography(Mat* img_object, Mat* img_scene, Mat & H);
	
	int getTheData(void);

	int makeTheFrame(void);
	
	int poseFromHomography(const Mat& H, Mat& pose);

	int findImageFromPose(Mat pose);


};



#endif