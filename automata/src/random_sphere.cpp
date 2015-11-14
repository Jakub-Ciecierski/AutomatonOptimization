//
// Created by root on 11/14/15.
//

#include "random_sphere.h"

RandomSphere::RandomSphere(Point<double> centerOfGravity, Point<double> oldPosition) :
_center(centerOfGravity){
    _radius = utils::euclidianDistance(centerOfGravity, oldPosition);
    cout << "radius: " << _radius << endl;
    _dimensions = centerOfGravity.size();
}

Point<double> RandomSphere::generatePointWithin() {
    Point<double> pointInSphere;
    do {
        pointInSphere = utils::generateRandomPoint(_dimensions, -_radius, _radius);
    } while(_outsideTheSphere(pointInSphere));

    return pointInSphere;
}

bool RandomSphere::_outsideTheSphere(Point<double> point) {
    double sumOfSquares = 0;

    for(int i = 0; i < point.size(); i++) {
        sumOfSquares += (point[i] * point[i]);
    }

    return (sumOfSquares > (_radius * _radius));
}
