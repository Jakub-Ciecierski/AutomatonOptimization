#include <gtest/gtest.h>
#include "words_generator.h"
#include "word.h"
#include "pair_of_words.h"
#include <vector>
#include <iostream>

TEST(WordGenerator, Hamming_Distance){
    vector<int> _alphabet = {0, 1};
    vector<int> _w1Vec = {0, 1, 0, 1 ,1 , 1};
    vector<int> _w2Vec = {0, 0, 0, 1 ,0 , 1};
    Word _w1(_w1Vec);
    Word _w2(_w2Vec);

    WordsGenerator _wg(_alphabet);
    EXPECT_EQ(2, _wg.hammingDistance(_w1, _w2));

}

TEST(WordGenerator, Constructor_Training_Set_Count){
    vector<int> _alphabet = {0, 1};
    int _c = 3;
    int _trainSetCount = 30;
    int _trainSetMexLength = 100;
    int _testSetCount = 40;
    int _testSetMaxLength = 200;
    WordsGenerator _wg(_alphabet, _c, _trainSetCount, _trainSetMexLength,
                       _testSetCount, _testSetMaxLength);
    unsigned int _size = 30;
    EXPECT_EQ(_size, _wg._trainingSet.size());
}

TEST(WordGenerator, Constructor_Testing_Set_Count){
    vector<int> _alphabet = {0, 1};
    int _c = 3;
    int _trainSetCount = 30;
    int _trainSetMexLength = 100;
    int _testSetCount = 40;
    int _testSetMaxLength = 200;
    WordsGenerator _wg(_alphabet, _c, _trainSetCount, _trainSetMexLength,
                       _testSetCount, _testSetMaxLength);
    unsigned int _size = 40;
    EXPECT_EQ(_size, _wg._testingSet.size());
}
