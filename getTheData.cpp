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
int getTheData(Lightfield * currField) {
	
	
	vector<Mat *>::iterator it = currField->samplingPath.begin();
	
	for (it ; it != currField->samplingPath.end(); ++it) {
		
		Mat H;
		int res = FAILURE;
		int i;

		Mat image = *it;

		for(i = 0; i < NUM_FRAMING_IMAGES; ++i) {
			res = calculateHomography(image, currField->frameImages.at(i), H);
			if(res == SUCCESS) {
				break;
			}
		}
		if(res == FAILURE) {
			return res;
		}
		
		//find the total homography of current image from the first frame
		//unclear if this matrix mult is in the correct order
		Mat totalH = currField->homographiesOfFrameImages.at(i) * H;
		Mat pose;

		if(poseFromHomography(totalH, pose) == FAILURE) {
			return FAILURE;
		}
		
		//call rayFromImage function	
		
		
	}
	
}
