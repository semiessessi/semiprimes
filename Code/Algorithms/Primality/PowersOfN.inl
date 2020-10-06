#include "../Number/Factorisation.h"
#include "../Number/Number.h"

template< int N >
Factorisation PowersOf( const Number& xNumber )
{
    int iPowers = 0;
    Number xWorkingValue = xNumber;

    while( ( xWorkingValue.LeastSignificantLimb() != 0 )
        && ( ( xWorkingValue % N ) == 0 ) )
    {
        xWorkingValue /= N;
        ++iPowers;
    }

    Factorisation xResult( xNumber );
    xResult.mbKnownComposite = iPowers > 0;
    if( xResult.mbKnownComposite )
    {
        Factorisation xFactorisation( N );
        xFactorisation.mbKnownPrime = true;
        xFactorisation.miPower = iPowers;
        xResult.mxKnownFactors.push_back( xFactorisation );
        // SE - TODO: equality test.
        if( xWorkingValue > 1 )
        {
            xResult.mxKnownFactors.push_back( Factorisation( xWorkingValue ) );
        }
    }

    return xResult;
}
