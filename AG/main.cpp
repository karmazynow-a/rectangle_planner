/** 
*   Genetic algorithm that finds best location of small boards
*		in restricted area
*   @author Aleksandra Poreba 
*/

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <chrono>
#include <ga/ga.h>
#include <ga/GA1DArrayGenome.h>

#include "AGtools/AGtools.h"
#include "Board/BoardList.h"
#include "Board/BoardLocation.h"

#include "AGtools/ObjectivePenalty.h"

#define VERBOSE 0

int main () {
	BoardLocation::maxWidth = 2800;
	BoardLocation::maxHeight = 2070;

	int testSize = 30;
	int popsize  = 1000;
	int ngen     = 800;

	// tresholds for thightening objective criteria
	int tr1 = round(ngen*0.4);
	int tr2 = round(ngen*0.6);
	int tr3 = round(ngen*0.8);

	float pcross = 0.5, pmut = 0.5;
	AGtools::setObjectiveParams(10, 10, true);

	BoardList::readData("../data/test_input1.dat");

	float bestObjective = 0;

	auto start = std::chrono::steady_clock::now();

	for (int i = 0; i < testSize; ++i){
		GAAlleleSetArray<int> alleles = AGtools::initPhenotype(BoardList::size(), BoardLocation::maxWidth, BoardLocation::maxHeight);

		GA1DArrayAlleleGenome<int> genome(alleles, AGtools::objective);

		genome.crossover(GA1DArrayGenome<int>::TwoPointCrossover);

		GASimpleGA ga(genome);
		ga.populationSize(popsize);
		ga.nGenerations(ngen);
		ga.pMutation(pmut);
		ga.pCrossover(pcross);

		ga.scaling(GASigmaTruncationScaling());
		ga.selector(GARankSelector());

		ga.elitist(gaTrue);
		ga.maximize();
		
		// evolution
		ga.initialize((unsigned)time(0));

		while ( !ga.done() ) {
			ga.step();

			if (VERBOSE) {
				std::cout << ga.generation() << "\t conv=" << ga.convergence();
				genome = ga.statistics().bestIndividual();
				std::cout << "\t x=" << genome.gene(0) << 
					"\t Fbest=" << AGtools::objective(genome) << std::endl;
			}
			
			if (ga.generation() == tr3){
				VERBOSE && std::cout << "Treshold 3" << std::endl;
				ga.elitist(gaFalse);
				AGtools::setObjectiveParams(1, 1, false);
			} else if (ga.generation() == tr3 + 1){
				ga.elitist(gaTrue);
			} else if (ga.generation() == tr1) {
				VERBOSE && std::cout << "Treshold 1" << std::endl;
				AGtools::setObjectiveParams(100, 100, true);
			} else if (ga.generation() == tr2) {
				VERBOSE && std::cout << "Treshold 2" << std::endl;
				AGtools::setObjectiveParams(1000, 1000, true);
			}
		}

		genome = ga.statistics().bestIndividual();
		std::cout << "Found new area: " << AGtools::objective(genome) << std::endl;

		if (AGtools::objective(genome) > bestObjective ){
			bestObjective = AGtools::objective(genome);

			// FIXME saving to file after execution causes segfaults
			AGtools::saveResults(genome);
		}
	}

	auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Algorithm took: " << elapsed_seconds.count() << "s\n";

	return 0;
}
