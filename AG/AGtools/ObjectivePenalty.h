#pragma once

#include <vector>
#include <ga/ga.h>

#include "../Board/Board.h"
#include "../Board/BoardLocation.h"
#include "../Board/BoardList.h"

/*******************************************************************************
 * Class to calculate penalty on Boards when they are outside big board or intersect
 ******************************************************************************/
class ObjectivePenalty {
public:
    int outsidePenalty(const Board &, const BoardLocation &);

    float intersectionPenalty(const int &, const std::vector<BoardLocation> & );

    std::vector<BoardLocation> createBoardLocationList(const GABin2DecGenome & g);

    void testIntersection();

private:
    float calculateIntersection (const Board &, const BoardLocation &, const Board &,
        const BoardLocation &);

    float checkCrossing( const std::pair<int, int> & l1, const std::pair<int, int> & r1,
        const std::pair<int, int> & l2, const std::pair<int, int> & r2);

    float checkCorner1( const std::pair<int, int> & l1, const std::pair<int, int> & r1,
        const std::pair<int, int> & l2, const std::pair<int, int> & r2);

    float checkCorner2( const std::pair<int, int> & l1, const std::pair<int, int> & r1,
        const std::pair<int, int> & l2, const std::pair<int, int> & r2);

    float checkVerticalSide( const std::pair<int, int> & l1, const std::pair<int, int> & r1,
        const std::pair<int, int> & l2, const std::pair<int, int> & r2, const int & height);

    float checkHorizontalSide( const std::pair<int, int> & l1, const std::pair<int, int> & r1,
        const std::pair<int, int> & l2, const std::pair<int, int> & r2, const int & height);
};