//
// Created by dybisz on 11/12/15.
//

#include "global_settings.h"

// Meaning of constants described in global_settings.h
// This file is just for quick values manipulations
namespace global_settings {

    /* ------ PSO SETTINGS ----- */
    std::string TOOL_URL    = "test_jastrz.txt";
    int MIN_STATES          = 1;
    int MAX_STATES          = 6;

    /* ------ WORDS GENERATION ----- */
    int R_MAX               = 30;
    int SIZE_S              = 10;
    int SIZE_M              = 10;
    int SIZE_L              = 10;
    int MIN_LENG_S          = 1;
    int MAX_LENG_S          = 5;
    int MIN_LENG_M          = 6;
    int MAX_LENG_M          = 15;
    int MIN_LENG_L          = 16;
    int MAX_LENG_L          = 25;

    /* ------ CLUSTERING ----- */
    double KM_TOL = 0.0001f;
    int KM_MAX_ITER = 1000;
}
