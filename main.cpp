#include <stdlib>
#include <vector>
#include <string>
#include <math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "makeTheFrame.cpp"
#include "getTheData.cpp"
#include "lightfield.h"

using namespace cv;
using namespace std;


/**
 * receive an array of images and create a lightfield
 * 
 */
int main( int argc, char** argv )
{
    if( argc < 2)
    {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }
    
    LightfieldClass * lightfield = new LightfieldClass()s;

    Mat image;
    int i;
    for(int i; i < argc + 1; i++){
		
		//loads image as grayscale
    	image = imread(argv[i + 1], CV_LOAD_IMAGE_GRAYSCALE);
    	// Check for invalid input
    	if(!image.data )                              
    	{
        	cout <<  "Error: could not open image" << endl ;
        	return -1;
   		}
   		if(i < NUM_FRAMING_IMAGES) {
   			//resize the image so that it is the correct resulution
			Size size(IMAGE_RESOLUTION_X, IMAGE_RESOLUTION_X);
   			resize(image,image,size)
   			
   			//insert the resized image into the lightfield
			lightfield->frameImages.push_back(&image);
		}
		else {
			lightfield->samplingPath.push_back(&image);
		}
    }
    
    int res;
    
    res = makeTheFrame(lightfield);
    
    if(res == FAILURE) {
		cout <<  "Error: could not create the frame" << endl;
        return -1;
	}
    
    
    res = getTheData(lightfield);
    
    if(res == FAILURE) {
		cout <<  "Error: could not get the data" << endl;
        return -1;
	}
    
    
    return 0;
}

/**
 * Compute the positions 
 */
void samplingParameter(Mat[] &x, Mat[] &theta, int delta_max){

	//fitting position and size of UV to theta and of ST to x
	//Surface fitting
	Coordinate theta_center = centerGravity(theta);
	Coordinate x_center = centerGravity(x);

	theta_center.difference(x_center);
	//find norm
	//	int fitting = norm(theta_center.x, theta_center.y);
	
    //SAMPLING RATES//
   
    int dmin, dmax;  // need to calculate minimum and maximum depths in theta

    int rh, alphah;  // need to get camera's horizontal image resolution and field of view angle 

    int distanceST = ((delta_max*2*tan(alphah/2))/rh)*((1/dmin)-(1/dmax));

}
