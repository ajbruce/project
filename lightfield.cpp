#include <stdlib>
#include <vector>
#include <string>

using namespace std;


//Create array of images from input

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

vector<Mat> images;

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

    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", image );                   // Show our image inside it.

    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}
