//
// Created by jakub on 11/10/15.
//

#include <log.h>
#include "flag_reader.h"

namespace console {

    void readFlags(int argc, char *argv[]) {
        std::vector<Flag> flags = getFlags();

        int i = 1;

        while (i < argc) {
            // Print help and exit app
            if (std::string(argv[i]) == "--help") {
                usage(argv[0], "Called for Help: ", flags);
                exit(EXIT_FAILURE);
            }
                // Or set all flags
            else {
                for (unsigned int j = 0; j < flags.size(); j++) {
                    if (argv[i] == flags[j].long_f ||
                        argv[i] == flags[j].short_f) {
                        std::string error;
                        // If value is missing
                        if (isError(argc, argv, i, flags[j], error)) {
                            usage(argv[0], error.c_str(), flags);
                            exit(EXIT_FAILURE);
                        }
                        flags[j].apply(argv[i + 1]);
                    }
                }
            }
            i++;
        }
    }

    bool isError(int argc, char *argv[], int i, Flag flag, std::string &error) {
        int j = i + 1;

        if (j >= argc && flag.type != BOOL) {
            error = "Not enough arguments";
            return true;
        }
        std::string str(argv[j]);
        if (str[0] == '-') {
            error = "Wrong input, values of flags can't start with /'-/'";
            return true;
        }
        return false;
    }

    void usage(char *appName, const char *what, std::vector<Flag> flags) {
        std::string INTENT = "    ";
        std::string PATH_TO_INFO = ".";
        int infoIntentStartColumn = 50;

        std::cout << what << std::endl;
        std::cout << appName << " Proper Flags: " << std::endl;
        for (unsigned int i = 0; i < flags.size(); i++) {
            int lineLength = 0;
            lineLength += flags[i].short_f.size();
            lineLength += INTENT.size();
            lineLength += flags[i].long_f.size();

            int actualIntentStart = infoIntentStartColumn - lineLength;

            std::cout
            << flags[i].short_f << INTENT
            << flags[i].long_f << " ";
            for (int j = 1; j < actualIntentStart; j++)
                std::cout << PATH_TO_INFO;
            std::cout << " " << flags[i].info
            << std::endl;
        }
    }


    std::vector<Flag> getFlags() {

        std::vector<Flag> flags;
        flags.push_back(Flag("A", "tool-url",
                             "Path to file with DFA Tool",
                             STRING, &global_settings::TOOL_URL));

        /* ------ OPTIMIZER SETTINGS ----- */
        flags.push_back(Flag("q", "state-min",
                             "Starting number of states in Optimizer",
                             INT, &global_settings::MIN_STATES));

        flags.push_back(Flag("Q", "state-max",
                             "Ending number of states in Optimizer",
                             INT, &global_settings::MAX_STATES));

        /* ------ PSO SETTINGS ----- */
        flags.push_back(Flag("l", "learn-fac",
                             "Learning Factor",
                             DOUBLE,
                             &global_settings::LEARNING_FACTOR));


        flags.push_back(Flag("v", "vel-weight",
                             "Particle Velocity Weight",
                             DOUBLE,
                             &global_settings::PARTICLE_VEL_WEIGHT));

        flags.push_back(Flag("s", "speed-fac",
                             "Speed Factor",
                             DOUBLE,
                             &global_settings::SPEED_FACTOR));


        flags.push_back(Flag("p", "pop-fac",
                             "Population Factor",
                             DOUBLE,
                             &global_settings::POPULATION_FACTOR));


        flags.push_back(Flag("f", "fit-tol",
                             "Fitness Tolerance",
                             DOUBLE,
                             &global_settings::FITNESS_TOLERANCE));

        flags.push_back(Flag("T", "thread-count",
                             "Default Thread Count - used only when system"
                                     " can't determine optimal number of "
                                     "threads",
                             DOUBLE,
                             &global_settings::DEFAULT_THREAD_COUNT));

        /* ------ WORDS GENERATION ----- */

        flags.push_back(Flag("R", "r-max",
                             "Maximum number of words",
                             INT,
                             &global_settings::R_MAX));


        flags.push_back(Flag("S", "w-size",
                             "Size of Small Omega",
                             INT,
                             &global_settings::SIZE_S));


        flags.push_back(Flag("M", "m-size",
                             "Size of Medium Omega",
                             INT,
                             &global_settings::SIZE_M));

        flags.push_back(Flag("L", "l-size",
                             "Size of Large Omega",
                             INT,
                             &global_settings::SIZE_L));

        flags.push_back(Flag("z", "word-s-min",
                             "Minimum Length of Small Words",
                             INT,
                             &global_settings::MIN_LENG_S));

        flags.push_back(Flag("Z", "word-s-max",
                             "Maximum Length of Small Words",
                             INT,
                             &global_settings::MAX_LENG_S));

        flags.push_back(Flag("x", "word-m-min",
                             "Minimum Length of Medium Words",
                             INT,
                             &global_settings::MIN_LENG_M));
        flags.push_back(Flag("X", "word-m-max",
                             "Maximum Length of Medium Words",
                             INT,
                             &global_settings::MAX_LENG_M));

        flags.push_back(Flag("c", "word-l-min",
                             "Minimum Length of Large Words",
                             INT,
                             &global_settings::MIN_LENG_L));
        flags.push_back(Flag("C", "word-l-max",
                             "Maximum Length of Large Words",
                             INT,
                             &global_settings::MAX_LENG_L));

        /* ------ CLUSTERING ----- */

        flags.push_back(Flag("t", "km-tol",
                             "K-means convergance tolerance",
                             DOUBLE,
                             &global_settings::KM_TOL));
        flags.push_back(Flag("i", "km-iter",
                             "K-means maxium iterations",
                             INT,
                             &global_settings::KM_MAX_ITER));

        flags.push_back(Flag("k", "km-s-k",
                             "Cluster evaluation starting k",
                             INT,
                             &global_settings::START_K));
        flags.push_back(Flag("K", "km-e-k",
                             "Cluster evaluation ending k",
                             INT,
                             &global_settings::END_K));

        /* ------ LOGGER ----- */

        flags.push_back(Flag("D", "log-main-dir",
                             "Main directory to store all logs",
                             STRING,
                             &global_settings::LOG_MAIN_DIR));
        flags.push_back(Flag("d", "log-dir",
                             "directory to store logs of current computations",
                             STRING,
                             &global_settings::LOG_CURR_DIR));

        return flags;
    }
}