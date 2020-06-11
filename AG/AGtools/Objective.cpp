
#include "Objective.h"
#include "ObjectivePenalty.h"

float Objective::iPenaltyFactor = 0;
float Objective::oPenaltyFactor = 0;
bool Objective::shouldPunish = true;


std::vector<BoardLocation> Objective::createBoardLocationList(const GABin2DecGenome & g){
    std::vector<BoardLocation> boardLocationList = std::vector<BoardLocation>();

    for (int i = 0; i < g.nPhenotypes(); i+=4){
        boardLocationList.push_back( BoardLocation(g.phenotype(i), g.phenotype(i + 1), 
                    g.phenotype(i + 2), g.phenotype(i + 3)) );
    }

    return boardLocationList;
}

float Objective::objective(GAGenome & g){
    auto &genome = (GABin2DecGenome &) g;

    ObjectivePenalty o = ObjectivePenalty();

    std::vector<BoardLocation> boardLocationList = Objective::createBoardLocationList(genome);

    float sum = 0;
    
    for (int i = 0; i < BoardList::size(); ++i){
        if (!boardLocationList.at(i).checkBorders()){
            return 0;
        }
        if (!boardLocationList.at(i).exists()){
            continue;
        }

        sum += BoardList::get(i).getArea();

        float penalty = 0;

        // check if they are outside board
        penalty += Objective::oPenaltyFactor*o.outsidePenalty(BoardList::get(i), boardLocationList.at(i));

        // check intersection
        penalty += Objective::iPenaltyFactor*o.intersectionPenalty(i, boardLocationList);
        
        if (!shouldPunish && penalty > 0){
            return 0;
        } else {
            sum -= penalty;
        }
    }

    //std::cout << "OBJ " << sum << std::endl;
    return sum;
}
