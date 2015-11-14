//
// Created by dybisz on 11/12/15.
//

#ifndef AC_RANDOM_GENERATOR_H
#define AC_RANDOM_GENERATOR_H

#include <random>
#include <vector>
#include <string>
#include <words_processing/word.h>
#include "word.h"

namespace utils {

    static bool seeded = false;

    inline void seed() {
        if(!seeded) {
            srand(time(NULL));
            seeded = true;
        }
    }

    template<class T>
    inline T generateRandomNumber(T startRange, T endRange) {
        return startRange + (T) rand() / ((T) RAND_MAX / (T) (endRange - startRange));
    }

    template<class T>
    inline std::string vectorToString(std::vector<T> vec) {
        std::string stringOut = "";
        for (auto i = vec.begin(); i != vec.end(); ++i) {
            stringOut += (std::to_string(*i) + " ");
        }
        return stringOut;
    }

    inline std::vector<int> initVectorOfMinusOnes(int size) {
        std::vector<int> output;
        for(int i = 0 ; i < size; i++) {
            output.push_back(-1);
        }
        return output;
    }
}

#endif //AC_RANDOM_GENERATOR_H
