#include <stdlib>
#include <vector>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;

#define FAILURE -1
#define SUCCESS 0

#define NUM_FRAMING_IMAGES 6

#define IMAGE_RESOLUTION_X 480
#define IMAGE_RESOLUTION_Y 640

#define POSE_RESOLUTION_X 
#define POSE_RESOLUTION_Y 


typedef pair<int, int> orderedPair
typedef pair<orderedPair, int> orderedPairAndPixel
typedef map<orderedPair, orderedPairAndPixel> lightfieldStruct

class LightFieldClass {

	lightfieldStruct lightfield;
    vector <Mat *> frameImages;
	vector <Mat> homographiesOfFrameImages;
	vector <Mat> posesOfFrameImages;
	
    vector <Mat *> samplingPath;
    
    //dimensions- (s,t)-poses; (u,v)-points
    int s;
    int t;
    int u;
    int v;
    //tolerance thresholds
    int tMin;
    int tMax;


};
