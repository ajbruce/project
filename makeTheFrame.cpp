#include <vector>
#include <string>
#include <iostream>
#include "LightfieldClass.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

/**
*Function that adds the data from the image to the
*lightfield.  Uses homography helper functions to find the
*pose of the camera.  Then puts that information into the
*lightfield. If there is already data there, then it takes the
*average
*/
//int LightFieldClass::makeTheFrame(LightFieldClass * currField) {
	int LightFieldClass::makeTheFrame(void) {
	LightFieldClass * currField = this;
	Mat H;

	int res = calculateHomography(*(currField->frameImages.at(0)), 
								  *(currField->frameImages.at(0)), H);

	cout << H << endl;

	if (res == FAILURE) {
		std::cout << "failed to find homography of: first" << std::endl;
		return res;
	}
	currField->homographiesOfFrameImages.push_back(H);

	for (int i = 1; i < NUM_FRAMING_IMAGES; ++i) {

		Mat H;
		//opencv
		res = calculateHomography(*(currField->frameImages.at(i)),
								  *(currField->frameImages.at(i - 1)), H);

		if (res == FAILURE) {
			std::cout << "failed to find homography of: " << i << std::endl;
			return res;
		}
		currField->homographiesOfFrameImages.push_back(H);
	}

	//now find total homographies.  first one is obviously 0. second one stays the same.	
	for (int j = 2; j < NUM_FRAMING_IMAGES; ++j) {

		//check that this matrix mult is in the correct order
		currField->homographiesOfFrameImages.at(j) =
			currField->homographiesOfFrameImages.at(j - 1) *
			currField->homographiesOfFrameImages.at(j);

	}

	////find total poses
	//for (int k = 0; k < NUM_FRAMING_IMAGES; ++k) {
	//	Mat pose;
	//	if (poseFromHomography(currField->homographiesOfFrameImages.at(k), pose) == FAILURE) {
	//		return FAILURE;
	//	}
	//	currField->posesOfFrameImages.at(k) = pose;
	//}

	return SUCCESS;

}