#include <cstdlib>
#include <iostream>
#include <ga/ga.h>

#include "utility.h"

extern std::vector<Board> boardList;

int main () {

	const int W = 2800;
	const int H = 2070;

	int popsize  = 100;
	int ngen     = 1000;
	float pcross = 0.5, pmut = 0.1;

	boardList = readData("../data/example_input.dat");
	GABin2DecPhenotype map = initPhenotype(boardList.size(), W, H);

	GABin2DecGenome genome(map, objective);

	//genome.initializer(init);
    genome.crossover(GABin2DecGenome::TwoPointCrossover);
    //genome.mutator(mutator);
    //genome.initialize();


	GASimpleGA ga(genome);
	ga.populationSize(popsize);
	ga.nGenerations(ngen);
	ga.pMutation(pmut);
	ga.pCrossover(pcross);

	ga.scaling(GASigmaTruncationScaling());
	ga.selector(GARouletteWheelSelector());
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
	ga.evolve((unsigned)time(0));

	genome = ga.statistics().bestIndividual();
	saveResults(genome, boardList);

	return 0;
}
