#pragma once

#include <iostream>
#include <vector>
#include <ga/ga.h>

#include "Board.h"
#include "BoardLocation.h"
#include "BoardList.h"
#include "ObjectiveHelper.h"


void saveResults(GABin2DecGenome &);

GABin2DecPhenotype initPhenotype(const int N, const int W, const int H);

// operator mutacji
int mutator(GAGenome & g, float pm);
