//
// Created by jakub on 12/3/15.
//

#ifndef AC_TRANSITION_FUNCTION_H
#define AC_TRANSITION_FUNCTION_H

#include "matrix.h"
#include <vector>

/*
 * Transition Function is of the form:
 *      d: Q x E x Q -> [0, 1]
 *
 * More precisely, we ask a question what is the fuzziness of
 * transition for given state and symbol to another state.
 *
 * Example:
 *      (FromState, Symbol, ToState) = 0.6
 *      From FromState by Symbol, we can transition to ToState with 0.6
 *      fuzziness.
 *
 * Note:
 *      Value 0.0 means no transition at all
 *      Value 1.0 means full, standard transition.
 *
 * Determinism:
 *      If for each From_State and Symbol, we have exactly one To_State
 *      with value 1.0, then such transition function corresponds to
 *      Determinist Finite Automaton.
 *
 * Solution:
 *      Entries of Transition Function are constructed as follows:
 *          For each Symbol given is
 *          a Matrix of (stateCount x stateCount) size corresponding to
 *          transition for that symbol
 *
 */
class FuzzyTransitionFunction {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    // Number of states
    unsigned int stateCount;

    // Number of symbols
    unsigned int symbolCount;

    // Matrix of transitions for each symbol.
    // There are as many Matrices as Symbols.
    // Each matrix is of (stateCount x stateCount) size
    std::vector<Matrix<float>*> entries;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

public:

    /*
     * Create a Transition Function for stateCount and symbolCount
     */
    FuzzyTransitionFunction(unsigned stateCount, unsigned symbolCount);

    FuzzyTransitionFunction(const FuzzyTransitionFunction& tf);

    ~FuzzyTransitionFunction();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    const unsigned int& getStateCount() const;

    const unsigned int& getSymbolCount() const;

    const Matrix<float>* const getTransitionMatrix(unsigned symbol) const;

    /*
     * Adds a transition to Transition Function
     *
     * fromState x symbol x toState = fazziness
     */
    void addTransition(const unsigned int fromState,
                       const unsigned int symbol,
                       const unsigned int toState,
                       const float fazziness);

    /*
     * Returns the fazziness of given transition
     */
    float getStateFazziness(const unsigned int fromState,
                            const unsigned int symbol,
                            const unsigned int toState) const;

    //-----------------------------------------------------------//
    //  OPERATORS
    //-----------------------------------------------------------//

    friend std::ostream& operator<<(std::ostream& os,
                                    const FuzzyTransitionFunction& tf);
};


#endif //AC_TRANSITION_FUNCTION_H
