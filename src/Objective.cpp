
#include "Objective.h"
#include "ObjectiveHelper.h"
#include "BoardList.h"

float Objective::iPenaltyFactor = 0;
float Objective::oPenaltyFactor = 0;
bool Objective::shouldPunish = true;

float Objective::objective(GAGenome & g){
    auto &genome = (GABin2DecGenome &) g;

    ObjectiveHelper o = ObjectiveHelper();

    std::vector<BoardLocation> boardLocationList = o.createBoardLocationList(genome);

    float sum = 0;
    
    for (int i = 0; i < BoardList::size(); ++i){

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

    return sum;
}