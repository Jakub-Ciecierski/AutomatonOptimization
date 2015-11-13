#include "main.h"

#define LOG_TYPE ERROR_LOG

#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include "logger.h"
#include "dfa.h"

int main(int argc, char *argv[]) {
    printf("Main starting...\n");

    if (argc != 2) {
        // TODO(dybisz) usage() function
        cout << "argc != 2\n";
        return EXIT_FAILURE;
    }
    string url = argv[1];

    //cout << res;
    return EXIT_SUCCESS;
}
