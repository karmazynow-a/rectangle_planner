
#include "utility.h"


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
    f << objective(g) << std::endl;

    for (int i = 0; i < BoardList::size(); ++i ){
        BoardLocation boardLocation (g.phenotype(i*4), g.phenotype(i*4 + 1), 
                    g.phenotype(i*4 + 2), g.phenotype(i*4 + 3));

        f << BoardList::get(i).getWidth() << " " 
            << BoardList::get(i).getHeight() << " "
            << boardLocation << std::endl;
    }

    f.close();
}

float objective(GAGenome & g){
    auto &genome = (GABin2DecGenome &) g;

    ObjectiveHelper o = ObjectiveHelper();

    std::vector<BoardLocation> boardLocationList = o.createBoardLocationList(genome);

    double sum = 0;
    
    for (int i = 0; i < BoardList::size(); ++i){
        sum += BoardList::get(i).getArea();

        // check if they are outside board
        sum -= o.outsidePenalty(BoardList::get(i), boardLocationList.at(i));

        // check intersection
        sum -= o.intersectionPenalty(i, boardLocationList);
    }

    float s = sum/100000.0; 

    return s;
}

int mutator(GAGenome & g, float pm){
    return 1;
}