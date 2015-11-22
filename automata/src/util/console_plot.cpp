//
// Created by root on 22/11/15.
//

#include <logger.h>
#include "console_plot.h"

ConsolePlot::ConsolePlot(int graphWidth, int graphHeight) : _graphWidth(graphWidth),
                                                            _graphHeight(graphHeight) {
    _bucketWidth = (double) global_settings::MAX_ITER / (double) _graphWidth;
    _bucketHeight = 1.0 / (double) _graphHeight;
    _barSymbol = "\u25A0";
    _init();
}

void ConsolePlot::_init() {
    for (int w = 0; w < _graphWidth; w++) {
        vector<int> _bar;
        for (int h = 0; h < _graphHeight; h++) {
            _bar.push_back(0);
        }
        _graph.push_back(_bar);
    }
}


void ConsolePlot::update(int t, double value) {
    if(_bucketWidth <= 1) {
        _updateBar(t, value);
    } else if (_bucketWidth > 1 && (t % (int) _bucketWidth == 0)) {
        _updateBar(t / _bucketWidth, value);
    }
}

void ConsolePlot::_updateBar(int t, double value) {
    for(int h = 0; h < value * _graphHeight; h++) {
        _graph[t][h] = 1;
    }
}

int ConsolePlot::print() {
    int numberOfLinesOccupied = 0;
    char arrowHead1[] = "\u25B2";
    cout << FREE_SPACE << "   " << "[F]"<< endl;
    cout << FREE_SPACE << "    " << arrowHead1<< endl;
    numberOfLinesOccupied+=2;
    for(int h = _graphHeight - 1; h >= 0 ; h--) {
        char line[] = "\u2528";
        cout << FREE_SPACE << _axisMarked(h) <<line;
        for(int t =  0; t < _graphWidth; t++) {
            int v =  _graph[t][h];

            if(v == 1) {
                // "\u2588" FULL BLOCK
                // "\u25FC" SQUARES LARGE
                cout << GREEN_TEXT("\u2588");
            }
            else {
                cout << " ";
            }

        }
        cout << endl;
        numberOfLinesOccupied++;
    }

    char elbow[] = "\u2517";
    cout << FREE_SPACE << "    "<<elbow;
    for(int i =0; i < _graphWidth * (2.0/3.0); i++) {
        char str[] = "\u2501";
        cout << str;
    }
    char arrowHead2[] = "\u25B6";
    cout << arrowHead2 <<" [t]"<< endl;
    numberOfLinesOccupied++;


    return numberOfLinesOccupied;
}

string ConsolePlot::_axisMarked(int h ) {
    if(h == _graphHeight -1) {
        return "  1 ";
    }
    else if (h == _graphHeight /2) {
        return "0.5 ";
    } else if(h == 0) {
        return  "  0 ";
    } else {
        return "    ";
    }
}


