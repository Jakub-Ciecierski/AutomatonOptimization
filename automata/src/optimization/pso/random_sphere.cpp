//
// Created by root on 11/14/15.
//

#include "random_sphere.h"

RandomSphere::RandomSphere(Point<double> centerOfGravity, Point<double> oldPosition) :
_center(centerOfGravity){
    _radius = utils::euclidianDistance(centerOfGravity, oldPosition);
//    cout << "radius: " << _radius << endl;
    _dimensions = centerOfGravity.size();
}

Point<double> RandomSphere::generatePointWithin() {
    Point<double> pointInHypercube;
    pointInHypercube = utils::generateRandomPoint(_dimensions, -_radius, _radius);
    pointInHypercube = _translatePoint(pointInHypercube, _center);
    Point<double> toCenter = _center - pointInHypercube;
    while(_outsideTheSphere(pointInHypercube)) {
//        cout << "X': " << pointInHypercube;
        pointInHypercube = pointInHypercube + (toCenter * 0.0001);
//        cout << "\nby: " << (toCenter * 0.1) << "\nto :" << pointInHypercube << endl;
//        cout << "to achieve center: " << _center << endl;
    }

//    do {

////        cout << "radius: " << _radius << endl;
////            cout << "pointInHypercube: " << pointInHypercube  << endl;
//    } while(_outsideTheSphere(pointInHypercube));

    return pointInHypercube;
}

bool RandomSphere::_outsideTheSphere(Point<double> point) {
    double sumOfSquares = 0;

    for(int i = 0; i < _dimensions; i++) {
        sumOfSquares += (point[i]- _center[i]) * (point[i] - _center[i]);
    }

    return (sumOfSquares > (_radius * _radius));
}

string RandomSphere::toString() {
    string outputString = "";
    outputString += "center: " + _center.toString();
    outputString += "radius: " + to_string(_radius);
    return outputString;
}

Point<double> RandomSphere::_translatePoint(Point<double> point, Point<double> translateVector) {
    for(int i = 0; i < point.size(); i++) {
        point[i] += translateVector[i];
    }
    return point;
}
