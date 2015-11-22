//
// Created by jakub on 11/22/15.
//

#include "logger2.h"

#include <sys/stat.h>
#include <ctime>
#include <iostream>

#include "global_settings.h"

namespace logger {
    std::string fullDirStr;

    void initLog() {
        // Create main log dir
        if (mkdir(global_settings::LOG_MAIN_DIR.c_str(), 0777) < 0)
            if (errno !=EEXIST) ERR("mkdir");

        // Create current log dir
        std::string timeStr = currentDateString();
        fullDirStr = global_settings::LOG_CURR_DIR
                                 + "_" + timeStr;

        fullDirStr = global_settings::LOG_MAIN_DIR +
                     "/" + fullDirStr;
        if (mkdir(fullDirStr.c_str(), 0777) < 0)
            if (errno !=EEXIST) ERR("mkdir");

        std::cout << "Created Log file: " << fullDirStr << std::endl;
    }

    void log()

    std::string currentDateString() {
        time_t t = time(0);   // get time now
        struct tm *now = localtime(&t);
        std::string timeStr;

        timeStr += std::to_string(now->tm_year + 1900) + "-";
        timeStr += std::to_string(now->tm_mon + 1) + "-";
        timeStr += std::to_string(now->tm_mday);

        std::cout << timeStr << std::endl;

        return timeStr;
    }
}