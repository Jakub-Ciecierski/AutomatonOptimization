//
// Created by root on 21/11/15.
//

#include "plotkin_bound.h"

// q - number of symbols
// n - word length
// d - hamming distance
//
// Boundary is calculated differently for binary alphabet.
// It is because more precise formulas are available.
int PlotkinBound::calculate(int q, int n, int d) {
    bool binaryAlphabet = (q == 2);

    if (binaryAlphabet) {
        return _calculatePlotkinForBinaryAlphabet(n, d);
    } else {
        return _calculateOrdinaryPlotkin(q, n, d);
    }
}

int PlotkinBound::_calculatePlotkinForBinaryAlphabet(int n, int d) {
    bool distanceIsEven = (d % 2 == 0);

    if (distanceIsEven) {
        return _calculateBinaryEvenCase(n, d);
    } else {
        return _calculateBinaryOddCase(n, d);
    }
}

int PlotkinBound::_calculateBinaryEvenCase(int n, int d) {
    bool isHalf = _checkIfHalf(n, d);

    if (isHalf) {
        return 2 * n;
    } else if (2 * d > n) {
        return 2 * (int) ((double) d / (double) (2.0 * d - n));
    } else {
        throw invalid_argument("Plotkin Bound error: 2 * d < n || n: " + to_string(n) + " d: " + to_string(d));
    }
}

int PlotkinBound::_calculateBinaryOddCase(int n, int d) {
    bool isHalf = _checkIfHalf(n, d);

    if (isHalf) {
        return n + 1; // TODO(dybisz) verify
    } else if (((2 * d) + 1) > n) {
        return 2 * (int) ((double) d / (double) (2.0 * d - n));
    } else {
        throw invalid_argument("Plotkin Bound error: 2 * d  + 1< n || n: " + to_string(n) + " d: " + to_string(d));
    }
}

bool PlotkinBound::_checkIfHalf(int n, int d) {
    bool lengthEven = (n % 2 == 0);

    if (lengthEven) {
        return d * 2 == n;
    } else {
        return (d * 2) + 1 == n;
    }
}

int PlotkinBound::_calculateOrdinaryPlotkin(int q, int n, int d) {
    _checkDenominatorCondition(q, n, d);
    return (q * d) / (q * d - ((q - 1) * n));
}

void PlotkinBound::_checkDenominatorCondition(int q, int n, int d) {
    if (d * q <= n * (q - 1)) {
        throw invalid_argument("Wrong Plotkin Bound Parameters; q: "
                               + to_string(q) + " n: " + to_string(n)
                               + " d: " + to_string(d));
    }
}


