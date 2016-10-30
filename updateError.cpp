#include <stdlib>
#include <vector>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


#include "lightfield.h"


using namespace cv;

/**
 *for each ray bundle, minimize the error function, which is
 * 1-(frac of area auv)
 */
Coordinate findNextPose(LightfieldClass * currField) {

    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    //go through each ray bundle
    for (i; i < currField->s; ++i) {
    	for (j; j < currField->t; ++j) {
    		for (k; k < currField->u; ++k) {
    			for (l; l < currField->v; ++l) {

    				//go through all previous poses on sampling path
    				int c = 0;
					int error = 100;
					for(Coordinate * currPose : currField->samplingPath) {
						int newError = findNewError(currPose);
    				}
    				currField->bundleArray[i][j][k][l].error = newError;
    			}
    		}
    	}
    }

}

int findNewError(Coordinate * pose) {

}
