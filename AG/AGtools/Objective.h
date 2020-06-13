#pragma once

#include <vector>
#include <ga/ga.h>

#include "../Board/BoardLocation.h"

/*******************************************************************************
 * Class to store static functions necessary for algorithm execution
 ******************************************************************************/
class Objective {
public:
    /*******************************************************************************
     * Calculate objective of gemone. It is equal to sum of small board's areas
     *  subtract the penalty - area outside the board and area of intersection.
     ******************************************************************************/
    static float objective(GAGenome &);

    /*******************************************************************************
     * Create list of board's locations based on genome.
     ******************************************************************************/
    static std::vector<BoardLocation> createBoardLocationList(const GA1DArrayAlleleGenome<int> & g);

    /*******************************************************************************
     * Factor for intersection between two boards penalty.
     ******************************************************************************/
    static float iPenaltyFactor;

    /*******************************************************************************
     * Factor for being outside the board penalty.
     ******************************************************************************/
    static float oPenaltyFactor;

    /*******************************************************************************
     * Flag that infroms whether we should add penalty (punish) for breaking the rules
     * or return value of objective as 0
     ******************************************************************************/
    static bool shouldPunish;
};