//
// Created by dybisz on 11/12/15.
//

#include <sstream>
#include <logger/log.h>
#include "global_settings.h"

// Meaning of constants described in global_settings.h
// This file is just for quick values manipulations
namespace global_settings {
    /* ------ OPTIMIZER SETTINGS ----- */
    int MIN_STATES              = 20;
    int MAX_STATES              = 21;

    /* ------ PSO SETTINGS ----- */
    std::string TOOL_URL        = "test_jastrz.txt";
    int MAX_ITER                = 90;
    double LEARNING_FACTOR      = 0.5 + log(2.0);
    double PARTICLE_VEL_WEIGHT  = 1.0 / (2.0 * log(2.0));
    double ENCODING_DELTA       = 0.5f;
    double UPPER_BOUND_ERR      = 0.001f;
    double SPEED_FACTOR         = 0.5f;
    double POPULATION_FACTOR    = 1.0f;
    double FITNESS_TOLERANCE    = 1.0f;

    int DEFAULT_THREAD_COUNT    = 4;

    /* ------ WORDS GENERATION ----- */
    int R_MAX                   = 300;
    int SIZE_S                  = 100;
    int SIZE_M                  = 100;
    int SIZE_L                  = 100;
    int MIN_LENG_S              = 20;
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

    //--------------------------------------------------------------------------

    void printSettings(){
        const std::string PATH_TO_VALUE = ".";
        int startColumn = 50;

        std::stringstream ss;
        std::string s = "";


        ss << std::endl<< "SETTINGS" <<std::endl;

        ss << std::endl<< "OPTIMIZER SETTINGS" <<std::endl <<std::endl;;

        s = "MIN_STATES ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << MIN_STATES << std::endl;


        s = "MAX_STATES ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << MAX_STATES << std::endl;


        ss << std::endl<< "POS SETTINGS" <<std::endl <<std::endl;


        s = "TOOL_URL ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << TOOL_URL << std::endl;

        s = "MAX_ITER ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << MAX_ITER << std::endl;

        s = "LEARNING_FACTOR ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << LEARNING_FACTOR << std::endl;

        s = "PARTICLE_VEL_WEIGHT ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << PARTICLE_VEL_WEIGHT << std::endl;

        s = "ENCODING_DELTA ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << ENCODING_DELTA << std::endl;

        s = "UPPER_BOUND_ERR ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << UPPER_BOUND_ERR << std::endl;

        s = "SPEED_FACTOR ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << SPEED_FACTOR << std::endl;

        s = "POPULATION_FACTOR ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << POPULATION_FACTOR << std::endl;

        s = "FITNESS_TOLERANCE ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << FITNESS_TOLERANCE << std::endl;

        s = "DEFAULT_THREAD_COUNT ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << DEFAULT_THREAD_COUNT << std::endl;


        ss << std::endl << "WORDS GENERATION SETTINGS" <<std::endl << std::endl;


        s = "R_MAX ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << R_MAX << std::endl;

        s = "SIZE_S ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << SIZE_S << std::endl;

        s = "SIZE_M ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << SIZE_M << std::endl;

        s = "SIZE_L ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << SIZE_L << std::endl;

        s = "MIN_LENG_S ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << MIN_LENG_S << std::endl;


        s = "MAX_LENG_S ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << MAX_LENG_S << std::endl;

        s = "MIN_LENG_M ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << MIN_LENG_M << std::endl;

        s = "MAX_LENG_M ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << MAX_LENG_M << std::endl;

        s = "MIN_LENG_L ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << MIN_LENG_L << std::endl;

        s = "MAX_LENG_L ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << MAX_LENG_L << std::endl;


        ss << std::endl<< "CLUSTERING SETTINGS" <<std::endl <<std::endl;


        s = "KM_TOL ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << KM_TOL << std::endl;

        s = "KM_MAX_ITER ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << KM_MAX_ITER << std::endl;

        s = "START_K ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << START_K << std::endl;

        s = "END_K ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << END_K << std::endl;



        ss << std::endl<< "LOGGER SETTINGS" <<std::endl <<std::endl;;


        s = "LOG_MAIN_DIR ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << LOG_MAIN_DIR << std::endl;

        s = "LOG_CURR_DIR ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << LOG_CURR_DIR << std::endl;


        logger::log(File("settings.txt"), ss.str());
    }
}
