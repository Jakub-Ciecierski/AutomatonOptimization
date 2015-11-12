#include "main.h"

#define LOG_TYPE ERROR_LOG

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "logger.h"
#include "transition_table.h"

int main(int argc, char* argv[]) {
    printf("Main starting...\n");

    if(argc != 2) {
        // TODO(dybisz) usage() function
        cout << "argc != 2\n";
        return EXIT_FAILURE;
    }
    string url = argv[1];
    TransitionTable tt;
    tt.loadFromFile(url);
    tt.print();
    return EXIT_SUCCESS;
}
