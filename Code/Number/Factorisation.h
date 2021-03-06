#ifndef FACTORISATION_H
#define FACTORISATION_H

#include "Number.h"

#include <vector>

struct Factorisation
{
	std::vector< Factorisation > mxKnownFactors;
	Number mxNumber;
	const char* szProofName;
	const char* szFactoringAlgorithm;
	int miPower;
	int64_t miFactoringTimeNS;
	int64_t miProofTimeNS;
	bool mbKnownPrime;
	bool mbKnownComposite;
	
	Factorisation( const Number& xNumber = 0z, const bool bPrime = false );

	void Report( const bool bVerbose = false );
		
	template< typename Algorithm >
	void ContinueWithAlgorithm( const Algorithm& xAlgorithm, const bool bRepeat = false );
};

#include "Factorisation.inl"

#endif
