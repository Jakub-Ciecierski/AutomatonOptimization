//
// Created by jakub on 11/22/15.
//

#ifndef AC_LOGGER2_H
#define AC_LOGGER2_H

#include "error.h"
#include <string>

namespace logger
{
    /*
     * Initiates the log functionality.
     */
    void initLog();

    /*
     * Gets current date in string
     */
    std::string currentDateString();
}

#endif //AC_LOGGER2_H
