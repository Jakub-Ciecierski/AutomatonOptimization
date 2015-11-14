//
// Created by root on 11/14/15.
//

#ifndef ACP_RANDOM_SPHERE_H
#define ACP_RANDOM_SPHERE_H

#include <math/point.h>
#include "utils.h"

class RandomSphere {
public:
    RandomSphere(Point<double> centerOfGravity, Point<double> oldPosition);
    Point<double> generatePointWithin();
private:
    Point<double> _center;
    double _dimensions;
    double _radius;

    bool _outsideTheSphere(Point<double> point);
};

#endif //ACPROJECT_RANDOM_SPHERE_H
