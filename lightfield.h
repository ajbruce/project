#include <stdlib>
#include <vector>
#include <string

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

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

};
