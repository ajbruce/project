#include <vector>
#include <string>
#include <math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "LightfieldClass.h"

using namespace std;
using namespace cv;


/**
* receive an array of images and create a lightfield
*
*/
//y is the ROW, x is the COL
int main(int argc, char** argv)
{
	if (argc < 2)
	{
		cout << " Usage: display_image ImageToLoadAndDisplay" << endl;
		return -1;
	}

	LightFieldClass * lightfield = new LightFieldClass();

	Mat image;
	int i = 0;
	for (i; i < argc + 1; ++i) {

		//loads image as grayscale
		image = imread(argv[i + 1], CV_LOAD_IMAGE_GRAYSCALE);
		// Check for invalid input
		if (!image.data)
		{
			cout << "Error: could not open image" << endl;
			return -1;
		}
		if (i < NUM_FRAMING_IMAGES) {
			//resize the image so that it is the correct resulution
			Size size(IMAGE_RESOLUTION_X, IMAGE_RESOLUTION_X);
			cv::resize(image, image, size);

			//insert the resized image into the lightfield
			lightfield->frameImages.push_back(&image);
		}
		else {
			lightfield->samplingPath.push_back(&image);
		}
	}

	int res;

	res = lightfield->makeTheFrame();

	if (res == FAILURE) {
		cout << "Error: could not create the frame" << endl;
		return -1;
	}


	res = lightfield->getTheData();

	if (res == FAILURE) {
		cout << "Error: could not get the data" << endl;
		return -1;
	}


	//TODO- get a pose from image
	Point2f uvCoord;
	res = lightfield->findImageFromPose(uvCoord);

	return 0;
}