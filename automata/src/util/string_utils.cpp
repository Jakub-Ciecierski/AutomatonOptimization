//
// Created by jakub on 11/23/15.
//

#include "string_utils.h"

namespace str_util
{

    std::vector<std::string> splitString(std::string s,
                                         std::string delimiter) {
        std::vector<std::string> tokens;

        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            tokens.push_back(token);
            s.erase(0, pos + delimiter.length());
        }
        tokens.push_back(s);
        return tokens;
    }
}