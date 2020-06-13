
#include <iostream>
#include <ga/ga.h>
#include <ga/GA1DArrayGenome.h>

// 
/*******************************************************************************
 * Specialize allele set function for int
 ******************************************************************************/

template <>
int GAAlleleSet<int>::allele() const {
    int value = 0;
    if (core->type == GAAllele::ENUMERATED){
        std::cout << "e";
        value = core->a[GARandomInt(0, core->sz - 1)];
    }
    else if (core->type == GAAllele::DISCRETIZED){
        std::cout<<"d";
        float n = (core->a[1] - core->a[0]) / core->a[2];
        int m = (int)n;
        if (core->lowerb == GAAllele::EXCLUSIVE)
            m -= 1;
        if (core->upperb == GAAllele::EXCLUSIVE)
            m -= 1;
        value = core->a[0] + GARandomInt(0, (int)m) * core->a[2];
        if (core->lowerb == GAAllele::EXCLUSIVE)
            value += core->a[2];
    }
    else {
        if (core->a[0] == core->a[1] &&
            core->lowerb == GAAllele::EXCLUSIVE &&
            core->upperb == GAAllele::EXCLUSIVE) {
            value = core->a[0];
        }
        else {
            do {
                value = GARandomInt(core->a[0], core->a[1]);
            } while ((core->lowerb == GAAllele::EXCLUSIVE && value == core->a[0]) ||
                     (core->upperb == GAAllele::EXCLUSIVE && value == core->a[1]));
        }
    }
    return value;
}

// discretize item
template <>
int GAAlleleSet<int>::allele(unsigned int i) const {
    int value = 0;
    if (core->type == GAAllele::ENUMERATED) {
        std::cout << "ee";
        value = core->a[i % core->sz];
    }

    else if (core->type == GAAllele::DISCRETIZED) {
        std::cout<<"dd";
        float n = (core->a[1] - core->a[0]) / core->a[2];
        unsigned int m = (unsigned int)n;
        if (core->lowerb == GAAllele::EXCLUSIVE)
            m -= 1;
        if (core->upperb == GAAllele::EXCLUSIVE)
            m -= 1;
        if (i > m)
            i = (int)m;
        value = core->a[0] + i * core->a[2];
        if (core->lowerb == GAAllele::EXCLUSIVE)
            value += core->a[2];
    }
    else {
        GAErr(GA_LOC, "GAAlleleSet", "allele", gaErrNoAlleleIndex);
        value = core->a[0];
    }

    return value;
}