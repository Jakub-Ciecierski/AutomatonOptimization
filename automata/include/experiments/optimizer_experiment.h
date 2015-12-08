//
// Created by jakub on 12/8/15.
//

#ifndef AC_OPTIMIZER_EXPERIMENT_H
#define AC_OPTIMIZER_EXPERIMENT_H


#include <optimizer.h>

namespace experiments
{

    void runOptimizerExperiment();

    namespace optimizer
    {
        /*
         * Summarizes the results of optimizer
         */
        void summarize(Optimizer &opt);
    }

}






#endif //AC_OPTIMIZER_EXPERIMENT_H
