#include <stdlib>
#include <vector>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;

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

class LightField {

    //lightFieldArray[s][t][u][v]
    int lightFieldArray[][][][];
    array <Mat> samplingPath;
    //dimensions- (s,t)-poses; (u,v)-points
    int s;
    int t;
    int u;
    int v;
    //tolerance thresholds
    int tMin;
    int tMax;


};
