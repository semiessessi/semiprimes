#include "Wheel.h"

#include "../Number/Factorisation.h"
#include "../Number/Number.h"

static const uint64_t uWheel3Cutoff = 150000;
static const uint64_t uWheel5Cutoff = 200000;

Factorisation Wheel3( const Number& xNumber )
{
	const unsigned int auDiffs[] = { 4, 2 };
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

Factorisation Wheel5( const Number& xNumber )
{
    const unsigned int auDiffs[] = { 6, 4, 2, 4, 2, 4, 6, 2 };
    Number xWorkingValue = xNumber;
    Factorisation xResult( xNumber );
    uint64_t uTest = 31;
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
        iDiff = ( iDiff + 1 ) & 7;

        if( uTest > uWheel5Cutoff )
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
