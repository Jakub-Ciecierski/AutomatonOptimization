//
// Created by jakub on 12/3/15.
//

#ifndef AC_DFA_T_H
#define AC_DFA_T_H

#include "word.h"

#include <ostream>
#include <vector>

#include "transition_function.h"

/*
 * Deterministic Finite Automaton - DFA
 *
 * DFA = (Q, E, d, q0, F)
 *  Q - set of states
 *  E - input alphabet
 *  d - Transition Function
 *  q0 - initial state
 *  F - set of accepting states.
 *
 *  Constructing DFA:
 *      1) Transition Function.
 *          - Must be built prior to constructing DFA instance
 *      2) Set of States
 *          - Determined based on Transition Function
 *      3) Input alphabet
 *          - Determined based on Transition Function
 *      4) Initial State
 *          - Default value: 0
 *      5) Set of Accepting
 *          - Can be empty.
 *
 */

class DFA {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    // Set of all accepting states
    std::vector<unsigned int>* acceptingStates;

    std::vector<int>* alphabet;

    // Transition Function
    TransitionFunction* transitionFunction;

    // Initial state
    unsigned int initialState;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

    void createAlphabet(unsigned int symbolCount);

    /*
     * Checks whether a DFA is in fact deterministic.
     * Throws invalid_argument exception if given Transition Function
     * does not yeild determinism
     */
    void checkDeterminism();

public:
    DFA(TransitionFunction* tf);

    DFA(TransitionFunction* tf, unsigned int initialState);

    DFA(const DFA & dfa);

    ~DFA();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    const TransitionFunction* getTransitionFunction() const;

    const std::vector<unsigned int>* getAcceptingStates() const;

    std::vector<int>* getAlphabet() const;

    const unsigned int& getStateCount() const;

    const unsigned int& getSymbolCount() const;

    const unsigned int& getInitialState() const;

    /*
     * Computes the given word.
     * Returns a state that automaton finished in
     */
    int compute(const Word& w) const;

    //-----------------------------------------------------------//
    //  OPERATORS
    //-----------------------------------------------------------//

    friend std::ostream& operator<<(std::ostream& os, const DFA & dfa);

};


#endif //AC_DFA_T_H
