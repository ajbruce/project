#include <stdlib>
#include <vector>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;

#define NUMFRAMINGIMAGES 6

typedef pair<int, int> orderedPair
typedef pair<orderedPair, int> orderedPairAndPixel
typedef map<orderedPair, orderedPairAndPixel> lightfieldStruct



//probably not used any more
typedef struct Coordinate
{
    int x;
    int y;

public:
    Coordinate (int x, int y) : x(x), y(y) {}
    Coordinate difference (Coordinate & other)
    {
        return Coordinate(this->x - other.x, this->y - other.y);
    }
} Coordinate;


//probably not used any more
class RayBundle {
    Mat pose;
    Coordinate point;
    int sizeVertical;
    int sizeHorizontal;

    RayBundle(Mat pose, Coordinate point, int sizeVertical,
              int sizeHorizontal) : pose(pose), point(point),
                                    sizeVertical(sizeVertical),
                                    sizeHorizontal(sizeHorizontal) {}


};

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
