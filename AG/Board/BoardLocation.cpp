
#include "BoardLocation.h"

int BoardLocation::maxWidth = 2800;
int BoardLocation::maxHeight = 2070;

std::ostream & operator<< (std::ostream& os, const BoardLocation & b){
    if (!b.exists()){
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
