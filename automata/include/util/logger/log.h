//
// Created by jakub on 11/22/15.
//

#ifndef AC_LOG_H
#define AC_LOG_H

#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#include "logger_settings.h"
#include "logger_engine.h"

namespace logger
{
    /*
     * Initiates the log functionality.
     */
    void initLog();

    void closeLog();

    // -------------------------------------------------------------------------

    /*
     * Logs arguments to default file and cout
     */
    template<typename T, typename... Args>
    inline void log(T t, Args... args)
    {
        settings::CURRENT_VERBOSE = settings::DEFAULT_VERBOSE;
        settings::CURRENT_VERBOSE_DEPTH = 0;

        engine::printVerboseAndTimeStamp(settings::DEFAULT_VERBOSE, 0);
        engine::recursivePrint(t, args...);


        settings::CURRENT_VERBOSE_DEPTH = 0;
    }

    /*
     * Logs arguments to File f, default file and cout
     */
    template<typename... Args>
    inline void log(File f, Args... args)
    {
        settings::CURRENT_VERBOSE = settings::DEFAULT_VERBOSE;
        settings::CURRENT_VERBOSE_DEPTH = 0;

        engine::openExtraFile(f.name);
        settings::EXTRA_FILE = f;

        engine::printVerboseAndTimeStamp(settings::DEFAULT_VERBOSE, 0);
        engine::recursivePrint(args...);

        engine::closeExtraFile();

        settings::CURRENT_VERBOSE_DEPTH = 0;
    }

    /*
     * Logs arguments to default file and cout
     */
    template<typename... Args>
    inline void log(Verbose verb, Args... args)
    {
        settings::CURRENT_VERBOSE = verb;
        settings::CURRENT_VERBOSE_DEPTH = 0;

        engine::printVerboseAndTimeStamp(verb, 0);
        engine::recursivePrint(args...);

        settings::CURRENT_VERBOSE_DEPTH = 0;
    }

    template<typename... Args>
    inline void log(File f, Verbose verb, Args... args)
    {
        settings::CURRENT_VERBOSE = verb;
        settings::CURRENT_VERBOSE_DEPTH = 0;

        engine::openExtraFile(f.name);
        settings::EXTRA_FILE = f;

        engine::printVerboseAndTimeStamp(verb, 0);
        engine::recursivePrint(args...);

        settings::CURRENT_VERBOSE_DEPTH = 0;

        engine::closeExtraFile();
    }

    template<typename... Args>
    inline void log(Verbose verb, File f, Args... args)
    {
        settings::CURRENT_VERBOSE = verb;
        settings::CURRENT_VERBOSE_DEPTH = 0;

        engine::openExtraFile(f.name);
        settings::EXTRA_FILE = f;

        engine::printVerboseAndTimeStamp(verb, 0);
        engine::recursivePrint(args...);

        settings::CURRENT_VERBOSE_DEPTH = 0;

        engine::closeExtraFile();
    }
/*
    template<typename... Args>
    inline void log(Verbose verb, File f, Args... args)
    {
        settings::CURRENT_VERBOSE = verb;
        settings::CURRENT_VERBOSE_DEPTH = 0;

        engine::openExtraFile(f.name);
        settings::EXTRA_FILE = f;

        engine::printVerboseAndTimeStamp(verb, 0);
        engine::recursivePrint(args...);

        settings::CURRENT_VERBOSE_DEPTH = 0;

        engine::closeExtraFile();
    }*/

    /*
    template<typename T1, typename T2, typename... Args>
    void log_test(T1 t1, T2 t2, Args... args)
    {
        settings::CURRENT_VERBOSE = settings::DEFAULT_VERBOSE;
        settings::CURRENT_VERBOSE_DEPTH = 0;
        int count = 0;

        // Found File
        if(std::is_same<T1, File>::value) {
            count++;

            engine::openExtraFile(t1.name);
            settings::EXTRA_FILE = t1;

            // Found Verbose
            if (std::is_same<T2, Verbose>::value) {
                count++;
                settings::CURRENT_VERBOSE = t2;
            }
        }
            // Found Verbose
        else if(std::is_same<T1, Verbose>::value) {
            count++;
            settings::CURRENT_VERBOSE = t2;

            // Found File
            if(std::is_same<T2, File>::value) {
                engine::openExtraFile(t1.name);
                settings::EXTRA_FILE = t1;
            }
        }

        engine::printVerboseAndTimeStamp(settings::CURRENT_VERBOSE, 0);

        if(count == 0)
            engine::recursivePrint(t1, t2, args...);
        if(count == 1)
            engine::recursivePrint(t2, args...);
        else if(count == 2)
            engine::recursivePrint(args...);

        settings::CURRENT_VERBOSE_DEPTH = 0;

    }
    */
}

#endif //AC_LOGGER2_H
