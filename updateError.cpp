#include <stdlib>
#include <vector>
#include <string>
#include "lightfield.h"

using namespace std;


//Create array of images from input

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/**
 *for each ray bundle, minimize the error function, which is
 * 1-(frac of area auv)
 */
Pose findNextPose(int * error, Lightfield * currField) {

}