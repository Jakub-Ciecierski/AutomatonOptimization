//
// Created by jakub on 12/3/15.
//

#include <gtest/gtest.h>

#include "transition_function.h"
#include "word.h"
#include "dfa.h"


//-----------------------------------------------------------//
//  DECLARATIONS
//-----------------------------------------------------------//

DFA* createDFA();

//-----------------------------------------------------------//
//  DEFINITIONS
//-----------------------------------------------------------//

DFA* createDFA(){
    unsigned int stateCount = 4;
    unsigned int symbolCount = 2;

    TransitionFunction* tf = new TransitionFunction(stateCount, symbolCount);

    tf->addTransition(0, 0, 1);
    tf->addTransition(1, 0, 2);
    tf->addTransition(2, 0, 2);
    tf->addTransition(3, 0, 3);

    tf->addTransition(0, 1, 3);
    tf->addTransition(1, 1, 2);
    tf->addTransition(2, 1, 2);
    tf->addTransition(3, 1, 3);

    DFA* dfa = new DFA(tf);

    return dfa;
}

//-----------------------------------------------------------//
//  TESTS
//-----------------------------------------------------------//

TEST(Automata, DFA_ComputeMediumWord_CorrectState){
    DFA* dfa = createDFA();

    std::vector<int> word_entries{0,1,1};
    Word w(word_entries);

    int expectedState = 2;
    int actualState = dfa->compute(w);

    EXPECT_EQ(expectedState, actualState);

    delete dfa;
}


TEST(Automata, DFA_ComputeSmallWord_CorrectState){
    DFA* dfa = createDFA();

    std::vector<int> word_entries2{0};
    Word w2(word_entries2);

    int expectedState = 1;
    int actualState = dfa->compute(w2);

    EXPECT_EQ(expectedState, actualState);

    delete dfa;
}