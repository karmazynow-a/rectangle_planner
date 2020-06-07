#include <cmath>

#include "utility.h"

// necessary for objective
std::vector<Board> boardList = std::vector<Board>();

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

std::vector<Board> readData (const std::string & fileName){
    std::vector<Board> vec;

    std::fstream f (fileName, std::ios_base::in);

    if ( !f.is_open() ){
        std::cout << "Nie znaleziono pliku " << fileName << std::endl;
        return vec;
    }

    int x, y;

    while ( f >> x ){
        f >> y;
        vec.push_back(Board(x, y));
    }

    f.close();

    return vec;
}

void saveResults(GABin2DecGenome & g, const std::vector<Board> & boards){
    std::fstream f ("output.txt", std::ios_base::out);

    // TODO jeszcze znalezione pole
    f << objective(g) << std::endl;

    for (int i = 0; i < boards.size(); ++i ){
        BoardLocation boardLocation (g.phenotype(i*4), g.phenotype(i*4 + 1), 
                    g.phenotype(i*4 + 2), g.phenotype(i*4 + 3));

        f << boards.at(i).getWidth() << " " 
            << boards.at(i).getHeight() << " "
            << boardLocation << std::endl;
    }

    f.close();
}

float objective(GAGenome & g){
    auto &genome = (GABin2DecGenome &) g;

    std::vector<BoardLocation> boardLocationList = createBoardLocationList(genome);

    double sum = 0;
    
    for (int i = 0; i < boardList.size(); ++i){
        sum += boardList.at(i).getArea();

        // check if they are outside board
        sum -= outsidePenalty(boardList.at(i), boardLocationList.at(i));

        // check intersection
        sum -= intersectionPenalty(i, boardList, boardLocationList);
    }

    float s = sum/100000.0; 

    //std::cout << "Objective is " << s << std::endl;

    return s;
}

std::vector<BoardLocation> createBoardLocationList(const GABin2DecGenome & g){
    std::vector<BoardLocation> boardLocationList = std::vector<BoardLocation>();

    for (int i = 0; i < boardList.size(); ++i){
        boardLocationList.push_back( BoardLocation(g.phenotype(i*4), g.phenotype(i*4 + 1), 
                    g.phenotype(i*4 + 2), g.phenotype(i*4 + 3)) );
    }

    return boardLocationList;
}

int mutator(GAGenome & g, float pm){
    return 1;
}

std::ostream & operator<< (std::ostream& os, const BoardLocation & b){
    if (b.exists()){
        os << -1 << " " 
            << -1 << " "
            << b.getR();
    }
    else {
        os << b.getX() << " " 
            << b.getY() << " "
            << b.getR();   
    }

    return os;
}

int outsidePenalty(const Board & board, const BoardLocation & boardLocation){
    if (!boardLocation.exists()){
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
        sum += board.getHeight() * (dimX - W);
    }

    if ( dimY > H){
        sum += board.getWidth() * (dimY - H);
    }

    return sum * sum;
}

float intersectionPenalty(const int & boardIndex, const std::vector<Board> & boardList, 
    const std::vector<BoardLocation> & boardLocationList ){

    float sum = 0;
    for (int i = boardIndex + 1; i < boardList.size(); ++i){
        sum += calculateIntersection(boardList.at(boardIndex), boardLocationList.at(boardIndex),
            boardList.at(i), boardLocationList.at(i) );
    }

    return sum;
}

// how b1 intercect with b2
float calculateIntersection (const Board & b1, const BoardLocation & b1Loc, 
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

    float s;
    s = checkHorizontalSide(l1, r1, l2, r2, b1.getWidth());
    if (s > 0) return s;
    s = checkHorizontalSide(l2, r2, l1, r1, b2.getWidth());
    if (s > 0) return s;
    s = checkVerticalSide(l1, r1, l2, r2, b1.getHeight());
    if (s > 0) return s;
    s = checkVerticalSide(l2, r2, l1, r1, b2.getHeight());
    if (s > 0) return s;

    // rogi
    float sum;
    sum += checkCorner1(l1, r1, l2, r2);
    sum += checkCorner1(l2, r2, l1, r1);
    sum += checkCorner2(l1, r1, l2, r2);
    sum += checkCorner2(l2, r2, l1, r1);

    return 100;
 
}

float checkCorner1( const std::pair<int, int> & l1, const std::pair<int, int> & r1,
    const std::pair<int, int> & l2, const std::pair<int, int> & r2){

    if ( r2.first > r2.first && r1.first < r2.first 
        && r1.second < l1.second && r1.second > r2.second){
        return std::fabs(r1.first - l1.first) * std::fabs(r2.second - l1.second);
    }
    else {
        return 0;
    }
}

float checkCorner2( const std::pair<int, int> & l1, const std::pair<int, int> & r1,
    const std::pair<int, int> & l2, const std::pair<int, int> & r2){
        
   if ( l1.first > l2.first && l1.first < r2.first 
        && r1.second < l1.second && r1.second > r2.second){
        return std::fabs(r1.first - l1.first) * std::fabs(r2.second - l1.second);
    }
    else {
        return 0;
    }
}

float checkVerticalSide( const std::pair<int, int> & l1, const std::pair<int, int> & r1,
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

float checkHorizontalSide( const std::pair<int, int> & l1, const std::pair<int, int> & r1,
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

void testIntersection () {
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
    std::cout << "INTERSEC" << std::endl;

    b1Loc = BoardLocation(100, 100, 0, 1);
    BoardLocation b2Loc = BoardLocation(1000, 1000, 0, 1);

    std::cout << "Test " << calculateIntersection(b1, b1Loc, b2, b2Loc) << std::endl; 
    std::cout << "Test " << calculateIntersection(b2, b2Loc, b1, b1Loc) << std::endl;

    b2Loc = BoardLocation(110, 110, 0, 1);
    std::cout << "Test " << calculateIntersection(b1, b1Loc, b2, b2Loc) << std::endl; 
    std::cout << "Test " << calculateIntersection(b2, b2Loc, b1, b1Loc) << std::endl;

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

    b2Loc = BoardLocation(90, 90, 0, 1); 
    std::cout << "Test " << calculateIntersection(b1, b1Loc, b2, b2Loc) << std::endl;
    std::cout << "Test " << calculateIntersection(b2, b2Loc, b1, b1Loc) << std::endl;
}