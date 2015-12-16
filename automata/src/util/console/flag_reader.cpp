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
                usage(argv[0], "Called for Help: ");
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
                            usage(argv[0], error.c_str());
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

    void usage(char *appName, const char *what) {
        std::vector<Flag> flags = getFlags();
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

        /* ------ EXPERIMENTS SETTINGS ----- */

        flags.push_back(Flag("E", "exp",
                             "Expiriment ID - "
                                     "0: Main Optimizer, "
                                     "1: DFA Generation, "
                                     "2: Word Generation",
                             INT, &global_settings::EXPERIMENT_ID));

        /* ------ DFA GENERATION SETTINGS ----- */

        flags.push_back(Flag("R", "gen-w-sym-count",
                             "Words Generation: Alphabet Size",
                             INT, &global_settings::GEN_WORDS_SYMBOL_COUNT));

        flags.push_back(Flag("C", "gen-w-c",
                             "Words Generation: The constant C",
                             INT, &global_settings::GEN_WORD_C));

        flags.push_back(Flag("T", "gen-w-train-size",
                             "Words Generation: Total train set count",
                             INT, &global_settings::GEN_WORD_TRAIN_COUNT));

        flags.push_back(Flag("Y", "gen-w-train-max-length",
                             "Words Generation: Train Set max word length",
                             INT, &global_settings::GEN_WORD_TRAIN_MAX_LENGTH));

        flags.push_back(Flag("t", "gen-w-test-size",
                             "Words Generation: Total test set count",
                             INT, &global_settings::GEN_WORD_TEST_COUNT));

        flags.push_back(Flag("y", "gen-w-test-max-length",
                             "Words Generation: Test Set max word length",
                             INT, &global_settings::GEN_WORD_TEST_MAX_LENGTH));

        /* ------ DFA GENERATION SETTINGS ----- */

        flags.push_back(Flag("P", "gen-dfa-path",
                             "DFA Generation: Path to save generated DFA",
                             STRING, &global_settings::GEN_DFA_PATH));

        flags.push_back(Flag("O", "gen-dfa-states",
                             "DFA Generation: Number of states to generate",
                             INT, &global_settings::GEN_DFA_STATES));

        flags.push_back(Flag("o", "gen-dfa-symbols",
                             "DFA Generation: Number of symbols to generate",
                             INT, &global_settings::GEN_DFA_SYMBOLS));

        /* ------ OPTIMIZER SETTINGS ----- */

        flags.push_back(Flag("A", "tool-url",
                             "Path to file with DFA Tool",
                             STRING, &global_settings::TOOL_URL));

        flags.push_back(Flag("W", "word-url",
                             "Path to file with Words",
                             STRING, &global_settings::WORDS_PATH));

        flags.push_back(Flag("q", "state-min",
                             "Starting number of states in Optimizer",
                             INT, &global_settings::MIN_STATES));

        flags.push_back(Flag("Q", "state-max",
                             "Ending number of states in Optimizer",
                             INT, &global_settings::MAX_STATES));

        /* ------ PSO SETTINGS ----- */
        flags.push_back(Flag("I", "max-iter",
                             "Maximum iterations of PSO",
                             INT, &global_settings::MAX_ITER));

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

        flags.push_back(Flag("V", "max-vel",
                             "Max Velocity",
                             DOUBLE,
                             &global_settings::MAX_VELOCITY));

        flags.push_back(Flag("p", "pop-fac",
                             "Population Factor",
                             DOUBLE,
                             &global_settings::POPULATION_FACTOR));


        flags.push_back(Flag("f", "fit-tol",
                             "Fitness Tolerance",
                             DOUBLE,
                             &global_settings::FITNESS_TOLERANCE));

        flags.push_back(Flag("S", "swarm-size",
                             "Swarm size",
                             INT,
                             &global_settings::SWARM_SIZE));

        /* ------ THREADING ----- */

        flags.push_back(Flag("g", "d-thread-count",
                             "Default Thread Count - used only when system"
                                     " can't determine optimal number of "
                                     "threads",
                             INT,
                             &global_settings::DEFAULT_THREAD_COUNT));

        flags.push_back(Flag("G", "t-thread-count",
                             "True Thread Count - How many threads should be "
                                     "activated. If value is below 1 then "
                                     "Optimal number of threads will be chosen",
                             INT,
                             &global_settings::TRUE_THREAD_COUNT));


        /* ------ CLUSTERING ----- */

        flags.push_back(Flag("m", "km-tol",
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