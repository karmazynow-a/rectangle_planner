
#include "AGtools.h"
#include "../Board/BoardLocation.h"

void AGtools::setObjectiveParams(const float& iPenaltyFactor, const float& oPenaltyFactor, const bool& shouldPunish){
    Objective::iPenaltyFactor = iPenaltyFactor;
    Objective::oPenaltyFactor = oPenaltyFactor;
    Objective::shouldPunish = shouldPunish;
}

int AGtools::mutator(GAGenome& g, float pm){
    int numberOfMutations = 0;

    auto &genome = (GABin2DecGenome &) g;

    int singleLength = 26; // TODO
    
    for (int i = 0; i < genome.nPhenotypes(); i+=4) {

        // beginning of individual in genome
        int dx = singleLength*(i/4);

        // mutate x and y - must be in borders
        // bitwise motation
        /*
        int tmpMut = 0;
        do{
            tmpMut = 0;
            for ( int idx = dx; idx < dx+12; ++idx){
                if (GAFlipCoin(pm)) {
                    genome.gene(idx, !genome.gene(idx));
                    tmpMut++;
                }
            }
        } while (genome.phenotype(i) >= 2800);

        numberOfMutations += tmpMut;

        do{
            tmpMut = 0;
            for ( int idx = dx + 12; idx < dx+24; ++idx){
                if (GAFlipCoin(pm)) {
                    genome.gene(idx, !genome.gene(idx));
                    tmpMut++;
                }
            }
        } while (genome.phenotype(i+1) >= 2070);

        numberOfMutations += tmpMut;
        */

        // real number mutation
        int mutationValue = 0;
        int counter = 0;

        if (genome.phenotype(i) > 2800) genome.phenotype(i, 2800);

        do{
            mutationValue = genome.phenotype(i) + GAUnitGaussian()*10;
        } while (mutationValue >= 2800 || mutationValue < 0 );

        genome.phenotype(i, mutationValue);

        if (genome.phenotype(i+1) > 2070) genome.phenotype(i+1, 2070);
        do{
            mutationValue = genome.phenotype(i+1) + GAUnitGaussian()*10;
        } while (mutationValue >= 2070 || mutationValue < 0 );

        genome.phenotype(i+1, mutationValue);

        if (GAFlipCoin(pm)) {
            genome.phenotype(i+2, !genome.phenotype(i+2));
            ++numberOfMutations;
        }

        if (GAFlipCoin(pm)) {
            genome.phenotype(i+3, !genome.phenotype(i+3));
            ++numberOfMutations;
        }
    }
    return numberOfMutations;
}

GABin2DecPhenotype AGtools::initPhenotype(const int& N, const int& W, const int& H){

    GABin2DecPhenotype map;
    for (int i = 0; i < N; ++i) {
        // temprorary - to have integers
        // kinda bad style, but thats temp solution (I hope)
        
        map.add(12, 0, 4095);  // x coord
        map.add(12, 0, 4095);  // y coord
        map.add(1, 0, 1);   // rotate
        map.add(1, 0, 1);   // exist
    }

    return map;
}


void AGtools::init(GAGenome& g) {
    auto &genome = (GABin2DecGenome &) g;
    for (int i = 0; i < genome.nPhenotypes(); i+=4) {

        genome.phenotype(i, GARandomInt(0, BoardLocation::maxWidth));
        genome.phenotype(i+1, GARandomInt(0, BoardLocation::maxHeight));
        genome.phenotype(i+2, GAFlipCoin(0.5));
        genome.phenotype(i+3, GAFlipCoin(0.5));
    }
}