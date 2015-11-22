//
// Created by dybisz on 11/12/15.
//

#include "global_settings.h"

// Meaning of constants described in global_settings.h
// This file is just for quick values manipulations
namespace global_settings {
    /* ------ OPTIMIZER SETTINGS ----- */
    int MIN_STATES              = 4;
    int MAX_STATES              = 10;

    /* ------ PSO SETTINGS ----- */
    std::string TOOL_URL        = "test_jastrz.txt";
    int MAX_ITER                = 100;
    double LEARNING_FACTOR      = 0.5 + log(2.0);
    double PARTICLE_VEL_WEIGHT  = 1.0 / (2.0 * log(2.0));
    double ENCODING_DELTA       = 0.5f;
    double UPPER_BOUND_ERR      = 0.001f;
    double SPEED_FACTOR         = 0.1f;
    double POPULATION_FACTOR    = 1.0f;
    double FITNESS_TOLERANCE    = 1.0f;

    /* ------ WORDS GENERATION ----- */
    int R_MAX                   = 300;
    int SIZE_S                  = 100;
    int SIZE_M                  = 100;
    int SIZE_L                  = 100;
    int MIN_LENG_S              = 20;
    int MAX_LENG_S              = 140;
    int MIN_LENG_M              = 400;
    int MAX_LENG_M              = 690;
    int MIN_LENG_L              = 700;
    int MAX_LENG_L              = 1000;
    
    /* ------ CLUSTERING ----- */
    double KM_TOL               = 0.0001f;
    int KM_MAX_ITER             = 1000;
    int START_K                 = 2;
    int END_K                   = 4;

    /* ------ LOGGER ----- */
    std::string LOG_MAIN_DIR    = "./log";
    std::string LOG_CURR_DIR    = "TEST";
}
