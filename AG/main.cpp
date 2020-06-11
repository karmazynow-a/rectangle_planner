#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <ga/ga.h>

#include "AGtools/AGtools.h"
#include "utility.h"
#include "Board/BoardList.h"
#include "Board/BoardLocation.h"

int main () {
	BoardLocation::maxWidth = 2800;
	BoardLocation::maxHeight = 2070;

	int popsize  = 1000;
	int ngen     = 500;
	int punishGen = 400;
	float pcross = 0.3, pmut = 0.5;
	AGtools::setObjectiveParams(10, 10, true);

	BoardList::readData("../data/example_input.dat");
	GABin2DecPhenotype map = AGtools::initPhenotype(BoardList::size(), BoardLocation::maxWidth, BoardLocation::maxHeight);

	GABin2DecGenome genome(map, AGtools::objective);

	genome.initializer(AGtools::init);
    genome.crossover(GABin2DecGenome::TwoPointCrossover);
    genome.mutator(AGtools::mutator);

	GASimpleGA ga(genome);
	ga.populationSize(popsize);
	ga.nGenerations(ngen);
	ga.pMutation(pmut);
	ga.pCrossover(pcross);

	ga.scaling(GASigmaTruncationScaling());
	ga.selector(GARouletteWheelSelector());
	//ga.selector(GARankSelector());
	ga.elitist(gaTrue);
	ga.maximize();

	// zapis statystyk
	ga.scoreFilename("zbieznosc.dat"); // plik z statystykami
	ga.scoreFrequency(10); // zapis statystyk
	ga.flushFrequency(50); // zapis do pliku
	ga.selectScores(
				GAStatistics::Mean | 
                GAStatistics::Maximum | 
                GAStatistics::Minimum |
                GAStatistics::Deviation |
                GAStatistics::Diversity);
	
	// ewolucja
	//ga.evolve((unsigned)time(0));
	ga.initialize((unsigned)time(0));
	genome = ga.statistics().bestIndividual();
	for (int i =0; i < genome.nPhenotypes(); ++i) {
		std::cout << genome.phenotype(i) << " ";
	}
	std::cout << std::endl;

	while ( !ga.done() ) {
		ga.step();
		//std::cout << "BEST" << std::endl;
		std::cout << ga.generation() << "\t conv=" << ga.convergence();
		genome = ga.statistics().bestIndividual();
		std::cout << "\t x=" << genome.phenotype(0) << 
			"\t Fbest=" << AGtools::objective(genome) << std::endl;
/*
		std::cout << "POP" << std::endl;
		GAPopulation p = ga.population();
		for (int i = 0; i< ga.populationSize(); ++i){
			std::cout << std::setw(10) << std::fixed << AGtools::objective(p.individual(i)) << std::endl;
		}
*/		
		if (ga.generation() == punishGen){
			ga.elitist(gaFalse);
			AGtools::setObjectiveParams(1, 1, false);
		} else if (ga.generation() == punishGen + 1){
			ga.elitist(gaTrue);
		} else if (ga.generation() == 50) {
			AGtools::setObjectiveParams(100, 100, true);
		} else if (ga.generation() == 100) {
			AGtools::setObjectiveParams(1000, 1000, true);
		}
	}

	genome = ga.statistics().bestIndividual();
	for (int i =0; i < genome.nPhenotypes(); ++i) {
		std::cout << genome.phenotype(i) << " ";
	}
	saveResults(genome);

	return 0;
}
