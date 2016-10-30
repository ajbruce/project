#include <stdlib>
#include <vector>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "lightfield.h"
#include "calculateHomography.cpp"
#include "poseFromHomography.cpp"

using namespace cv;

/**
 *Function that adds the data from the image to the
 *lightfield.  Uses homography helper functions to find the 
 *pose of the camera.  Then puts that information into the 
 *lightfield. If there is already data there, then it takes the
 *average
 */
int makeTheFrame(LightFieldClass * currField) {
	
	
	int res = calculateHomography(currField->frameImages.at(0), currField->frameImages.at(0), H);
	
	if(res == FAILURE) {
		std:: cout << "failed to find homography of: first" << std::endl;
		return res;
	}
	currField->homographiesOfFrameImages.at(0) = H;
	
	int i = 1;
	for (i; i < NUM_FRAMING_IMAGES; ++it) {
		
		Mat H;
		//opencv
		res = calculateHomography(currField->frameImages.at(i), 
					  currField->frameImages.at(i - 1), H);
								  
		if(res == FAILURE) {
			std:: cout << "failed to find homography of: " << i << std::endl;
			return res;
		}
		currField->homographiesOfFrameImages.at(i) = H;
	}
	
	//now find total homographies.  first one is obviously 0. second one stays the same.	
	int j = 2;
	for(j; j < NUM_FRAMING_IMAGES; ++j) {
		
		//check that this matrix mult is in the correct order
		currField->homographiesOfFrameImages.at(j) = 
						currField->homographiesOfFrameImages.at(j - 1) *
					    currField->homographiesOfFrameImages.at(j);
	
	}
	
	//find total poses
	for(j; j < NUM_FRAMING_IMAGES; ++j) {
		Mat pose; 
		if(poseFromHomography(totalH, pose) == FAILURE) {
			return FAILURE;
		}
		currField->posesOfFrameImages.at(j) = pose;
	}

	
}
