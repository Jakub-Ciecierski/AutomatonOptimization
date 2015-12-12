//
// Created by kuba on 12/12/15.
//

#include <vector>
#include "words_gen_experiment.h"
#include "global_settings.h"
#include "words_generator.h"

namespace experiments
{
    void runWordsGenerationExperiment(){

        std::vector<int> alphabet(global_settings::GEN_WORDS_SYMBOL_COUNT);
        for(int i = 0; i < global_settings::GEN_WORDS_SYMBOL_COUNT; i++){
            alphabet[i] = i;
        }

        WordsGenerator wg(alphabet, global_settings::GEN_WORD_C,
                       global_settings::GEN_WORD_TRAIN_COUNT,
                       global_settings::GEN_WORD_TRAIN_MAX_LENGTH,
                       global_settings::GEN_WORD_TEST_COUNT,
                       global_settings::GEN_WORD_TEST_MAX_LENGTH);
    }
}