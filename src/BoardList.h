#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Board.h"

class BoardList{
public:
    static void readData(const std::string & fileName);
    static int size() {return boardList.size();}
    static Board get(const int i) {return boardList.at(i);}

private:
    static std::vector<Board> boardList;
};