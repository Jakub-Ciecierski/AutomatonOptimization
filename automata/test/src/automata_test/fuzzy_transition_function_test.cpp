//
// Created by jakub on 12/6/15.
//

#include <gtest/gtest.h>
#include "fuzzy_transition_function.h"

//-----------------------------------------------------------//
//  DECLARATIONS
//-----------------------------------------------------------//

void fuzzyTransitionFunctionPrint();


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

//-----------------------------------------------------------//
//  TESTS
//-----------------------------------------------------------//

TEST(Automata, FuzzyTransitionFunction_PrintOut) {
    //transitionFunctionPrint();
}


TEST(Automata, FuzzyTransitionFunction_AddTransition_ProperFazzyValue) {
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