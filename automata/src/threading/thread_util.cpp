//
// Created by jakub on 12/1/15.
//

#include <settings/global_settings.h>
#include "thread_util.h"

namespace threading
{
    void setTrueNumberOfThreads(){
        // If the user set value below 1, change it
        if(global_settings::TRUE_THREAD_COUNT < 1){
            global_settings::TRUE_THREAD_COUNT = getNumberOfCores();
            // If the system could not determine, choose the default value
            if(global_settings::TRUE_THREAD_COUNT < 1){
                global_settings::TRUE_THREAD_COUNT =
                        global_settings::DEFAULT_THREAD_COUNT;
            }
        }
    }

    int getNumberOfCores(){
        return std::thread::hardware_concurrency();
    }
}
