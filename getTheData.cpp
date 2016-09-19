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

#define FAILURE -1
#define SUCCESS 0

/**
 *Function that adds the data from the image to the
 *lightfield.  Uses homography helper functions to find the 
 *pose of the camera.  Then puts that information into the 
 *lightfield. If there is already data there, then it takes the
 *average
 */
int getTheData(Lightfield * currField) {
	
	
	vector<Mat *>::iterator it = currField->frameImages.begin();
	
	for (it ; it != currField->frameImages.end(); ++it) {
		
		Mat H;
		int res = FAILURE;
		int i;
		for(i = 0; i < NUMFRAMINGIMAGES; ++i) {
			res = calculateHomography(it, currField->frameImages.at(i), H);
			if(res == SUCCESS) {
				break;
			}
		}
		if(res == FAILURE) {
			return res;
		}
		
		//find the total homography of current image from the first frame
		//unclear if this matrix mult is in the correct order
		Mat totalH = homographiesOfFrameImages.at(i) * H;
		Mat pose;

		if(poseFromHomography(totalH, pose) == FAILURE) {
			return FAILURE;
		}
		
		//find coordinates from homography and pose
		
		//insert the data into the lightfield structure
		
		//find next pose
		
		
		
	}
	





}
