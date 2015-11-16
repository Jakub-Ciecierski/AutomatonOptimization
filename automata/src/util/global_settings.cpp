//
// Created by dybisz on 11/12/15.
//

#include "global_settings.h"

// Meaning of constants described in global_settings.h
// This file is just for quick values manipulations
namespace global_settings {
    /* ------ OPTIMIZER SETTINGS ----- */
    int MIN_STATES              = 4;
    int MAX_STATES              = 21;

    /* ------ PSO SETTINGS ----- */
    std::string TOOL_URL        = "test_jastrz.txt";
    int MAX_ITER                = 200;
    double LEARNING_FACTOR      = 0.5 + log(2.0);
    double PARTICLE_VEL_WEIGHT  = 1.0 / (2.0 * log(2.0));
    double ENCODING_DELTA       = 0.5f;
    double UPPER_BOUND_ERR      = 0.001f;
    double SPEED_FACTOR         = 0.1f;
    double POPULATION_FACTOR    = 10.0f;
    double FITNESS_TOLERANCE    = 1.0f;

    /* ------ WORDS GENERATION ----- */
    int R_MAX                   = 30;
    int SIZE_S                  = 10;
    int SIZE_M                  = 10;
    int SIZE_L                  = 10;
    int MIN_LENG_S              = 1;
    int MAX_LENG_S              = 5;
    int MIN_LENG_M              = 6;
    int MAX_LENG_M              = 15;
    int MIN_LENG_L              = 16;
    int MAX_LENG_L              = 25;
    
    /* ------ CLUSTERING ----- */
    double KM_TOL               = 0.0001f;
    int KM_MAX_ITER             = 1000;
    int START_K                 = 2;
    int END_K                   = 4;
}
