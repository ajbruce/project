#include <stdlib>
#include <vector>
#include <string>
#include "lightfield.h"
#include "calculateHomography.cpp"
#include "poseFromHomography.cpp"

using namespace std;


//Create array of images from input

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

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
int rayFromImage(Lightfield * currField, Mat * image) {

	Mat H = calculateHomography(currField->originImage, image)
	
	// 3x4 matrix, the camera pose
	Mat pose;

	if(poseFromHomography(H, pose) == FAILURE) {
		return FAILURE;
	}





}
