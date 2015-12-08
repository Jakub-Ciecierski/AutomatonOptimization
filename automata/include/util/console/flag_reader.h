//
// Created by jakub on 11/10/15.
//

#ifndef AC_CONSOLE_H
#define AC_CONSOLE_H

#include <string>
#include <vector>
#include "flag.h"
#include "global_settings.h"
namespace console
{
/*
 * This module read flags from command line.
 *
 * You can either define new flag in a cool way inside
 * getFlags() function.
 * Or if you want a very custom flag that calls a function etc.
 * simply add it to readFlags(), like "--help"
 */

    /*
     * Read flags from the command line
     */
    void readFlags(int argc, char *argv[]);

    /*
     * Check if given flag has proper value
     * Error is stored in error
     */
    bool isError(int argc, char *argv[], int i, Flag flag, std::string &error);

    /*
     * Prints usages with what message
     */
    void usage(char *appName, const char *what);

    /*
     * Returns of developer defined flags
     */
    std::vector<Flag> getFlags();

}

#endif //AC_CONSOLE_H
