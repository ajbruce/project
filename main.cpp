#include <vector>
#include <string>
#include <math.h>
#include <iostream>
#include "dirent.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

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
	if (argc < 1)
	{
		cout << " Usage: display_image ImageToLoadAndDisplay" << endl;
		return -1;
	}

	string inputDirectory = "C:\\Users\\ajbruce\\workspace\\Project";
	DIR *directory = opendir(inputDirectory.c_str());
	struct dirent *_dirent = NULL;
	if (directory == NULL)
	{
		printf("Cannot open Input Folder\n");
		return 1;
	}

	LightFieldClass * lightfield = new LightFieldClass();
	int i = 0;
	while ((_dirent = readdir(directory)) != NULL)
	{
		string fileName = inputDirectory + "\\" + string(_dirent->d_name);
		Mat image = imread(fileName.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
		if (image.data == NULL)
		{
			cout << "Error: Cannot Open Image: " << i << endl;
			continue;
		}

		namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
		imshow("Display window", image);                   // Show our image inside it.

		waitKey(0);

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
		++i;

	}
	closedir(directory);

	if (lightfield->makeTheFrame() == FAILURE) {
		cout << "Error: could not create the frame" << endl;
		return -1;
	}

	if (lightfield->getTheData() == FAILURE) {
		cout << "Error: could not get the data" << endl;
		return -1;
	}

	Mat pose;
	if (lightfield->findImageFromPose(pose) == FAILURE) {
		cout << "Error: could not find the new image" << endl;
		return -1;
	}

	return 0;
}