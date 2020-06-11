
#include <cmath>

#include "ObjectiveHelper.h"

int ObjectiveHelper::outsidePenalty(const Board & board, const BoardLocation & boardLocation){
    if (!boardLocation.exists()){
        //std::cout << "BYE" << std::endl;
        return 0;
    }

    int W = 2800, H = 2070;
    int sum = 0;

    int dimX = boardLocation.rotated()
        ? boardLocation.getX() + board.getHeight()
        : boardLocation.getX() + board.getWidth();

    int dimY = boardLocation.rotated()
        ? boardLocation.getY() + board.getWidth()
        : boardLocation.getY() + board.getHeight();

    if ( dimX > W){
        sum += board.getHeight() * std::fabs(dimX - W);
    }

    if ( dimY > H){
        sum += board.getWidth() * std::fabs(dimY - H);
    }

    return sum;
}

float ObjectiveHelper::intersectionPenalty(const int & boardIndex, 
    const std::vector<BoardLocation> & boardLocationList ){

    float sum = 0;
    for (int i = boardIndex + 1; i < BoardList::size(); ++i){
        sum += calculateIntersection(BoardList::get(boardIndex), boardLocationList.at(boardIndex),
            BoardList::get(i), boardLocationList.at(i) );
    }

    return sum;
}

std::vector<BoardLocation> ObjectiveHelper::createBoardLocationList(const GABin2DecGenome & g){
    std::vector<BoardLocation> boardLocationList = std::vector<BoardLocation>();

    for (int i = 0; i < BoardList::size(); ++i){
        boardLocationList.push_back( BoardLocation(g.phenotype(i*4), g.phenotype(i*4 + 1), 
                    g.phenotype(i*4 + 2), g.phenotype(i*4 + 3)) );
    }

    return boardLocationList;
}

float ObjectiveHelper::calculateIntersection (const Board & b1, const BoardLocation & b1Loc, 
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

    // b1 b2 crossing
    float sum = 0;

    sum += checkCrossing(l1, r1, l2, r2);
    sum += checkCrossing(l2, r2, l1, r1);

    if (sum > 0) return sum;

    sum += checkHorizontalSide(l1, r1, l2, r2, b1.getWidth());
    sum += checkHorizontalSide(l2, r2, l1, r1, b2.getWidth());
    sum += checkVerticalSide(l1, r1, l2, r2, b1.getHeight());
    sum += checkVerticalSide(l2, r2, l1, r1, b2.getHeight());

    if (sum > 0) return sum;

    // rogi
    sum += checkCorner1(l1, r1, l2, r2);
    sum += checkCorner1(l2, r2, l1, r1);
    sum += checkCorner2(l1, r1, l2, r2);
    sum += checkCorner2(l2, r2, l1, r1);

    return sum;
}

float ObjectiveHelper::checkCrossing( const std::pair<int, int> & l1, const std::pair<int, int> & r1,
    const std::pair<int, int> & l2, const std::pair<int, int> & r2){

    if (l1.first <= l2.first && r1.first >= r2.first
        && l2.second <= l2.second && r2.second >= r1.second){
            return std::fabs(l1.second - r1.second) * std::fabs(l2.first - r2.first);
    }
    return 0;
}

// r1 crosses r2's upper left corner 
// same as r2 crosses r1 lower right corner
float ObjectiveHelper::checkCorner1( const std::pair<int, int> & l1, const std::pair<int, int> & r1,
    const std::pair<int, int> & l2, const std::pair<int, int> & r2){

    if ( r1.first > l2.first && r1.second > l2.second
        && r1.first < r2.first && r1.second < r2.second){
        return std::fabs(r1.first - l2.first) * std::fabs(r1.second - l2.second);
    }
    return 0;
}

// r1 crosses r2's upper right corner 
// same as r2 crosses r1 lower left corner
float ObjectiveHelper::checkCorner2( const std::pair<int, int> & l1, const std::pair<int, int> & r1,
    const std::pair<int, int> & l2, const std::pair<int, int> & r2){

   if ( r2.first < r1.first && r2.first > l1.first 
        && l2.second < r1.second && l2.second > l1.second){
        return std::fabs(l1.first - r2.first) * std::fabs(r1.second - l2.second);
    }
    return 0;
}

float ObjectiveHelper::checkVerticalSide( const std::pair<int, int> & l1, const std::pair<int, int> & r1,
    const std::pair<int, int> & l2, const std::pair<int, int> & r2, const int & height){

    if ( l1.second > l2.second && r1.second < r2.second){
        // right
        if (l1.first < r2.first && r1.first > r2.first){
            return height * std::fabs(l1.first - r2.first);
        }

        // left
        if (l1.first < l2.first && r1.first > l2.first){
            return height * std::fabs(l2.first - r1.first);
        }
    }

    return 0;
}

float ObjectiveHelper::checkHorizontalSide( const std::pair<int, int> & l1, const std::pair<int, int> & r1,
    const std::pair<int, int> & l2, const std::pair<int, int> & r2, const int & width){

    if ( l1.first > l2.first && r1.first < r2.first){
        // bottom
        if (l1.second < r2.second && r1.second > r2.second){
            return width * std::fabs(l1.second - r2.second);
        }

        // top
        if (l1.second < l2.second && r1.second > l2.second){
            return width * std::fabs(l2.second - r1.second);
        }
    }

    return 0;
}

void ObjectiveHelper::testIntersection () {

    Board b1 = Board(400, 200);
    Board b2 = Board(50, 100);

    // test outside penalty
    std::cout << "OUTSIDE" << std::endl;
    BoardLocation b1Loc = BoardLocation(2750, 10, 0, 1);

    std::cout << "Test " << outsidePenalty(b1, b1Loc) << std::endl; 

    b1Loc = BoardLocation(10, 2000, 0, 1);
    std::cout << "Test " << outsidePenalty(b1, b1Loc) << std::endl; 

    b1Loc = BoardLocation(10, 2000, 1, 1);
    std::cout << "Test " << outsidePenalty(b1, b1Loc) << std::endl; 

    b1Loc = BoardLocation(10, 2000, 1, 0);
    std::cout << "Test " << outsidePenalty(b1, b1Loc) << std::endl; 

    // test intersection
    std::cout  << std::endl << "INTERSEC" << std::endl;

    b1Loc = BoardLocation(100, 100, 0, 1);
    BoardLocation b2Loc = BoardLocation(1000, 1000, 0, 1);

    std::cout << "Test " << calculateIntersection(b1, b1Loc, b2, b2Loc) << std::endl; 
    std::cout << "Test " << calculateIntersection(b2, b2Loc, b1, b1Loc) << std::endl;

    std::cout  << std::endl << "ZAWIERANIE" << std::endl;
    b2Loc = BoardLocation(110, 110, 0, 1);
    std::cout << "Test " << calculateIntersection(b1, b1Loc, b2, b2Loc) << std::endl; 
    std::cout << "Test " << calculateIntersection(b2, b2Loc, b1, b1Loc) << std::endl;

    std::cout  << std::endl << "BOKI" << std::endl;
    b2Loc = BoardLocation(90, 110, 0, 1); 
    std::cout << "Test " << calculateIntersection(b1, b1Loc, b2, b2Loc) << std::endl;
    std::cout << "Test " << calculateIntersection(b2, b2Loc, b1, b1Loc) << std::endl;

    b2Loc = BoardLocation(480, 110, 0, 1); 
    std::cout << "Test " << calculateIntersection(b1, b1Loc, b2, b2Loc) << std::endl;
    std::cout << "Test " << calculateIntersection(b2, b2Loc, b1, b1Loc) << std::endl;

    b2Loc = BoardLocation(110, 80, 0, 1); 
    std::cout << "Test " << calculateIntersection(b1, b1Loc, b2, b2Loc) << std::endl;
    std::cout << "Test " << calculateIntersection(b2, b2Loc, b1, b1Loc) << std::endl;

    b2Loc = BoardLocation(110, 280, 0, 1); 
    std::cout << "Test " << calculateIntersection(b1, b1Loc, b2, b2Loc) << std::endl;
    std::cout << "Test " << calculateIntersection(b2, b2Loc, b1, b1Loc) << std::endl;

    std::cout  << std::endl << "ROGI" << std::endl;

    b2Loc = BoardLocation(90, 90, 0, 1); 
    std::cout << "Test " << calculateIntersection(b1, b1Loc, b2, b2Loc) << std::endl;
    std::cout << "Test " << calculateIntersection(b2, b2Loc, b1, b1Loc) << std::endl;

    b2Loc = BoardLocation(480, 280, 0, 1); 
    std::cout << "Test " << calculateIntersection(b1, b1Loc, b2, b2Loc) << std::endl;
    std::cout << "Test " << calculateIntersection(b2, b2Loc, b1, b1Loc) << std::endl;

    b2Loc = BoardLocation(490, 90, 0, 1); 
    std::cout << "Test " << calculateIntersection(b1, b1Loc, b2, b2Loc) << std::endl;
    std::cout << "Test " << calculateIntersection(b2, b2Loc, b1, b1Loc) << std::endl;

    b2Loc = BoardLocation(90, 280, 0, 1); 
    std::cout << "Test " << calculateIntersection(b1, b1Loc, b2, b2Loc) << std::endl;
    std::cout << "Test " << calculateIntersection(b2, b2Loc, b1, b1Loc) << std::endl;

    std::cout  << std::endl << "INNE" << std::endl;

    b2Loc = BoardLocation(100, 100, 0, 1); 
    std::cout << "Test " << calculateIntersection(b1, b1Loc, b2, b2Loc) << std::endl;
    std::cout << "Test " << calculateIntersection(b2, b2Loc, b1, b1Loc) << std::endl;

    b2Loc = BoardLocation(100, 100, 0, 1); 
    b2 = Board(200, 500);
    std::cout << "Test " << calculateIntersection(b1, b1Loc, b2, b2Loc) << std::endl;
    std::cout << "Test " << calculateIntersection(b2, b2Loc, b1, b1Loc) << std::endl;

    b2 = Board(123, 678);
    b2Loc = BoardLocation(2757, 1576, 0, 1); 
    std::cout << "Test " << outsidePenalty(b2, b2Loc) << std::endl; 

    b1 = Board(1400, 500);
    b1Loc = BoardLocation(1920, 1238, 1, 1); 
    b2 = Board(900, 900);
    b2Loc = BoardLocation(1221, 723, 1, 1); 
    std::cout << "Test " << calculateIntersection(b1, b1Loc, b2, b2Loc) << std::endl;
    std::cout << "Test " << calculateIntersection(b2, b2Loc, b1, b1Loc) << std::endl;

}