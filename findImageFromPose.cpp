#include <vector>
#include <string>
#include <iostream>
#include "LightfieldClass.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;


int LightFieldClass::findImageFromPose(Point2f uvCoord) {
	Point2f closestCoord1;
	Point2f closestCoord2;
	Point2f closestCoord3;
	Point2f closestCoord4;

	Mat * image1;
	Mat * image2;
	Mat * image3;
	Mat * image4;

	double eucDist1 = 200000;
	double eucDist2 = 200000;
	double eucDist3 = 200000;
	double eucDist4 = 200000;

	typedef lightfieldStruct::iterator it_type;
	for (it_type iter = lightfield.begin(); 
		 iter != lightfield.end(); ++iter) {
		Point2f tmp = iter->first;

		//closestCoord1: top left
		if ((tmp.x < uvCoord.x) && (tmp.y < uvCoord.y)) {
			float dist = sqrt((tmp.x - uvCoord.x) *(tmp.x - uvCoord.x)
				+ (tmp.y - uvCoord.y)*(tmp.y - uvCoord.y));

			if (dist < eucDist1) {
				eucDist1 = dist;
				closestCoord1 = tmp;
				image1 = iter->second;
			}
		}
		//closestCoord2: top right
		else if ((tmp.x >= uvCoord.x) && (tmp.y < uvCoord.y)) {
			float dist = sqrt((tmp.x - uvCoord.x) *(tmp.x - uvCoord.x)
				+ (tmp.y - uvCoord.y)*(tmp.y - uvCoord.y));

			if (dist < eucDist2) {
				eucDist2 = dist;
				closestCoord2 = tmp;
				image2 = iter->second;
			}
		}
		//closestCoord3: bottom left
		else if ((tmp.x < uvCoord.x) && (tmp.y >= uvCoord.y)) {
			float dist = sqrt((tmp.x - uvCoord.x) *(tmp.x - uvCoord.x)
				+ (tmp.y - uvCoord.y)*(tmp.y - uvCoord.y));

			if (dist < eucDist3) {
				eucDist3 = dist;
				closestCoord3 = tmp;
				image3 = iter->second;
			}
		}
		//closestCoord4: bottom right
		else if ((tmp.x >= uvCoord.x) && (tmp.y >= uvCoord.y)) {
			float dist = sqrt((tmp.x - uvCoord.x) *(tmp.x - uvCoord.x)
				+ (tmp.y - uvCoord.y)*(tmp.y - uvCoord.y));

			if (dist < eucDist4) {
				eucDist4 = dist;
				closestCoord4 = tmp;
				image4 = iter->second;
			}
		}
	}

	//interpolation1
	float diffXLeftTop = uvCoord.x - closestCoord1.x;
	float diffXRightTop = closestCoord2.x - uvCoord.x;

	float alpha1 = diffXLeftTop / (diffXLeftTop + diffXRightTop);
	float alpha2 = diffXRightTop / (diffXLeftTop + diffXRightTop);



	

}