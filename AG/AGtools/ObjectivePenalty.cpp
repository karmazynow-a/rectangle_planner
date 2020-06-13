
#include <cmath>
#include <cassert>  

#include "ObjectivePenalty.h"

float ObjectivePenalty::outsidePenalty(const Board & board, const BoardLocation & boardLocation){
    if (!boardLocation.exists()){
        return 0;
    }

    float sum = 0;

    int dimX = boardLocation.rotated()
        ? boardLocation.getX() + board.getHeight()
        : boardLocation.getX() + board.getWidth();

    int dimY = boardLocation.rotated()
        ? boardLocation.getY() + board.getWidth()
        : boardLocation.getY() + board.getHeight();

    int width = boardLocation.rotated()
        ? board.getHeight()
        : board.getWidth();
    
    int height = boardLocation.rotated()
        ? board.getWidth()
        : board.getHeight();

    if ( dimX > BoardLocation::maxWidth){
        sum += height * std::fabs(dimX - BoardLocation::maxWidth);
    }

    if ( dimY > BoardLocation::maxHeight){
        sum += width * std::fabs(dimY - BoardLocation::maxHeight);
    }

    return sum*sum;
}

float ObjectivePenalty::intersectionPenalty(const int & boardIndex, 
    const std::vector<BoardLocation> & boardLocationList ){

    if (!boardLocationList.at(boardIndex).exists()){
        return 0;
    }

    float sum = 0;
    for (int i = boardIndex + 1; i < BoardList::size(); ++i){
        sum += calculateIntersection(BoardList::get(boardIndex), boardLocationList.at(boardIndex),
            BoardList::get(i), boardLocationList.at(i) );
    }

    return sum*sum;
}

float ObjectivePenalty::calculateIntersection (const Board & b1, const BoardLocation & b1Loc, 
    const Board & b2, const BoardLocation & b2Loc ){

    if ( !b1Loc.exists() || !b2Loc.exists() ){
        return 0;
    }

    auto l1 = std::make_pair(b1Loc.getX(), b1Loc.getY());
    auto l2 = std::make_pair(b2Loc.getX(), b2Loc.getY());

    auto r1 = b1Loc.rotated() 
            ? std::make_pair(b1Loc.getX() + b1.getHeight(), b1Loc.getY() + b1.getWidth())
            : std::make_pair(b1Loc.getX() + b1.getWidth(), b1Loc.getY() + b1.getHeight());

    auto r2 = b2Loc.rotated()
            ? std::make_pair(b2Loc.getX() + b2.getHeight(), b2Loc.getY() + b2.getWidth())
            : std::make_pair(b2Loc.getX() + b2.getWidth(), b2Loc.getY() + b2.getHeight());

    if ( (l2.first >= r1.first) || (l1.first >= r2.first)||
        (l2.second >= r2.second || l1.second >= r2.second)){
        return 0;
    }

    // b1 inside b2
    if (l1.first > l2.first && l1.second > l2.second 
        && r1.first < r2.first && r1.second < r2.second){
        return b1.getArea();
    }

    // b2 inside b1
    if (l2.first > l1.first && l2.second > l1.second 
        && r2.first < r1.first && r2.second < r1.second){
        return b2.getArea();
    }

    float sum = 0;

    sum += checkCrossing(l1, r1, l2, r2);
    sum += checkCrossing(l2, r2, l1, r1);

    if (sum > 0) return sum;
    sum += checkHorizontalSide(l1, r1, l2, r2);
    sum += checkHorizontalSide(l2, r2, l1, r1);
    sum += checkVerticalSide(l1, r1, l2, r2);
    sum += checkVerticalSide(l2, r2, l1, r1);

    if (sum > 0) return sum;

    sum += checkCorner1(l1, r1, l2, r2);
    sum += checkCorner1(l2, r2, l1, r1);
    sum += checkCorner2(l1, r1, l2, r2);
    sum += checkCorner2(l2, r2, l1, r1);

    return sum;
}

float ObjectivePenalty::checkCrossing( const std::pair<int, int> & l1, const std::pair<int, int> & r1,
    const std::pair<int, int> & l2, const std::pair<int, int> & r2){

    if (l1.first <= l2.first && r1.first >= r2.first
        && l2.second <= l1.second && r2.second >= r1.second){
            return std::fabs(l1.second - r1.second) * std::fabs(l2.first - r2.first);
    }
    return 0;
}

// r1 crosses r2's upper left corner 
// same as r2 crosses r1 lower right corner
float ObjectivePenalty::checkCorner1( const std::pair<int, int> & l1, const std::pair<int, int> & r1,
    const std::pair<int, int> & l2, const std::pair<int, int> & r2){

    if ( r1.first > l2.first && r1.second > l2.second
        && r1.first < r2.first && r1.second < r2.second){
        return std::fabs(r1.first - l2.first) * std::fabs(r1.second - l2.second);
    }
    return 0;
}

// r1 crosses r2's upper right corner 
// same as r2 crosses r1 lower left corner
float ObjectivePenalty::checkCorner2( const std::pair<int, int> & l1, const std::pair<int, int> & r1,
    const std::pair<int, int> & l2, const std::pair<int, int> & r2){

   if ( r2.first < r1.first && r2.first > l1.first 
        && l2.second < r1.second && l2.second > l1.second){
        return std::fabs(l1.first - r2.first) * std::fabs(r1.second - l2.second);
    }
    return 0;
}

// b2 crosses b1's vertical side
float ObjectivePenalty::checkVerticalSide( const std::pair<int, int> & l1, const std::pair<int, int> & r1,
    const std::pair<int, int> & l2, const std::pair<int, int> & r2){

    if ( l1.second <= l2.second && r1.second >= r2.second){

        if (l1.first <= r2.first && r1.first >= r2.first){
            return std::fabs(l2.second - r2.second) * std::fabs(l1.first - r2.first);
        }

        if (l1.first <= l2.first && r1.first >= l2.first){
            return std::fabs(l2.second - r2.second) * std::fabs(l2.first - r1.first);
        }
    }

    return 0;
}

// b2 crosses b1's horizontal side
float ObjectivePenalty::checkHorizontalSide( const std::pair<int, int> & l1, const std::pair<int, int> & r1,
    const std::pair<int, int> & l2, const std::pair<int, int> & r2){

    if ( l1.first <= l2.first && r1.first >= r2.first){
        if (l1.second <= r2.second && r1.second >= r2.second){
            return std::fabs(l2.first - r2.first) * std::fabs(l1.second - r2.second);
        }

        if (l1.second <= l2.second && r1.second >= l2.second){
            return std::fabs(l2.first - r2.first) * std::fabs(l2.second - r1.second);
        }
    }

    return 0;
}
