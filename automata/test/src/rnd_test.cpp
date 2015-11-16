//
// Created by jakub on 11/14/15.
//


#include <gtest/gtest.h>

#include <vector>
#include <random>
#include <utils.h>
#include "random.h"

//-----------------------------------------------------------//
//  DECLARATIONS
//-----------------------------------------------------------//


//-----------------------------------------------------------//
//  DEFINITIONS
//-----------------------------------------------------------//

/*
 * Tests shows how to use random discrete distribution from
 * a vector of distributions.
 */
TEST(Random, Discrete_Distribution) {
    const int nrolls = 10000;

    std::vector<double> vec;
    vec.push_back(10);
    vec.push_back(5);
    vec.push_back(1);

    std::default_random_engine generator;
    std::discrete_distribution<> distribution (vec.begin(), vec.end());

    int p[3]={};

    for (int i=0; i < nrolls; ++i) {
        int number = distribution(generator);
        ++p[number];
    }
/*
    std::cout << "a discrete_distribution:" << std::endl;
    for (int i=0; i<3; ++i)
        std::cout << i << ": " << p[i] << std::endl;
    */
}

TEST(Random, Uniform_Real_Distribution) {
    int count, dim;
    double min, max;

    count = 100;
    dim = 10;
    min = 0.0f;
    max = 10.0f;

    rnd::uniformPoints(count, dim, min, max);
}

