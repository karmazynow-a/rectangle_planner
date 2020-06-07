#pragma once

#include <iostream>
#include <vector>
#include <ga/ga.h>

class Board {
public:
    Board(const int w,const int h) : width(w), height(h) {}
    Board() : width(-1), height(-1) {}

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getArea() const { return height*width; }

private:
    int width;
    int height;
};

class BoardLocation {
public:
    BoardLocation() : m_x(-1), m_y(-1), m_r(-1), m_e(-1){}
    BoardLocation(int x, int y, int r, int e) : m_x(x), m_y(y), m_r(r), m_e(e){}
    BoardLocation(float x, float y, int r, int e) : m_x(abs(x)), m_y(abs(y)), m_r(r), m_e(e) {}

    int getX() const {return m_x;}
    int getY() const {return m_y;}
    int getR() const {return m_r;}
    int getE() const {return m_e;}

    bool exists() const {return m_e;}
    bool rotated() const {return m_r;}

    friend std::ostream & operator<< (std::ostream& os, const BoardLocation & b);

private:
    int m_x;
    int m_y;
    int m_r;
    int m_e;
};

float objective(GAGenome &);

// save data from input file to vector
std::vector<Board> readData (const std::string & fileName);

void saveResults(GABin2DecGenome &, const std::vector<Board> &);

GABin2DecPhenotype initPhenotype(const int N, const int W, const int H);

// operator mutacji
int mutator(GAGenome & g, float pm);

int outsidePenalty(const Board &, const BoardLocation &);

float intersectionPenalty(const int &, const std::vector<Board> &, 
    const std::vector<BoardLocation> & );

std::vector<BoardLocation> createBoardLocationList(const GABin2DecGenome & g);

float calculateIntersection (const Board &, const BoardLocation &, const Board &,
    const BoardLocation &);

float checkCorner1( const std::pair<int, int> & l1, const std::pair<int, int> & r1,
    const std::pair<int, int> & l2, const std::pair<int, int> & r2);

float checkCorner2( const std::pair<int, int> & l1, const std::pair<int, int> & r1,
    const std::pair<int, int> & l2, const std::pair<int, int> & r2);

float checkVerticalSide( const std::pair<int, int> & l1, const std::pair<int, int> & r1,
    const std::pair<int, int> & l2, const std::pair<int, int> & r2, const int & height);

float checkHorizontalSide( const std::pair<int, int> & l1, const std::pair<int, int> & r1,
    const std::pair<int, int> & l2, const std::pair<int, int> & r2, const int & height);

void testIntersection();