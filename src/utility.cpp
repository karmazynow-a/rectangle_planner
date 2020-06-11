#include <iostream>

#include "utility.h"
#include "Objective.h"


GABin2DecPhenotype initPhenotype(const int N, const int W, const int H){

    GABin2DecPhenotype map;
    for (int i = 0; i < N; ++i) {
        map.add(12, 0, W);  // x coord
        map.add(12, 0, H);  // y coord
        map.add(1, 0, 1);   // rotate
        map.add(1, 0, 1);   // exist
    }

    return map;
}


void saveResults(GABin2DecGenome & g){
    std::fstream f ("output.txt", std::ios_base::out);

    // TODO jeszcze znalezione pole
    f << Objective::objective(g) << std::endl;

    for (int i = 0; i < BoardList::size(); ++i ){
        BoardLocation boardLocation (g.phenotype(i*4), g.phenotype(i*4 + 1), 
                    g.phenotype(i*4 + 2), g.phenotype(i*4 + 3));

        f << BoardList::get(i).getWidth() << " " 
            << BoardList::get(i).getHeight() << " "
            << boardLocation << std::endl;
    }

    f.close();
}

int mutator(GAGenome & g, float pm){
    return 1;
}