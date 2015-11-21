//
// Created by dybisz on 21/11/15.
//

#ifndef ACPROJECT_PLOTKIN_BOUND_H
#define ACPROJECT_PLOTKIN_BOUND_H

#include <stdexcept>
#include <logger.h>
#include <iostream>

using namespace std;

// Since there is no quick way to check how many possible strings
// of specific length with hamming distance bounded from below there are,
// we use Plotkin Bound to roughly estimate this value.
class PlotkinBound {
public:
    int calculate(int numberOfSymbols, int length, int distance);

private:
    int _calculatePlotkinForBinaryAlphabet(int n, int d);

    int _calculateOrdinaryPlotkin(int q, int n, int d);

    void _checkDenominatorCondition(int q, int n, int d);

    int _calculateBinaryEvenCase(int n, int d);

    int _calculateBinaryOddCase(int n, int d);

    // Checks if d is half of n. In case n is even: 2*d = n,
    // but in case odd n: 2*d + 1 = n for function to be true.
    bool _checkIfHalf(int n, int d);
};

#endif //ACPROJECT_PLOTKIN_BOUND_H
