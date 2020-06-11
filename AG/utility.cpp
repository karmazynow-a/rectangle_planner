#include <iostream>

#include "utility.h"
#include "AGtools/AGtools.h"
#include "Board/BoardList.h"
#include "Board/BoardLocation.h"


void saveResults(GABin2DecGenome & g){
    std::fstream f ("output.txt", std::ios_base::out);

    // TODO jeszcze znalezione pole
    f << AGtools::objective(g) << std::endl;

    for (int i = 0; i < BoardList::size(); ++i ){
        BoardLocation boardLocation (g.phenotype(i*4), g.phenotype(i*4 + 1), 
                    g.phenotype(i*4 + 2), g.phenotype(i*4 + 3));

        f << BoardList::get(i).getWidth() << " " 
            << BoardList::get(i).getHeight() << " "
            << boardLocation << std::endl;
    }

    f.close();
}

