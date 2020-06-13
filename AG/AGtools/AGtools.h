#pragma once

#include <ga/ga.h>
#include <ga/GARealGenome.h>

#include "Objective.h"

/*******************************************************************************
 * Class with all necessary tools for algorithm execution - operators, objective, etc
 ******************************************************************************/
class AGtools {
public:
    /*******************************************************************************
     * Calculate objective of algorithm - sum of all areas minus penalties
     ******************************************************************************/
    static float objective(GAGenome& g) {return Objective::objective(g);}

    /*******************************************************************************
     * Set parameters for objective function, factor for intersection, being outside
     * penalties and if algorithm should punish or not
     ******************************************************************************/
    static void setObjectiveParams(const float&, const float&, const bool& );

    /*******************************************************************************
     * Create phenotype - prepare the genes
     ******************************************************************************/
    static GAAlleleSetArray<int> initPhenotype(const int&, const int&, const int&);

    /*******************************************************************************
     * Save results (objective, boards and its locations) to file
     ******************************************************************************/
    static void saveResults(GA1DArrayAlleleGenome<int> &);
};