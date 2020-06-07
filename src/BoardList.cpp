
#include <fstream>

#include "BoardList.h"

std::vector<Board> BoardList::boardList = std::vector<Board>();

void BoardList::readData (const std::string & fileName){

    std::fstream f (fileName, std::ios_base::in);

    if ( !f.is_open() ){
        std::cout << "Nie znaleziono pliku " << fileName << std::endl;
        return;
    }

    int x, y;

    while ( f >> x ){
        f >> y;
        boardList.push_back(Board(x, y));
    }

    f.close();
}