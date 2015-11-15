//
// Created by jakub on 11/15/15.
//

#include <iostream>
#include "clock.h"

namespace clk
{
    // The time in seconds
    double g_prevSecond = -1;

    //-----------------------------------------------------------//

    /*
     * Starts the clock
     */
    void startClock(){
        g_prevSecond = currentSecond();
    }

    /*
     * Stops the clock.
     */
    double stopClock(){
        // If g_prevSecond was not initiated return -1
        if (g_prevSecond == -1)
            return -1;

        // Calculate delta time
        double currSecond = currentSecond();
        double delta = (currSecond - g_prevSecond);

        // Set the value back to -1
        g_prevSecond = -1;

        return delta;
    }

    void my_test(){
        std::cout << "my_test\n";
    }

    //-----------------------------------------------------------//

    /*
     * CurrentSecond()
     */
    /* WINDOWS */
    #if defined(_WIN32)
        #if !defined(WIN32_LEAN_AND_MEAN)
    #define WIN32_LEAN_AND_MEAN
    #endif
    #include <windows.h>
    double currentSecond(void)
    {
        LARGE_INTEGER t;
        static double oofreq;
        static int checkedForHighResTimer;
        static BOOL hasHighResTimer;

        if (!checkedForHighResTimer) {
            hasHighResTimer = QueryPerformanceFrequency(&t);
            oofreq = 1.0 / (double)t.QuadPart;
            checkedForHighResTimer = 1;
        }
        if (hasHighResTimer) {
            QueryPerformanceCounter(&t);
            return (double)t.QuadPart * oofreq;
        }
        else {
            return (double)GetTickCount();
        }
    }

    /* LINUX */
    #elif defined(__linux__) || defined(__APPLE__)

    #include <stddef.h>
    #include <sys/time.h>

    double currentSecond(void) {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        return (double) tv.tv_sec + (double) tv.tv_usec / 1000000.0;
    }

    /* UNKNOWN */
    #else
    #error unsupported platform
    #endif

    //-----------------------------------------------------------//
}