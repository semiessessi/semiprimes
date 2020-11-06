#ifndef FACTORISATION_INL
#define FACTORISATION_INL

// SE - NOTE: for intellisense.. urg
#include "Factorisation.h"

Number GetWheelBound();

template< typename Algorithm >
void Factorisation::ContinueWithAlgorithm( const Algorithm& xAlgorithm, const bool bRepeat )
{
	if( mbKnownPrime == true )
	{
		return;
	}

	// is it a perfect power?
	// (what about products of them??)
	if( ( mbKnownComposite == true )
		&& ( mxKnownFactors.size() == 1 )
		&& ( mxKnownFactors[ 0 ].mbKnownPrime == true ) )
	{
		return;
	}

	if( mxKnownFactors.size() == 0 )
	{
		mxKnownFactors.push_back( Factorisation( mxNumber ) );
	}

	const size_t uSize = mxKnownFactors.size();
	for( size_t u = 0; u < ( bRepeat ? mxKnownFactors.size() : uSize ); ++u )
	{
		// maybe the wheel bound has increased
		if( mxKnownFactors[ u ].mbKnownPrime == false )
		{
			if( mxKnownFactors[ u ].mxNumber < GetWheelBound() )
			{
				mxKnownFactors[ u ].mbKnownPrime = true;
				mxKnownFactors[ u ].szProofName = "bound set by trial division";
			}
		}

		// this might be breakable or prime and unknown...
		if( mxKnownFactors[ u ].mbKnownComposite || !mxKnownFactors[ u ].mbKnownPrime )
		{
			Factorisation xNew = xAlgorithm( mxKnownFactors[ u ].mxNumber );
			xNew.miPower = mxKnownFactors[ u ].miPower;
			xNew.szFactoringAlgorithm = mxKnownFactors[ u ].szFactoringAlgorithm;
			if( mxKnownFactors[ u ].mbKnownComposite )
			{
				xNew.mbKnownComposite = true;
				xNew.szProofName = mxKnownFactors[ u ].szProofName;
				mbKnownComposite = true;
			}
			// .. if we got factors substitute them.
			if( xNew.mxKnownFactors.size() > 0 )
			{
				mxKnownFactors.erase( mxKnownFactors.begin() + u );
				for( size_t v = 0; v < xNew.mxKnownFactors.size(); ++v )
				{
					xNew.mxKnownFactors[ v ].miPower *= xNew.miPower;
					if( xNew.mxKnownFactors[ v ].szFactoringAlgorithm[ 0 ] == 0 )
					{
						// why not?
						xNew.mxKnownFactors[ v ].szFactoringAlgorithm = xNew.szFactoringAlgorithm;
					}
					mxKnownFactors.insert( mxKnownFactors.begin() + u + v, xNew.mxKnownFactors[ v ] );
				}

				// go again on the new factor (?)
				/*
				if( bRepeat && !mxKnownFactors[ u ].mbKnownPrime )
				{
					--u;
				}
				*/
			}
			else
			{
				mxKnownFactors[ u ] = xNew;
			}
		}
	}

	// SE - TODO: sort/collapse/tidy results (?)

	// SE - NOTE: not sure how this happens...
	if( ( mxKnownFactors.size() == 1 )
		//&& ( mxKnownFactors[ 0 ].miPower == 1 )
		&& ( mxKnownFactors[ 0 ].mbKnownPrime == true ) )
	{
		mbKnownPrime = mxKnownFactors[ 0 ].miPower == 1;
		mbKnownComposite = !mbKnownPrime;
	}

	if( mxKnownFactors.size() > 1 )
	{
		mbKnownComposite = true;
	}

	if( mbKnownComposite && ( mxKnownFactors.size() == 1 ) )
	{
		mxKnownFactors[ 0 ].mbKnownComposite = true;
	}
}

#endif
