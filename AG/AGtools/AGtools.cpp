
#include "AGtools.h"

void AGtools::setObjectiveParams(const float& iPenaltyFactor, const float& oPenaltyFactor, const bool& shouldPunish){
    Objective::iPenaltyFactor = iPenaltyFactor;
    Objective::oPenaltyFactor = oPenaltyFactor;
    Objective::shouldPunish = shouldPunish;
}

int AGtools::mutator(GAGenome & g, float pm){
    return 1;
}

GABin2DecPhenotype AGtools::initPhenotype(const int& N, const int& W, const int& H){

    GABin2DecPhenotype map;
    for (int i = 0; i < N; ++i) {
        // temprorary - to have integers
        // kinda bad style, but thats temp solution
        
        map.add(12, 0, 4095);  // x coord
        map.add(12, 0, 4095);  // y coord
        map.add(1, 0, 1);   // rotate
        map.add(1, 0, 1);   // exist
    }

    return map;
}