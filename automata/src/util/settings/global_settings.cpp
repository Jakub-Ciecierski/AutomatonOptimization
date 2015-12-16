//
// Created by dybisz on 11/12/15.
//

#include <sstream>
#include <logger/log.h>
#include "global_settings.h"

// Meaning of constants described in global_settings.h
// This file is just for quick values manipulations
namespace global_settings {
    /* ------ EXPERIMENT SETTINGS ----- */
    int EXPERIMENT_ID           = 0;

    /* ------ Words GENERATION SETTINGS ----- */
    int GEN_WORDS_SYMBOL_COUNT      = 5;
    int GEN_WORD_C                  = 5;
    int GEN_WORD_TRAIN_COUNT        = 4000;
    int GEN_WORD_TRAIN_MAX_LENGTH   = 20;
    int GEN_WORD_TEST_COUNT         = 4000;
    int GEN_WORD_TEST_MAX_LENGTH    = 30;

    /* ------ DFA GENERATION SETTINGS ----- */
    std::string GEN_DFA_PATH    = "";
    int GEN_DFA_STATES          = 8;
    int GEN_DFA_SYMBOLS         = 5;

    /* ------ OPTIMIZER SETTINGS ----- */
    int MIN_STATES              = 3;
    int MAX_STATES              = 15;

    /* ------ PSO SETTINGS ----- */
    std::string TOOL_URL        = "test_jastrz.txt";
    std::string WORDS_PATH      = "";
    int MAX_ITER                = 99;
    double LEARNING_FACTOR      = 0.5 + log(2.0);
    double PARTICLE_VEL_WEIGHT  = 1.0 / (2.0 * log(2.0));
    double ENCODING_DELTA       = 0.5f;
    double UPPER_BOUND_ERR      = 0.001f;
    double SPEED_FACTOR         = 0.05f;
    double MAX_VELOCITY         = 0.3f;
    double POPULATION_FACTOR    = 1.0f;
    double FITNESS_TOLERANCE    = 1.0f;
    int SWARM_SIZE              = 100;

    /* ------ THREAD SETTINGS ----- */
    int DEFAULT_THREAD_COUNT    = 4;
    int TRUE_THREAD_COUNT       = 0;

    /* ------ CLUSTERING ----- */
    double KM_TOL               = 0.0001f;
    int KM_MAX_ITER             = 1000;
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

        ss << std::endl<< "EXPERIMENT SETTINGS" <<std::endl <<std::endl;

        s = "EXPERIMENT_ID ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << EXPERIMENT_ID << std::endl;

        ss << std::endl<< "DFA GENERATION SETTINGS" <<std::endl <<std::endl;
        s = "GEN_DFA_PATH ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << GEN_DFA_PATH<< std::endl;


        s = "GEN_DFA_STATES ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << GEN_DFA_STATES<< std::endl;

        s = "GEN_DFA_SYMBOLS";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << GEN_DFA_SYMBOLS<< std::endl;

        ss << std::endl<< "OPTIMIZER SETTINGS" <<std::endl <<std::endl;

        s = "TOOL_URL ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << TOOL_URL << std::endl;

        s = "WORDS_PATH ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << WORDS_PATH << std::endl;

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


        ss << std::endl<< "PSO SETTINGS" <<std::endl <<std::endl;


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

        s = "MAX_VELOCITY ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << MAX_VELOCITY << std::endl;

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

        s = "SWARM_SIZE";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << SWARM_SIZE << std::endl;

        ss << std::endl << "THREADS SETTINGS" <<std::endl << std::endl;

        s = "DEFAULT_THREAD_COUNT ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << DEFAULT_THREAD_COUNT << std::endl;

        s = "TRUE_THREAD_COUNT ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << TRUE_THREAD_COUNT << std::endl;


        ss << std::endl << "WORDS GENERATION SETTINGS" <<std::endl << std::endl;


        s = "GEN_WORDS_SYMBOL_COUNT";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << GEN_WORDS_SYMBOL_COUNT<< std::endl;

        s = "GEN_WORD_C";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << GEN_WORD_C<< std::endl;


        s = "GEN_WORD_TRAIN_COUNT";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << GEN_WORD_TRAIN_COUNT << std::endl;


        s = "GEN_WORD_TRAIN_MAX_LENGTH";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << GEN_WORD_TRAIN_MAX_LENGTH<< std::endl;


        s = "GEN_WORD_TEST_COUNT";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << GEN_WORD_TEST_COUNT<< std::endl;



        s = "GEN_WORD_TEST_MAX_LENGTH";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << GEN_WORD_TEST_MAX_LENGTH<< std::endl;

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
