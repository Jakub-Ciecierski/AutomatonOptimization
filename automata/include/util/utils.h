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
        if (!seeded) {
            srand(time(NULL));
            seeded = true;
        }
    }

    template<class T>
    inline std::vector<T> concatenateVector(std::vector<T> vec1, std::vector<T> vec2) {
        std::vector<T> vec12;
        vec12.reserve(vec1.size() + vec2.size());
        vec12.insert(vec12.end(), vec1.begin(), vec1.end());
        vec12.insert(vec12.end(), vec2.begin(), vec2.end());
        return vec12;
    }

    template<class T>
    inline std::vector<T> mergeVectors(std::vector<T> vec1, std::vector<T> vec2, std::vector<T> vec3) {
        std::vector<T> vec123;
        vec123.reserve(vec1.size() + vec2.size() + vec3.size());
        vec123.insert(vec123.end(), vec1.begin(), vec1.end());
        vec123.insert(vec123.end(), vec2.begin(), vec2.end());
        vec123.insert(vec123.end(), vec3.begin(), vec3.end());
        return vec123;
    }

    // TODO(dybisz) fix this shit
    // In case of int generation, make endRange++.
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
        for (int i = 0; i < size; i++) {
            output.push_back(-1);
        }
        return output;
    }
}

#endif //AC_RANDOM_GENERATOR_H
