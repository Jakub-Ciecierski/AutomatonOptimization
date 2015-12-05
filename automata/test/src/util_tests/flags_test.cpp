//
// Created by jakub on 11/15/15.
//

#include <gtest/gtest.h>
#include "flag_reader.h"

//-----------------------------------------------------------//
//  DECLARATIONS
//-----------------------------------------------------------//


//-----------------------------------------------------------//
//  DEFINITIONS
//-----------------------------------------------------------//



//-----------------------------------------------------------//
//  TESTS
//-----------------------------------------------------------//

TEST(Console, NoFlagsHaveTheSameShortAndLongValue) {
    std::vector<console::Flag> flags = console::getFlags();
    unsigned int size = flags.size();
    for(unsigned int i = 0; i < size-1; i++){
        for(unsigned int j = i+1; j < size; j++){
            console::Flag flag1 = flags[i];
            console::Flag flag2 = flags[j];

            EXPECT_NE(flag1.short_f, flag2.short_f);
            EXPECT_NE(flag1.long_f, flag2.long_f);
        }
    }
}
