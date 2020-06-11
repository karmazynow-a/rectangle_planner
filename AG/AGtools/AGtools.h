#pragma once

#include <ga/ga.h>

#include "Objective.h"

/*******************************************************************************
 * Class with all necessary tools for algorithm execution - operators, objective, etc
 ******************************************************************************/
class AGtools {
public:
    static float objective(GAGenome & g) {return Objective::objective(g);}
    static void setObjectiveParams(const float&, const float&, const bool& );

    static int mutator(GAGenome & , float ); ///< Mutation operator

    static GABin2DecPhenotype initPhenotype(const int&, const int&, const int&);
};