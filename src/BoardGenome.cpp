
#include "BoardGenome.h"

BoardGenome::BoardGenome() {
    initializer(Initializer);
    mutator(Mutator);
    comparator(Comparator);
	evaluator(Evaluator);
    crossover(Crossover);

	//floatVal = nullptr;
}


BoardGenome::BoardGenome(const std::string & fileName) {
    initializer(Initializer);
    mutator(Mutator);
    comparator(Comparator);
	evaluator(Evaluator);
    crossover(Crossover);

    std::cout << "Will read values from file" << std::endl;

}


BoardGenome::~BoardGenome(){
    // TODO
}


BoardGenome& BoardGenome::operator=(const GAGenome& orig){
	if (&orig != this) copy(orig);
	return *this;
}

int BoardGenome::operator==(const GAGenome& orig){
	return this->equal(orig);
}

int BoardGenome::equal(const GAGenome& g) const {
	BoardGenome& genome = ( BoardGenome& ) g;

    // TODO porównać wartości w tablicach
	return 1;
}

BoardGenome* BoardGenome::clone(GAGenome::CloneMethod) const {
	return new BoardGenome(*this);
}

void BoardGenome::copy(const GAGenome& c){
	if (&c != this && sameClass(c)) {
		GAGenome::copy(c);

		BoardGenome & bc = (BoardGenome &)c;
		//floatVal->copy(*(bc.floatVal));
		//boolVars->copy(*(bc.boolVars));
	}
}

int BoardGenome::write(std::ostream & os) const{
    // TODO zapisać do pliku jak ma być format outputu

    os << "Party" << std::endl;

    return os.fail() ? 1 : 0;
}

void BoardGenome::Initializer(GAGenome& G) {

	BoardGenome& g = (BoardGenome &)G;

	//g.floatVal->initialize();
	//g.boolVars->initialize();
	//g._evaluated = gaFalse;
}

int BoardGenome::Mutator(GAGenome& G, float pmut) {
	BoardGenome& child = (BoardGenome &)G;

    // TODO nie mutujemy wymiarów!
	int nmut = 0;
            //child.floatVal->mutate(pmut) 
            //+ child.boolVars->mutate(pmut);
            
	return nmut;
}

float BoardGenome::Comparator(const GAGenome& p1, const GAGenome& p2) {
    BoardGenome& g1 = (BoardGenome &) p1;
    BoardGenome& g2 = (BoardGenome &) p2;

	//return 0.5 * (g1.floatVal->compare(g2) + g1.boolVars->compare(g2));
    return 1.0;
}

int BoardGenome::Crossover(const GAGenome& p1, const GAGenome& p2, GAGenome* c1, GAGenome* c2) {
    int n = 0;

    BoardGenome& parent1 = (BoardGenome &) p1;
    BoardGenome& parent2 = (BoardGenome &) p2;

    if (c1){
        BoardGenome& child1 = (BoardGenome &) *c1;
        // TODO perform crossover
        //BoardGenome::performCrossover(p1, p2, c1);
        n++;
    }
    if (c2){
        BoardGenome& child2 = (BoardGenome &) *c2;
        //BoardGenome::performCrossover(p1, p2, c2);
        n++;
    }

    return n;
}

float BoardGenome::Evaluator(GAGenome& g) {
    BoardGenome& evalG = (BoardGenome &) g;
    //float s = (float)(HGAGenome::calcObjectValue(hgenome));
    float s = 1;
/*
    if (hgenome.isFeasible){
        cout << "***********************************************Acceptable with cost = " << hgenome.durationCost << endl;
        if (HPGV::bestFeasibleCost == 0){
            HPGV::bestFeasibleCost = hgenome.durationCost;
            bestSol = hgenome;
        }else{
            if (HPGV::bestFeasibleCost > hgenome.durationCost){
                HPGV::bestFeasibleCost = hgenome.durationCost;
                bestSol = hgenome;
            }
        }
    }
    */
    return s;
}