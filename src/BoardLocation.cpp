
#include "BoardLocation.h"

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
