//
// Created by root on 11/14/15.
//

#ifndef ACP_RANDOM_SPHERE_H
#define ACP_RANDOM_SPHERE_H

#include <math/point.h>
#include "utils.h"
#include <string>

// Great document about hypercubes-hypersphere relations,
// when nunmber of dimensions increases:
// https://www.cs.cmu.edu/~venkatg/teaching/CStheory-infoage/chap1-high-dim-space.pdf
class RandomSphere {
public:
    RandomSphere(Point<double> centerOfGravity, Point<double> oldPosition);
    Point<double> generatePointWithin();
    string toString();

private:
    Point<double> _center;
    double _dimensions;
    double _radius;

    bool _outsideTheSphere(Point<double> point);

    Point<double> _translatePoint(Point<double> point, Point<double> center);
};

#endif //ACPROJECT_RANDOM_SPHERE_H
