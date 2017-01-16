#include <vector>
#include <string>
#include <iostream>
#include "LightfieldClass.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void findClosestNeighbors(LightFieldClass * lightfieldholder, Point2f uvCoord, 
						  lightfieldStructUnit neighbors[4]){

	double eucDist0 = 200000;
	double eucDist1 = 200000;
	double eucDist2 = 200000;
	double eucDist3 = 200000;

	typedef vector<lightfieldStructUnit>::iterator it_type;
	for (it_type iter = lightfieldholder->lightfield.begin();
		iter != lightfieldholder->lightfield.end(); ++iter) {
		Point2f tmp = (*iter).position;

		//closestCoord1: top left
		if ((tmp.x < uvCoord.x) && (tmp.y < uvCoord.y)) {
			float dist = sqrt((tmp.x - uvCoord.x) *(tmp.x - uvCoord.x)
				+ (tmp.y - uvCoord.y)*(tmp.y - uvCoord.y));

			if (dist < eucDist0) {
				eucDist1 = dist;
				neighbors[0] = (*iter);
			}
		}
		//closestCoord2: top right
		else if ((tmp.x >= uvCoord.x) && (tmp.y < uvCoord.y)) {
			float dist = sqrt((tmp.x - uvCoord.x) *(tmp.x - uvCoord.x)
				+ (tmp.y - uvCoord.y)*(tmp.y - uvCoord.y));

			if (dist < eucDist1) {
				eucDist1 = dist;
				neighbors[1] = (*iter);
			}
		}
		//closestCoord3: bottom left
		else if ((tmp.x < uvCoord.x) && (tmp.y >= uvCoord.y)) {
			float dist = sqrt((tmp.x - uvCoord.x) *(tmp.x - uvCoord.x)
				+ (tmp.y - uvCoord.y)*(tmp.y - uvCoord.y));

			if (dist < eucDist2) {
				eucDist2 = dist;
				neighbors[2] = (*iter);
			}
		}
		//closestCoord4: bottom right
		else if ((tmp.x >= uvCoord.x) && (tmp.y >= uvCoord.y)) {
			float dist = sqrt((tmp.x - uvCoord.x) *(tmp.x - uvCoord.x)
				+ (tmp.y - uvCoord.y)*(tmp.y - uvCoord.y));

			if (dist < eucDist3) {
				eucDist3 = dist;
				neighbors[3] = (*iter);
			}
		}
	}
}
//TODO- CHECK
bool isInsideRegion(vector<Point2f> patch, vector<Point2f> region) {

	if (patch[0].x > region[0].x  && patch[0].y > region[0].y) {
		if (patch[1].x > region[1].x  && patch[1].y < region[1].y) {
			if (patch[2].x < region[2].x  && patch[2].y > region[2].y) {
				if (patch[3].x < region[3].x  && patch[3].y < region[3].y) {
					return true;
				}
			}

		}
	}
	return false;

}

int LightFieldClass::findImageFromPose(Mat pose) {

	Mat newImage(IMAGE_RESOLUTION_X, IMAGE_RESOLUTION_Y, CV_8UC3, Scalar(0, 0, 0));

	vector<Point2f> imageCenterAndCorners(5);
	imageCenterAndCorners[0] = cvPoint(IMAGE_RESOLUTION_X / 2, IMAGE_RESOLUTION_Y / 2);
	imageCenterAndCorners[1] = cvPoint(0, 0);
	imageCenterAndCorners[2] = cvPoint(0, IMAGE_RESOLUTION_Y);
	imageCenterAndCorners[3] = cvPoint(IMAGE_RESOLUTION_X, 0);
	imageCenterAndCorners[4] = cvPoint(IMAGE_RESOLUTION_X, IMAGE_RESOLUTION_Y);

	vector<Point2f> cameraCenterAndCorners(5);
	perspectiveTransform(imageCenterAndCorners, cameraCenterAndCorners, pose);

	Point2f uvCoord = cameraCenterAndCorners[0];

	lightfieldStructUnit neighbors[4];
	findClosestNeighbors(this, uvCoord, neighbors);

	int patchSize = 10;

	for (int i = 0; i < IMAGE_RESOLUTION_X - patchSize; i += patchSize) {
		for (int j = 0; j < IMAGE_RESOLUTION_Y - patchSize; j+= patchSize) {

			bool outOfBounds = true;
			vector<Point2f> patchCornersUV(4);
			patchCornersUV[0] = cvPoint(i, j);
			patchCornersUV[1] = cvPoint(i, j + patchSize);
			patchCornersUV[2] = cvPoint(i + patchSize, j);
			patchCornersUV[3] = cvPoint(i + patchSize, j + patchSize);

			vector<Point2f> patchCornersST(4);
			perspectiveTransform(patchCornersUV, patchCornersST, pose.inv());

			int k = 0;
			for (k; k < 4; ++k) {
				if (isInsideRegion(patchCornersST, (neighbors[k]).corners)) {
					outOfBounds = false;
					break;
				}
			}

			if (!outOfBounds) {
				return FAILURE;
			}
			Mat imageToCopyPatch = *(neighbors[k].image);

			vector<Point2f> originalCornersUV(4);
			perspectiveTransform(patchCornersST, originalCornersUV,
								 *(neighbors[k].homography));

			for (int m = 0; m < patchSize; ++m) {
				for (int n = 0; n < patchSize; ++n) {
					newImage.at<uchar>(m + i, n + j) = 
						imageToCopyPatch.at<uchar>(Point2f(originalCornersUV[0].x + i,
													   originalCornersUV[0].y + j));

				}
			}
		}
	}
	//TODO display new image
	return SUCCESS;
}
