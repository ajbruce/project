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
    Coordinate pose;
    Coordinate point;
    int sizeVertical;
    int sizeHorizontal;

    RayBundle(Coordinate pose, Coordinate point, int sizeVertical,
              int sizeHorizontal) : pose(pose), point(point),
                                    sizeVertical(sizeVertical),
                                    sizeHorizontal(sizeHorizontal) {}


};

class LightField {

    //lightFieldArray[s][t][u][v]
    int lightFieldArray[][][][];
    array <Coordinate> samplingPath;
    //dimensions- (s,t)-poses; (u,v)-points
    int s;
    int t;
    int u;
    int v;
    //tolerance thresholds
    int tMin;
    int tMax;


};
