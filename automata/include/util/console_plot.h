//
// Created by dybisz on 22/11/15.
//

#ifndef AC_CONSOLE_PLOT_H
#define AC_CONSOLE_PLOT_H

#include <iostream>
#include <vector>
#include <string>
#include "global_settings.h"

using namespace std;

// WARNING: Class is partially based on global_settings.cpp/h.
class ConsolePlot {
public:
    ConsolePlot(int graphWidth, int graphHeight);

    void update(int t, double value);

    int print();

private:
    vector<vector<int>> _graph;
    double _bucketWidth;
    double _bucketHeight;
    int _graphWidth;
    int _graphHeight;
    string _barSymbol;

    void _init();

    void _updateBar(int t, double value);
    string _axisMarked(int h );
};

#endif //AC_CONSOLE_PLOT_H
