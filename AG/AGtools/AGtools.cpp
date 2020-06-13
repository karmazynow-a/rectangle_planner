#include <algorithm>

#include "AGtools.h"
#include "../Board/BoardList.h"
#include "../Board/BoardLocation.h"

void AGtools::setObjectiveParams(const float& iPenaltyFactor, const float& oPenaltyFactor, const bool& shouldPunish){
    Objective::iPenaltyFactor = iPenaltyFactor;
    Objective::oPenaltyFactor = oPenaltyFactor;
    Objective::shouldPunish = shouldPunish;
}

GAAlleleSetArray<int> AGtools::initPhenotype(const int& N, const int& W, const int& H){

    GAAlleleSetArray<int> map;
    for (int i = 0; i < N; ++i) {
        map.add(0, W);  // x coord
        map.add(0, H);  // y coord
        map.add(0, 1);   // rotate
        map.add(0, 1);   // exist
    }

    return map;
}

void AGtools::saveResults(GA1DArrayAlleleGenome<int> & g){
    std::fstream f ("output.txt", std::ios_base::out);

    f << AGtools::objective(g) << std::endl;

    for (int i = 0; i < BoardList::size(); ++i ){
        BoardLocation boardLocation (g.gene(i*4), g.gene(i*4 + 1), 
                    g.gene(i*4 + 2), g.gene(i*4 + 3));

        f << BoardList::get(i).getWidth() << " " 
            << BoardList::get(i).getHeight() << " "
            << boardLocation << std::endl;
    }

    f.close();
}