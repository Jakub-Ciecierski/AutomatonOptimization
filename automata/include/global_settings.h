//
// Created by dybisz on 11/12/15.
//

#ifndef AC_GLOBAL_SETTINGS_H
#define AC_GLOBAL_SETTINGS_H

#include <string>

// Few remarks about whole project:
// |--o   symbols take values from interval [1; _numberOfSymbols]
// |--o   states are marked by values from interval [1; _numberOfStates]

namespace global_settings {
    extern std::string TOOL_URL;
    extern int MIN_STATES;
    extern int MAX_STATES;
}


#endif //AC_GLOBAL_SETTINGS_H
