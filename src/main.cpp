#include <cstdlib>
#include <iostream>
#include <ga/ga.h>

#include "Board.h"
#include "BoardGenome.h"

// funkcja celu
float objective(GAGenome &);

int main () {

	int popsize  = 100;
	int ngen     = 1000;
	float pcross = 0.5, pmut = 0.1;

	// kodowanie binarne
	GABin2DecPhenotype map;
	map.add(30, 0.0, 1.0);
	map.add(30, 0.0, 1.0);

	GABin2DecGenome genome(map, objective);

	BoardGenome gg ("../data/example_input.dat");

	GASimpleGA ga(gg);

	// inicjacja algorytmu
	ga.populationSize(popsize);
	ga.nGenerations(ngen);
	ga.pMutation(pmut);
	ga.pCrossover(pcross);

	// nieujemność f dostosowania
	GASigmaTruncationScaling scaling;
	ga.scaling(scaling);

	// ustawienie selekcji
	GARouletteWheelSelector s;
	ga.selector(s);

	// ustawienie krzyżowania
	ga.crossover(GABin2DecGenome::TwoPointCrossover);

	// sukcesja elitarna
	ga.elitist(gaTrue); 

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

	/*
	std::cout << "Najlepsze rozwiazanie : "
			<< "F( x=" << genome.phenotype(0) 
			<< ", y=" << genome.phenotype(1) 
			<< ") = " << objective(genome) << std::endl;
	*/
	return 0;
}


float objective(GAGenome & c) {
  //GABin2DecGenome & genome = (GABin2DecGenome &) c;

  // obliczyć powierzchnie
  // sprawedzić przecięcia między wszystkimi
  return 0;
}