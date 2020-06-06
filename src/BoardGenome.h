# pragma once

#include <iostream>
#include <string>
#include <ga/ga.h>

class BoardGenome : public GAGenome {
public:
    // class name and id
    GADefineIdentity("BoardGenome", 201);
    static void Initializer(GAGenome&);
    static int Mutator(GAGenome&, float);
    static float Comparator(const GAGenome&, const GAGenome&);
    static float Evaluator(GAGenome&);
    static int Crossover(const GAGenome&, const GAGenome&, GAGenome*,
			GAGenome*);

    BoardGenome();
    BoardGenome(const std::string & fileName);
    virtual ~BoardGenome();

    int operator==(const GAGenome& orig);
    BoardGenome& operator=(const GAGenome & arg);
    int write(std::ostream & os) const;

    virtual BoardGenome* clone(GAGenome::CloneMethod) const;
    virtual void copy(const GAGenome& c);
    virtual int equal(const GAGenome& g) const;


private:
    int maxWidth;
    int maxHeigth;
};