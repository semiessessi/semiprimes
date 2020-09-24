#include "Wheel.h"

#include "../Number/Factorisation.h"
#include "../Number/Number.h"

static const uint64_t uWheel3Cutoff = 150000;

Factorisation Wheel3( const Number& xNumber )
{
	const unsigned int auDiffs[] = { 4, 2 };
    // SE - TODO: this is only really good up to 32-bit factors.
    Number xWorkingValue = xNumber;
    Factorisation xResult( xNumber );
    uint64_t uTest = 7;
    int iDiff = 0;
    while( xWorkingValue > ( ( uTest * uTest ) - 1 ) )
    {
        if( ( xWorkingValue % uTest ) == 0 )
        {
            xResult.mbKnownComposite = true;
            Factorisation xNew( uTest, true );
            xNew.miPower = 0;
            while( ( xWorkingValue % uTest ) == 0 )
            {
                ++xNew.miPower;
                xWorkingValue /= uTest;
            }
            xResult.mxKnownFactors.push_back( xNew );
        }

        uTest += auDiffs[ iDiff ];
        iDiff ^= 1;

        if( uTest > uWheel3Cutoff )
        {
            xResult.mxKnownFactors.push_back( Factorisation( xWorkingValue ) );
            return xResult;
        }
    }

    if( xResult.mxKnownFactors.empty() )
    {
        xResult.mbKnownPrime = true;
    }
    else if( xWorkingValue > 1 )
    {
        xResult.mxKnownFactors.push_back( Factorisation( xWorkingValue, true ) );
    }

    return xResult;
}
