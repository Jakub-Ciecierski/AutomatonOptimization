//
// Created by jakub on 11/23/15.
//

#ifndef AC_FLAG_H
#define AC_FLAG_H

#include <string>

namespace console
{

    enum FlagType {
        INT,
        DOUBLE,
        STRING,
        BOOL
    };

/*
 * Flag class encapsulates the console flag.
 * Contains its short and long version,
 * as well as short info to be printed in usage.
 */
    class Flag {
    private:
        const std::string SHORT_SIGN = "-";
        const std::string LONG_SIGN = "--";

    public:
        Flag(const char *short_f, const char *long_f);

        Flag(const char *short_f, const char *long_f,
             const char *info, FlagType type, void *valueToChange);

        Flag(const char *short_f, const char *long_f, const char *info);

        void apply(char *value);

        std::string short_f;
        std::string long_f;
        std::string info;
        FlagType type;

        void *valueToChange;
    };
}
#endif //AC_FLAG_H
