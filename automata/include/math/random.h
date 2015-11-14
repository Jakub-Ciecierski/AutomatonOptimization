//
// Created by jakub on 11/12/15.
//

#ifndef AC_RANDOM_H
#define AC_RANDOM_H

#include "point.h"
#include <vector>
#include <random>

namespace rnd
{
    template <typename T>
    std::vector<Point<T>> uniformPoints(int count, int dim, T min, T max);
}

#endif //AC_RANDOM_H
