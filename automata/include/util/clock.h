//
// Created by jakub on 11/15/15.
//

#ifndef AC_CLOCK_H
#define AC_CLOCK_H
/*
 * Provides a cross platform solution to time measurement.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

namespace clk
{
    /*
     * Starts the clock. sets the value of currSecond to current second
     */
    void startClock();

    /*
     * Stops the clock and returns the time length in seconds
     * between last startClock
     * or -1 if stopClock was called before startClock.
     */
    double stopClock();

    /*
     * Returns current second from the system.
     */
    double currentSecond();
}

#endif //AC_CLOCK_H
