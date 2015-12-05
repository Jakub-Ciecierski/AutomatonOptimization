//
// Created by jakub on 12/3/15.
//

#include <gtest/gtest.h>
#include "fuzzy_transition_function.h"
#include <word.h>
#include "dfa.h"
#include <clock.h>

//-----------------------------------------------------------//
//  DECLARATIONS
//-----------------------------------------------------------//

void fuzzyTransitionFunctionPrint();

void transitionFunctionTime();
unsigned int compute(const Word& w, TransitionFunction* dft);

//-----------------------------------------------------------//
//  DEFINITIONS
//-----------------------------------------------------------//

void fuzzyTransitionFunctionPrint(){
    unsigned int stateCount = 3;
    unsigned int symbolCount = 2;

    FuzzyTransitionFunction transitionFunction(stateCount, symbolCount);

    unsigned int fromState = 0;
    unsigned int symbol = 0;
    unsigned int toState = 1;

    float fuzziness = 1.0f;

    transitionFunction.addTransition(fromState, symbol, toState,
                                     fuzziness);

    for(unsigned int i = 0; i < symbolCount; i++){
        for(unsigned int j = 0; j < stateCount; j++){
            transitionFunction.addTransition(j, i, toState,
                                             fuzziness);
        }
    }

    std::cout << transitionFunction << std::endl;
}

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

TEST(Automaton, FuzzyTransitionFunction_PrintOut) {
    //transitionFunctionPrint();
}


TEST(Automaton, FuzzyTransitionFunction_AddTransition_ProperFazzyValue) {
    unsigned int stateCount = 3;
    unsigned int symbolCount = 2;

    FuzzyTransitionFunction transitionFunction(stateCount, symbolCount);

    unsigned int fromState = 0;
    unsigned int symbol = 0;
    unsigned int toState = 1;

    float fuzziness = 1.0f;

    transitionFunction.addTransition(fromState, symbol,
                                     toState,
                                     fuzziness);


    double actualValue = transitionFunction.getStateFazziness(fromState,
                                                              symbol,
                                                              toState);

    EXPECT_EQ(fuzziness, actualValue);
}

TEST(Automaton, TransitionFunction_AddTransition_CorrectState){
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


TEST(Automaton, DFA_ComputeWord_CorrectState){
    unsigned int stateCount = 4;
    unsigned int symbolCount = 2;

    TransitionFunction tf(stateCount, symbolCount);

    tf.addTransition(0, 0, 1);
    tf.addTransition(1, 0, 2);
    tf.addTransition(2, 0, 2);
    tf.addTransition(3, 0, 3);

    tf.addTransition(0, 1, 3);
    tf.addTransition(1, 1, 2);
    tf.addTransition(2, 1, 2);
    tf.addTransition(3, 1, 3);

    DFA dfa(tf);

    std::vector<int> word_entries{0,1,1};
    Word w(word_entries);

    int expectedState = 2;
    int actualState = dfa.compute(w);

    EXPECT_EQ(expectedState, actualState);

    std::vector<int> word_entries2{0};
    Word w2(word_entries2);

    expectedState = 1;
    actualState = dfa.compute(w2);

    EXPECT_EQ(expectedState, actualState);
}