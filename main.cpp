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

	vector<String> fn;
	string path = "C:\\Users\\ajbruce\\workspace\\Project\\small_data_set\\*.png";
	glob(path, fn, false);
	// Now we have list of filenames in fn.

	if (fn.size() <= 6) {
		return FAILURE;
	}


	Mat * allImages = new Mat[fn.size()];
	LightFieldClass * lightfield = new LightFieldClass();
	int i = 0;

	vector<String>::iterator it;
	for (it = fn.begin(); it != fn.end(); ++it) {
		Mat image = imread(*(it), CV_LOAD_IMAGE_GRAYSCALE);
		if (image.data == NULL) {
			cout << "Error: Cannot Open Image: " << i << endl;
			continue;
		}
		allImages[i] = image;
  		if (i < NUM_FRAMING_IMAGES) {
			//insert the resized image into the lightfield
			lightfield->frameImages.push_back(&(allImages[i]));
		}
		else {
			lightfield->samplingPath.push_back(&(allImages[i]));
		}
		++i;
	}

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


	delete[] allImages;
	delete lightfield;

	return 0;
}