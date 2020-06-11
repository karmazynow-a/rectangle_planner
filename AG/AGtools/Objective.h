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

    static std::vector<BoardLocation> createBoardLocationList(const GABin2DecGenome & g);

    static float iPenaltyFactor;                ///< Factor for intersection penalty
    static float oPenaltyFactor;                ///< Factor for outside the board penalty
    static bool shouldPunish;                   ///< In case of breaking the rules - should we add penalty or return value of objective as 0
};