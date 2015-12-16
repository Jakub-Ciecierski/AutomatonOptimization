//
// Created by jakub on 12/3/15.
//

#include <gtest/gtest.h>
#include <algorithms/automata_algs.h>
#include <map>

//-----------------------------------------------------------//
//  DECLARATIONS
//-----------------------------------------------------------//

DFA* createDFA_s4_r2_unreach0();

DFA* createDFA_s5_r2_unreach1();

DFA* createDFA_s6_r2_unreach2();

DFA* createDFA_s6_r4_unreach3();

Word* createMediumWord_r2();
Word* createBigWord_r2();

Word* createMediumWord_r4();
Word* createBigWord_r4();

//-----------------------------------------------------------//
//  DEFINITIONS
//-----------------------------------------------------------//

DFA* createDFA_s5_r2_unreach0(){
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

DFA* createDFA_s5_r2_unreach1(){
    unsigned int stateCount = 5;
    unsigned int symbolCount = 2;

    TransitionFunction* tf = new TransitionFunction(stateCount, symbolCount);

    tf->addTransition(0, 0, 1);
    tf->addTransition(1, 0, 2);
    tf->addTransition(2, 0, 2);
    tf->addTransition(3, 0, 3);
    tf->addTransition(4, 0, 4);

    tf->addTransition(0, 1, 3);
    tf->addTransition(1, 1, 2);
    tf->addTransition(2, 1, 2);
    tf->addTransition(3, 1, 3);
    tf->addTransition(4, 1, 4);

    DFA* dfa = new DFA(tf);

    return dfa;
}

DFA* createDFA_s6_r2_unreach2(){
    unsigned int stateCount = 6;
    unsigned int symbolCount = 2;

    TransitionFunction* tf = new TransitionFunction(stateCount, symbolCount);

    tf->addTransition(0, 0, 1);
    tf->addTransition(1, 0, 2);
    tf->addTransition(2, 0, 2);
    tf->addTransition(3, 0, 3);
    tf->addTransition(4, 0, 4);
    tf->addTransition(5, 0, 4);

    tf->addTransition(0, 1, 3);
    tf->addTransition(1, 1, 2);
    tf->addTransition(2, 1, 2);
    tf->addTransition(3, 1, 3);
    tf->addTransition(4, 1, 4);
    tf->addTransition(5, 1, 5);

    DFA* dfa = new DFA(tf);

    return dfa;
}

DFA* createDFA_s6_r4_unreach3(){
    unsigned int stateCount = 6;
    unsigned int symbolCount = 4;

    TransitionFunction* tf =
            new TransitionFunction(stateCount, symbolCount);

    tf->addTransition(0, 0, 2);
    tf->addTransition(1, 0, 2);
    tf->addTransition(2, 0, 2);
    tf->addTransition(3, 0, 3);
    tf->addTransition(4, 0, 4);
    tf->addTransition(5, 0, 4);

    tf->addTransition(0, 1, 3);
    tf->addTransition(1, 1, 2);
    tf->addTransition(2, 1, 2);
    tf->addTransition(3, 1, 3);
    tf->addTransition(4, 1, 4);
    tf->addTransition(5, 1, 5);

    tf->addTransition(0, 2, 2);
    tf->addTransition(1, 2, 2);
    tf->addTransition(2, 2, 2);
    tf->addTransition(3, 2, 3);
    tf->addTransition(4, 2, 4);
    tf->addTransition(5, 2, 4);

    tf->addTransition(0, 3, 3);
    tf->addTransition(1, 3, 2);
    tf->addTransition(2, 3, 2);
    tf->addTransition(3, 3, 3);
    tf->addTransition(4, 3, 4);
    tf->addTransition(5, 3, 5);

    DFA* dfa = new DFA(tf);

    return dfa;
}

Word* createMediumWord_r2(){
    std::vector<int> word_entries{0,1,1};
    Word* w = new Word(word_entries);

    return w;
}
Word* createBigWord_r2(){
    std::vector<int> word_entries{0,1,1,0,1,0,1,1,1};
    Word* w = new Word(word_entries);

    return w;
}

Word* createMediumWord_r4(){
    std::vector<int> word_entries{0,3,1,2, 3};
    Word* w = new Word(word_entries);

    return w;
}
Word* createBigWord_r4(){
    std::vector<int> word_entries{0,2,3,3,1,0,2,3,3,1,1,2,3,0,1,1,0,1,0,1,1,1};
    Word* w = new Word(word_entries);

    return w;
}

//-----------------------------------------------------------//
//  TESTS
//-----------------------------------------------------------//

TEST(AutomataAlgorithms,
     RemoveUnreachableStates_DFA_s4_r2_unreach0_0StatesRemoved){
    DFA* dfa = createDFA_s5_r2_unreach0();

    unsigned int expectedunreachableCount = 0;
    unsigned int actualunreachableCount =
            automata::removeUnreachableStates(&dfa);

    delete dfa;

    EXPECT_EQ(expectedunreachableCount, actualunreachableCount);
}


TEST(AutomataAlgorithms,
     RemoveUnreachableStates_DFA_s5_r2_unreach1_1StatesRemoved){
    DFA* dfa = createDFA_s5_r2_unreach1();

    unsigned int expectedunreachableCount = 1;
    unsigned int actualunreachableCount =
            automata::removeUnreachableStates(&dfa);

    delete dfa;
    EXPECT_EQ(expectedunreachableCount, actualunreachableCount);
}


TEST(AutomataAlgorithms,
     RemoveUnreachableStates_DFA_s6_r2_unreach2_2StatesRemoved){
    DFA* dfa = createDFA_s6_r2_unreach2();

    unsigned int expectedunreachableCount = 2;
    unsigned int actualunreachableCount =
            automata::removeUnreachableStates(&dfa);

    delete dfa;
    EXPECT_EQ(expectedunreachableCount, actualunreachableCount);
}

TEST(AutomataAlgorithms,
     RemoveUnreachableStates_DFA_s6_r4_unreach3_3StatesRemoved){
    DFA* dfa = createDFA_s6_r4_unreach3();

    unsigned int expectedunreachableCount = 3;
    unsigned int actualunreachableCount =
            automata::removeUnreachableStates(&dfa);

    delete dfa;
    EXPECT_EQ(expectedunreachableCount, actualunreachableCount);
}

TEST(AutomataAlgorithms,
     RemoveUnreachableStates_DFA_s6_r2_unreach2_ComputesSameMediumWord){
    DFA* dfa = createDFA_s6_r2_unreach2();

    Word* w = createMediumWord_r2();

    int expectedState = dfa->compute(*w);
    automata::removeUnreachableStates(&dfa);
    int actualState = dfa->compute(*w);

    delete w;
    delete dfa;

    EXPECT_EQ(expectedState, actualState);
}

TEST(AutomataAlgorithms,
     RemoveUnreachableStates_DFA_s6_r2_unreach2_ComputesSameBigWord){
    DFA* dfa = createDFA_s6_r2_unreach2();

    Word* w = createBigWord_r2();

    int expectedState = dfa->compute(*w);
    automata::removeUnreachableStates(&dfa);
    int actualState = dfa->compute(*w);

    delete w;
    delete dfa;
    EXPECT_EQ(expectedState, actualState);
}


TEST(AutomataAlgorithms,
      RemoveUnreachableStates_DFA_s6_r4_unreach3_ComputesSameMediumWord){
    DFA* dfa = createDFA_s6_r4_unreach3();
    Word* w = createMediumWord_r4();

    int preReductionState = dfa->compute(*w);

    std::vector<unsigned int>* reachibilityFlags =
                        automata::getReachabilityFlags(dfa);
    std::map<int, int>* mapping =
                        automata::reduceDFA(&dfa, reachibilityFlags);

    int actualState = dfa->compute(*w);
    int expectedState = (*mapping)[preReductionState];

    delete reachibilityFlags;
    delete mapping;
    delete w;
    delete dfa;

    EXPECT_EQ(expectedState, actualState);
}

TEST(AutomataAlgorithms,
     RemoveUnreachableStates_DFA_s6_r4_unreach3_ComputesSameBigWord){
    DFA* dfa = createDFA_s6_r4_unreach3();
    Word* w = createBigWord_r4();

    int preReductionState = dfa->compute(*w);

    std::vector<unsigned int>* reachibilityFlags =
                    automata::getReachabilityFlags(dfa);
    std::map<int, int>* mapping =
                    automata::reduceDFA(&dfa, reachibilityFlags);

    int actualState = dfa->compute(*w);
    int expectedState = (*mapping)[preReductionState];

    delete reachibilityFlags;
    delete mapping;
    delete w;
    delete dfa;

    EXPECT_EQ(expectedState, actualState);
}

