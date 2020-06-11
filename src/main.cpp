#include <cstdlib>
#include <iostream>
#include <ga/ga.h>

#include "utility.h"
#include "BoardList.h"
#include "Objective.h"

int main () {
	ObjectiveHelper o = ObjectiveHelper();
	//o.testIntersection();

	const int W = 2800;
	const int H = 2070;

	int popsize  = 10;
	int ngen     = 100;
	float pcross = 0.5, pmut = 0.5;

	BoardList::readData("../data/example_input.dat");
	GABin2DecPhenotype map = initPhenotype(BoardList::size(), W, H);

	GABin2DecGenome genome(map, Objective::objective);

	//genome.initializer(init);
    genome.crossover(GABin2DecGenome::TwoPointCrossover);
    //genome.mutator(mutator);
    genome.initialize();


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
		std::cout << ga.generation() << "\t conv=" << ga.convergence();
		genome = ga.statistics().bestIndividual();
		std::cout << "\t x=" << genome.phenotype(0) << "\t Fbest=" << Objective::objective(genome) << std::endl;
	
		if (ga.generation() == ngen/2){
			Objective::shouldPunish = false;
		}
	}

	genome = ga.statistics().bestIndividual();
	for (int i =0; i < genome.nPhenotypes(); ++i) {
		std::cout << genome.phenotype(i) << " ";
	}
	saveResults(genome);

	return 0;
}
