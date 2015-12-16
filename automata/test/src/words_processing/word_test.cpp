#include <gtest/gtest.h>
#include "word.h"
#include <vector>

TEST(Word, Operators){
    vector<int> _testVec = {0, 5, 8, 2, 3};
    Word word(_testVec);
    int _last = word[4];
    EXPECT_EQ(3, _last);
}

TEST(Word, Appending_Symbol){
    Word word;
    word.appendSymbol(0);
    word.appendSymbol(1);
    word.appendSymbol(3);

    int _second = word[1];

    EXPECT_EQ(1, _second);
}

TEST(Word, Constructor_From_Vector){
    vector<int> _testVec = {0, 5, 2, 1, 3};
    Word word(_testVec);
    int _second = word[1];
    EXPECT_EQ(5, _second);
}

TEST(Word, Length){
    vector<int> _testVec = {0, 5, 2, 1, 3};
    Word word(_testVec);
    int _length = word.length();
    EXPECT_EQ(5, _length);
}

TEST(Word, Clear){
    vector<int> _testVec = {0, 5, 2, 1, 3};
    Word word(_testVec);
    word.clear();
    int _length = word.length();
    EXPECT_EQ(0, _length);
}
