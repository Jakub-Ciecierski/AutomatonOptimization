//
// USAGE FOR NOW:
// LOG(message)
//
// REMARK: for now there is either no log or just errors.
//
// To provide simple macros for debugging/logging/error tracking.
// Created by dybisz on 11/11/15.
//

#ifndef AC_LOGGER_H
#define AC_LOGGER_H


static inline char* whitespaces(int);

// http://www.cplusplus.com/reference/cstring/strrchr/
//#define _FILE           strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__

// Available types of logging
#define NO_LOG          0
#define ERROR_LOG       1

// Tags for logging types
#define TAG_ERROR_LOG   "[ERROR]"

// By default there is no log
#ifndef LOG_TYPE
#define LOG_TYPE        ERROR_LOG
#endif

#define LENGTH(word)    sizeof(word)
#define SPACE(tag)      whitespaces(LENGTH(tag))

#define PRINT_FUNCTION(TAG, message) \
        std::cout << TAG << std::endl << \
                     SPACE(TAG) << "[file]:     " << __FILE__ << std::endl << \
                     SPACE(TAG) << "[function]: " << __PRETTY_FUNCTION__ << std::endl << \
                     SPACE(TAG) << "[line]:     " << __LINE__ << std::endl << \
                     SPACE(TAG) << "[message]:  " << message << std::endl;

#if LOG_TYPE == ERROR_LOG
#define LOG(message) PRINT_FUNCTION(TAG_ERROR_LOG, message)
#else
#define LOG(message)
#endif


static inline char *whitespaces(int length) {
    static char* buffer = new char[length +1];

    for(int i = 0; i < length ; i++) {
        buffer[i] = char(32);
    }
    buffer[length] = '\0';
    return buffer;
}


#endif //ACPROJECT_LOGGER_H
