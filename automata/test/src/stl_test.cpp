//
// Created by jakub on 11/10/15.
//

#include <gtest/gtest.h>

#include <vector>

TEST(STL, vector_iterator) {
    int expectedValue;
    std::vector<std::vector<int>> vec;

    std::vector<int> sub_vec1 = {1, 2, 3};
    std::vector<int> sub_vec2 = {4, 5, 6};
    std::vector<int> sub_vec3 = {7, 8 ,9};

    vec.push_back(sub_vec1);
    vec.push_back(sub_vec2);
    vec.push_back(sub_vec3);

    expectedValue = 1;

    for(std::vector<std::vector<int>>::iterator it = vec.begin(); it != vec.end(); it++){
        std::vector<int> sub_vec = *it;

        for(std::vector<int>::iterator it2 = sub_vec.begin(); it2 != sub_vec.end(); it2++) {
            int actualValue = *it2;

            EXPECT_EQ(expectedValue++, actualValue );
        }

    }
}