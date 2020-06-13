#pragma once

#include <ga/ga.h>

#include "../Board/Board.h"
#include "../Board/BoardLocation.h"
#include "../Board/BoardList.h"

/*******************************************************************************
 * Class to calculate penalty on Boards when they are outside big board or intersect
 ******************************************************************************/
class ObjectivePenalty {
public:
    /*******************************************************************************
     * Penalty for being outside restricted area (big board)
     ******************************************************************************/
    float outsidePenalty(const Board &, const BoardLocation &);

    /*******************************************************************************
     * Penalty for intersecting with other boards
     ******************************************************************************/
    float intersectionPenalty(const int &, const std::vector<BoardLocation> & );

    /*******************************************************************************
     * Function to test if penalties are correct
     ******************************************************************************/
    friend void test();

private:
    /*******************************************************************************
     * Calculate intersection between two boards
     ******************************************************************************/
    float calculateIntersection (const Board &, const BoardLocation &, const Board &,
        const BoardLocation &);

    /*******************************************************************************
     * Check if boards are in cross position
     ******************************************************************************/
    float checkCrossing( const std::pair<int, int> & l1, const std::pair<int, int> & r1,
        const std::pair<int, int> & l2, const std::pair<int, int> & r2);

    /*******************************************************************************
     * Check if boards intersect in upper left / low right corner
     ******************************************************************************/
    float checkCorner1( const std::pair<int, int> & l1, const std::pair<int, int> & r1,
        const std::pair<int, int> & l2, const std::pair<int, int> & r2);

    /*******************************************************************************
     * Check if boards intersect in upper right / low left corner
     ******************************************************************************/
    float checkCorner2( const std::pair<int, int> & l1, const std::pair<int, int> & r1,
        const std::pair<int, int> & l2, const std::pair<int, int> & r2);

    /*******************************************************************************
     * Check if boards intersect on vertical side given b1 contains b2's side
     ******************************************************************************/
    float checkVerticalSide( const std::pair<int, int> & l1, const std::pair<int, int> & r1,
        const std::pair<int, int> & l2, const std::pair<int, int> & r2);

    /*******************************************************************************
     * Check if boards intersect on horizontal side given b1 contains b2's side
     ******************************************************************************/
    float checkHorizontalSide( const std::pair<int, int> & l1, const std::pair<int, int> & r1,
        const std::pair<int, int> & l2, const std::pair<int, int> & r2d);
};