//
// Created by jakub on 12/3/15.
//

#ifndef AC_TRANSITION_FUNCTION_H
#define AC_TRANSITION_FUNCTION_H

#include <vector>
#include <iostream>

/*
 * Transition Function is of the form known as Natural Decoding. Formally:
 *      - Transitions are stored in a virtual 2D array - physically 1D.
 *      - First stateCount entries or simply first row,
 *          represent transitions for consecutive states for first symbol.
 *      - Symbols are enumerated: 0, 1, ... , (symbolCount-1)
 *      - States are enumerated: 0, 1, ... , (stateCount-1)
 *      - Negative values represent undefined transition.
 * Example:
 *      [[0, 1, 2], [1, 2, 1]]
 *
 *      - First row represent transition for first symbol (e.g. a)
 *      - d(a, 0) = 0
 *      - d(a, 1) = 1
 *      - d(a, 2) = 2
 *      - Second row represent transition for second symbol (e.g. b)
 *      - d(b, 0) = 1
 *      - d(b, 1) = 2
 *      - d(b, 2) = 1
 */
class TransitionFunction {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    // Number of states
    unsigned int stateCount;

    // Number of symbols
    unsigned int symbolCount;

    std::vector<int> entries;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

    /*
     * Gets index to entries corresponding to given transition
     */
    unsigned int getIndex(const unsigned int state,
                          const unsigned int symbol) const;

public:
    TransitionFunction(unsigned int stateCount,
                        unsigned int symbolCount);

    TransitionFunction(unsigned int stateCount,
                        unsigned int symbolCount,
                        std::vector<int> entries);

    TransitionFunction(const TransitionFunction& tf);

    ~TransitionFunction();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    const unsigned int& getStateCount() const;

    const unsigned int& getSymbolCount() const;

    /*
     * Returns a state as according to transition function.
     */
    int getState(const unsigned int fromState,
                 const unsigned int symbol) const;

    /*
     * Adds a Transition fromState, symbol toState
     */
    void addTransition( const unsigned int fromState,
                        const unsigned int symbol,
                        const unsigned int toState);

    //-----------------------------------------------------------//
    //  OPERATORS
    //-----------------------------------------------------------//

    friend std::ostream& operator<<(std::ostream& os,
                                    const TransitionFunction& tf);
};


#endif //AC_TRANSITION_FUNCTION_H
