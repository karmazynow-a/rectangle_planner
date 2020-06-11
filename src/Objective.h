#pragma once

#include <ga/ga.h>

class Objective {
public:
    static float objective(GAGenome &);

    static float iPenaltyFactor;
    static float oPenaltyFactor;
    static bool shouldPunish;
};