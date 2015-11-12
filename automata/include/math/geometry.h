//
// Created by jakub on 11/11/15.
//

#ifndef AC_GEOMETRY_H
#define AC_GEOMETRY_H

#include "point.h"

/*
 * Contains useful geometry functions
 */
namespace acm
{

    /*
    * Returns the distance between two points
    */
    template<typename T>
    double distance(const Point<T>& p1, const Point<T>& p2);

    /*
     * Computes the mean point - the center of mass
     */
    template<typename T>
    Point<T> centerOfMass(const std::vector<Point<T>>* points);
}

#endif //AC_GEOMETRY_H
