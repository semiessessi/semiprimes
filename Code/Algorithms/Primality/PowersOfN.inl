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

    static const std::string xName =
        std::string( "power of " ) + std::to_string( N ) + " removal";
    Factorisation xResult( xNumber );
    xResult.mbKnownComposite = iPowers > 0;
    if( xResult.mbKnownComposite )
    {
        Factorisation xFactorisation( N );
        xFactorisation.mbKnownPrime = true;
        xFactorisation.miPower = iPowers;
        xFactorisation.szFactoringAlgorithm = xName.c_str();
        xFactorisation.szProofName = "wheel setup";
        xResult.mxKnownFactors.push_back( xFactorisation );
        // SE - TODO: equality test.
        if( xWorkingValue > 1 )
        {
            xResult.mxKnownFactors.push_back( Factorisation( xWorkingValue ) );
        }
    }

    return xResult;
}
