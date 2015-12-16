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
#include "point.h"
#include <math.h>
#include <stdexcept>

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

    template<class T>
    inline T generateRandomNumber(T startRange, T endRange) {
        return startRange + (T) rand() / ((T) RAND_MAX / (T) (endRange - startRange));
    }

    template<class T>
    inline std::string vectorToString(std::vector<T> vec) {
        std::string stringOut = "";
        for (auto i = vec.begin(); i != vec.end(); ++i) {
            stringOut += (std::to_string(*i));
            if (i != vec.end()-1)
                stringOut += ", ";
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

    template <class T>
    static double euclidianDistance(Point<T> p1, Point<T> p2) {
        Point<T> difference = p1 - p2;
        T result = 0;

        if (p1.size() != p2.size()){
            throw std::invalid_argument("The dimensions must match : utils.h");
        }

        for(int i = 0; i < p1.size(); i++) {
            result += difference[i] * difference[i];
        }

        return sqrt(result);
    }

    template <class T>
    static Point<T> generateRandomPoint(T dimensions, double min, double max) {
        Point<T> point;

        if (dimensions < 0){
            throw std::invalid_argument("The dimensions <0");
        }

        for(int i = 0; i < dimensions; i++) {
            point.addDimension(generateRandomNumber(min, max));
        }

        return point;
    }

//    static double power(double base, double exponent) {
//        return pow(base, exponent);
//    }
}

#endif //AC_RANDOM_GENERATOR_H
