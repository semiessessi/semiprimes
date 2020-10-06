#ifndef FACTORISATION_H
#define FACTORISATION_H

#include "Number.h"

#include <vector>

struct Factorisation
{
	std::vector< Factorisation > mxKnownFactors;
	Number mxNumber;
	int miPower;
	bool mbKnownPrime;
	bool mbKnownComposite;
	
	Factorisation( const Number& xNumber = 0z, const bool bPrime = false );

	void Report( const bool bVerbose = false ) const;
		
	template< typename Algorithm >
	void ContinueWithAlgorithm( const Algorithm& xAlgorithm );
};

#include "Factorisation.inl"

#endif
