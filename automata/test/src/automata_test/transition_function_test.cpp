//
// Created by jakub on 12/6/15.
//

#include <gtest/gtest.h>

#include "transition_function.h"

#include "word.h"
#include "dfa.h"
#include "clock.h"


//-----------------------------------------------------------//
//  DECLARATIONS
//-----------------------------------------------------------//

void transitionFunctionTime();
unsigned int compute(const Word& w, TransitionFunction* dft);

//-----------------------------------------------------------//
//  DEFINITIONS
//-----------------------------------------------------------//

unsigned int compute(const Word& w,
                     TransitionFunction* dft){
    int len = w.length();

    unsigned int currentState = 0;

    // for each symbol
    for(int i = 0; i < len; i++){
        currentState = dft->getState(currentState, w[i]);
    }

    return currentState;
}

void transitionFunctionTime(){
    unsigned int stateCount = 100;
    unsigned int symbolCount = 5;

    unsigned int wordLength = 200;
    std::vector<int> w_entries(wordLength);
    Word w(w_entries);

    TransitionFunction transitionFunction(stateCount, symbolCount);

    for(unsigned int i = 0; i < symbolCount; i++){
        for(unsigned int j = 0; j < stateCount; j++){
            transitionFunction.addTransition(j, i, 0);
        }
    }

    const int wordCount = 1000;

    double time;

    clk::startClock();

    int count = 1;
    int iter = 0;
    while(iter++ < count)
        for(int i = 0; i < wordCount-1; i++){
            for(int j = i; j < wordCount; j++){
                compute(w, &transitionFunction);
            }
        }

    time = clk::stopClock();

    std::cout << "Word Count: " << wordCount << " Time: " << time << std::endl;
}

//-----------------------------------------------------------//
//  TESTS
//-----------------------------------------------------------//

TEST(Automata, TransitionFunction_AddTransition_CorrectState){
    unsigned int stateCount = 3;
    unsigned int symbolCount = 2;

    int fromState = 0;
    int symbol = 0;
    int expectedToState = 1;

    TransitionFunction tf(stateCount, symbolCount);

    tf.addTransition(fromState, symbol, expectedToState);

    int actualToState = tf.getState(fromState, symbol);

    EXPECT_EQ(expectedToState, actualToState);
}