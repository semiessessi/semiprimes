#ifndef FACTORISATION_H
#define FACTORISATION_H

#include "Number.h"

#include <vector>

struct Factorisation
{
	std::vector<Factorisation> mxKnownFactors;
	Number mxNumber;
	bool mbKnownPrime;
	bool mbKnownComposite;
	
	Factorisation( const Number& xNumber = 0z );
};

#endif
