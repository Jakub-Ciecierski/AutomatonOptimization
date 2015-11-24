//
// Created by jakub on 11/24/15.
//


#include <gtest/gtest.h>

//-----------------------------------------------------------//
//  DECLARATIONS
//-----------------------------------------------------------//

void test1(int& x);
void test2(int& x);

//-----------------------------------------------------------//
//  DEFINITIONS
//-----------------------------------------------------------//

void test1(int& x){
    x = 5;
}
void test2(int& x){
    x = 10;
}

TEST(cpp, Reference){
    int x = 20;

    test1(x);
    EXPECT_EQ(5, x);

    test2(x);
    EXPECT_EQ(10, x);
}