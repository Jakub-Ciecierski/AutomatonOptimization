//
// Created by dybisz on 11/12/15.
//

#include "global_settings.h"

// Meaning of constants described in global_settings.h
// This file is just for quick values manipulations
namespace global_settings {
    /* ------ OPTIMIZER SETTINGS ----- */
    int MIN_STATES              = 3;
    int MAX_STATES              = 5;

    /* ------ PSO SETTINGS ----- */
    std::string TOOL_URL        = "test_jastrz.txt";
    int MAX_ITER                = 90;
    double LEARNING_FACTOR      = 0.5 + log(2.0);
    double PARTICLE_VEL_WEIGHT  = 1.0 / (2.0 * log(2.0));
    double ENCODING_DELTA       = 0.5f;
    double UPPER_BOUND_ERR      = 0.001f;
    double SPEED_FACTOR         = 0.5f;
    double POPULATION_FACTOR    = 5.0f;
    double FITNESS_TOLERANCE    = 1.0f;

    int DEFAULT_THREAD_COUNT    = 4;

    /* ------ WORDS GENERATION ----- */
    int R_MAX                   = 100;
    int SIZE_S                  = 30;
    int SIZE_M                  = 30;
    int SIZE_L                  = 30;
    int MIN_LENG_S              = 2;
    int MAX_LENG_S              = 39;
    int MIN_LENG_M              = 40;
    int MAX_LENG_M              = 69;
    int MIN_LENG_L              = 70;
    int MAX_LENG_L              = 100;
    
    /* ------ CLUSTERING ----- */
    double KM_TOL               = 0.0001f;
    int KM_MAX_ITER             = 10000;
    int START_K                 = 2;
    int END_K                   = 6;

    /* ------ LOGGER ----- */
    std::string LOG_MAIN_DIR    = "./logs";
    std::string LOG_CURR_DIR    = "TEST";
}
