
#include <fstream>

#include "BoardList.h"

std::vector<Board> BoardList::boardList = std::vector<Board>();

bool BoardList::readData (const std::string & fileName){

    std::fstream f (fileName, std::ios_base::in);

    if ( !f.is_open() ){
        std::cout << "File " << fileName << " not found!" << std::endl;
        return false;
    }

    int x, y;

    while ( f >> x ){
        f >> y;
        boardList.push_back(Board(x, y));
    }

    f.close();
    std::cout << "Data is ready." << std::endl<< std::endl;
    return true;
}