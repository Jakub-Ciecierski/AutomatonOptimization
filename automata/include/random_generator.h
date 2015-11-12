//
// Created by root on 11/12/15.
//

#ifndef AC_RANDOM_GENERATOR_H
#define AC_RANDOM_GENERATOR_H

#include <random>

namespace random_generator {

    void seed() {
        srand(time(NULL));
    }

    template<class T>
    T generateRandomNumber(T startRange, T endRange) {
        return startRange + (T) rand() / ((T) RAND_MAX / (T) (endRange - startRange));
    }
}

#endif //AC_RANDOM_GENERATOR_H
