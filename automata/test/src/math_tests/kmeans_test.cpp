//
// Created by jakub on 11/10/15.
//

#include <gtest/gtest.h>
#include <vector>

#include "kmeans.h"
#include <iostream>

TEST(KMeans, GetK_GetMaxIter_GetTol) {
    int expected_k, actual_k;
    int expected_max_iter, actual_max_iter;
    double expected_tol, actual_tol;

    actual_k = 4;
    actual_max_iter = 20;
    actual_tol = 0.001;

    KMeans<int> km(actual_k, actual_tol, actual_max_iter);

    expected_k = km.getK();
    expected_max_iter = km.getMaxIter();
    expected_tol = km.getTol();

    EXPECT_EQ(expected_k, actual_k);
    EXPECT_EQ(expected_max_iter, actual_max_iter);
    EXPECT_EQ(expected_tol, actual_tol);
}


TEST(KMeans, Set_Data) {

}
