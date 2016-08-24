#include <stdlib>
#include <vector>
#include <string>
#include <math.h>
using namespace std;


//Create array of images from input

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

vector<Mat> images;

/**
 * receive an array of images and create a lightfield
 */
int main( int argc, char** argv )
{
    if( argc < 2)
    {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }

    Mat image;
    for(int i = 1; i < argc; i++){
    	
    	image = imread(argv[i], CV_LOAD_IMAGE_GRAYSCALE);
    	if(! image.data )                              // Check for invalid input
    	{
        	cout <<  "Error: could not open image" << std::endl ;
        	return -1;
   		}
    	images.push_back(image);
    }
       // Read the file

    // namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    // imshow( "Display window", image );                   // Show our image inside it.

    // waitKey(0);                                          // Wait for a keystroke in the window
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
