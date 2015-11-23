//
// Created by jakub on 11/23/15.
//

#include "flag.h"

namespace console {

    Flag::Flag(const char *short_f, const char *long_f) {
        this->short_f = SHORT_SIGN + short_f;
        this->long_f = LONG_SIGN + long_f;

        this->info = "";
    }

    Flag::Flag(const char *short_f, const char *long_f,
               const char *info, FlagType type, void *valueToChange) {
        this->short_f = SHORT_SIGN + short_f;
        this->long_f = LONG_SIGN + long_f;

        this->info = info;

        this->type = type;
        this->valueToChange = valueToChange;
    }

    Flag::Flag(const char *short_f, const char *long_f, const char *info) {
        this->short_f = SHORT_SIGN + short_f;
        this->long_f = LONG_SIGN + long_f;

        this->info = info;
    }

    void Flag::apply(char *value) {
        switch (type) {
            case INT:
                (*(int *) valueToChange) = atoi(value);
                break;
            case DOUBLE:
                (*(double *) valueToChange) = atof(value);
                break;
            case STRING:
                (*(std::string *) valueToChange) = value;
                break;
            case BOOL:
                (*(bool *) valueToChange) = true;
        }
    }
}