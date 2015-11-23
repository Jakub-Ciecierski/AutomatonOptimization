//
// Three types of verbose level available for now:
// NO_LOG               clear console - no messages
// ERROR_LOG            only errors are displayed
// INFO_LOG             info and errors are displayed
// DEBUG_LOG            info, errors and debug info are displayed
//
// Usage:
// LOG_ERROR(message)   prints error with [file]/[function]/[line]/[message] fields
// LOG_INFO(message)    prints errors and info with [message] field
// LOG_DEBUG(message)   prints info, error and debug with [file]/[function]/[line]/[message] fields;
//                      kind of info with all knowledge about origin
//
// Created by dybisz on 11/11/15.
//

#ifndef AC_LOGGER_H
#define AC_LOGGER_H

#include "color_text.h"

// Available types of logging
#define NO_LOG          0x00
#define ERROR_LOG       0x01
#define INFO_LOG        0x02
#define CALC_LOG        0x03
#define DEBUG_LOG       0x04

// Tags for logging types
#define TAG_ERROR_LOG   "[ERROR]"
#define TAG_INFO_LOG    "[INFO]"
#define TAG_DEBUG_LOG   "[DEBUG]"

// Set logging type
#ifndef LOG_TYPE
#define LOG_TYPE        CALC_LOG
#endif

#define RED_SPACE(word)     RED_BOLD_TEXT("   |-----o ")
#define BLUE_SPACE(word)    BLUE_BOLD_TEXT("   |-----o ")
#define GREEN_SPACE(word)   GREEN_BOLD_TEXT("   |-----o ")
#define FREE_SPACE          "           "

#define PRINT_ERROR(message)     \
        std::cout << RED_BOLD_TEXT(TAG_ERROR_LOG) << std::endl << \
                     RED_SPACE(TAG_ERROR_LOG) << "[file]:     " << __FILE__ << std::endl << \
                     RED_SPACE(TAG_ERROR_LOG) << "[function]: " << __PRETTY_FUNCTION__ << std::endl << \
                     RED_SPACE(TAG_ERROR_LOG) << "[line]:     " << __LINE__ << std::endl << \
                     RED_SPACE(TAG_ERROR_LOG) << "[message]:  " << message << std::endl;

#define PRINT_INFO(message) \
        std::cout << BLUE_BOLD_TEXT(TAG_INFO_LOG) << std::endl << \
                     BLUE_SPACE(TAG_INFO_LOG) << "[message]:  " << message << std::endl;

#define PRINT_CALC(tag, values) \
        std::cout << FREE_SPACE << "[" << tag << "]: " << values << std::endl;

#define PRINT_DEBUG(message) \
        std::cout << GREEN_BOLD_TEXT(TAG_DEBUG_LOG) << std::endl << \
                     GREEN_SPACE(TAG_DEBUG_LOG) << "[file]:     " << __FILE__ << std::endl << \
                     GREEN_SPACE(TAG_DEBUG_LOG) << "[function]: " << __PRETTY_FUNCTION__ << std::endl << \
                     GREEN_SPACE(TAG_DEBUG_LOG) << "[line]:     " << __LINE__ << std::endl << \
                     GREEN_SPACE(TAG_DEBUG_LOG) << "[message]:  " << message << std::endl;


#if LOG_TYPE >= ERROR_LOG
#define LOG_ERROR(message) PRINT_ERROR(message)
#else
#define LOG_ERROR(message)
#endif

#if LOG_TYPE >= INFO_LOG
#define LOG_INFO(message) PRINT_INFO(message)
#else
#define LOG_INFO(message)
#endif

#if LOG_TYPE >= CALC_LOG
#define LOG_CALC(tag, message) PRINT_CALC(tag, message)
#else
#define LOG_CALC(tag, message)
#endif

#if LOG_TYPE >= DEBUG_LOG
#define LOG_DEBUG(message) PRINT_DEBUG(message)
#else
#define LOG_DEBUG(message)
#endif

#endif //AC_LOGGER_H
