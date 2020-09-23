#ifndef FACTORISATION_INL
#define FACTORISATION_INL

// SE - NOTE: for intellisense.. urg
#include "Factorisation.h"

template< typename Algorithm >
void Factorisation::ContinueWithAlgorithm( const Algorithm& xAlgorithm )
{
	if( mbKnownPrime == true )
	{
		return;
	}

	if( mxKnownFactors.size() == 0 )
	{
		mxKnownFactors.push_back( Factorisation( mxNumber ) );
	}

	for( size_t u = 0; u < mxKnownFactors.size(); ++u )
	{
		// this might be breakable or prime and unknown...
		if( mxKnownFactors[ u ].mbKnownComposite || !mxKnownFactors[ u ].mbKnownPrime )
		{
			const Factorisation xNew = xAlgorithm( mxKnownFactors[ u ].mxNumber );
			// .. if we got factors substitute them.
			if( xNew.mxKnownFactors.size() > 0 )
			{
				mbKnownComposite = xNew.mbKnownComposite;
				mxKnownFactors.erase( mxKnownFactors.begin() + u );
				for( size_t v = 0; v < xNew.mxKnownFactors.size(); ++v )
				{
					mxKnownFactors.insert( mxKnownFactors.begin() + u + v, xNew.mxKnownFactors[ v ] );
				}
			}
			else
			{
				mxKnownFactors[ u ] = xNew;
			}
		}
	}

	// SE - TODO: sort/collapse/tidy results (?)
}

#endif
