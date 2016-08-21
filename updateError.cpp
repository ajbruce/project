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
Coordinate findNextPose(Lightfield * currField) {

    int error = 1;

    for ( int i = 0; i < currField->samplingPoses; ++i) {
        
    }
}
