#ifndef AC_MAIN_H
#define AC_MAIN_H


#define LOG_TYPE ERROR_LOG

#include <iostream>
#include <stdio.h>
#include <vector>
#include "random_generator.h"
#include "global_settings.h"

int main(int argc, char *argv[]) {
    printf("Main starting...\n");

    if (argc != 2) {
        // TODO(dybisz) usage() function
        cout << "argc != 2\n";
        return EXIT_FAILURE;
    }
    global_settings::TOOL_URL = argv[1];

    return EXIT_SUCCESS;
}

#endif //AC_STANDARD_TRANSITION_T_H