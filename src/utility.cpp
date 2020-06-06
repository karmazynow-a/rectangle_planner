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

    float sum = 0;
    
    for (int i = 0; i < boardList.size(); ++i){
        BoardLocation boardLocation (genome.phenotype(i*4), genome.phenotype(i*4 + 1), 
                    genome.phenotype(i*4 + 2), genome.phenotype(i*4 + 3));

        sum += boardList.at(i).getArea();

        // check if they are outside
        sum += outsidePenalty(boardList.at(i), boardLocation);

        // check intersection
    }


    return sum;
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
    int W = 2800, H = 2070;
    int sum = 0;
 
    if (boardLocation.getX() + board.getWidth() > W){
        sum += board.getHeight() * (boardLocation.getX() + board.getWidth() - W);
    }

    if (boardLocation.getY() + board.getHeight() > H){
        sum += board.getWidth() * (boardLocation.getY() + board.getHeight() - H);
    }

    return (-1) * sum;
}