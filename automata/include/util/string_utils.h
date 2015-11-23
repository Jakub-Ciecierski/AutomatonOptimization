//
// Created by jakub on 11/23/15.
//

#ifndef AC_STRING_UTILS_H
#define AC_STRING_UTILS_H

#include <string>
#include <vector>

namespace str_util
{
    /*
     * Splits the string s into tokens, substrings which
     * are seperated by delimiter.
     */
    std::vector<std::string> splitString(std::string s,
                                         std::string delimiter);
}


#endif //AC_STRING_UTILS_H