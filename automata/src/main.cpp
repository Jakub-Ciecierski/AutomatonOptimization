#include "main.h"

#define LOG_TYPE ERROR_LOG

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "logger.h"
#include "standard_transition_t.h"
#include "per_symbol_transition_t.h"
#include "coded_transition_t.h"

int main(int argc, char* argv[]) {
    printf("Main starting...\n");

    if(argc != 2) {
        // TODO(dybisz) usage() function
        cout << "argc != 2\n";
        return EXIT_FAILURE;
    }
    string url = argv[1];
    CodedTransitionTable ctt(url);
    ctt.print();

    return EXIT_SUCCESS;
}
