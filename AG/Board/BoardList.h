#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Board.h"

/*******************************************************************************
 * Class containing list of boards - it is static, because sizes of boards are
 * the same for all genomes with locations
 ******************************************************************************/
class BoardList{
public:

    /*******************************************************************************
     * Read boards' dimentions from file
     ******************************************************************************/
    static void readData(const std::string & fileName);

    /*******************************************************************************
     * Number of boards
     ******************************************************************************/
    static int size() {return boardList.size();}

    /*******************************************************************************
     * Get board as given index
     ******************************************************************************/
    static Board get(const int i) {return boardList.at(i);}

private:
    static std::vector<Board> boardList;    ///< Vector with boards
};