
#include "../Primality/Wheel.h"
#include "../../Number/Factorisation.h"
#include "../../Number/Number.h"

Number GetWheelBound();

Factorisation PollardPMinus1( const Number& xNumber )
{
    Factorisation xResult( xNumber );

    Number xRemainingValue = xNumber;
    Number xA = 2;

    // SE - TODO: more primes.
    size_t uPrimeCount = sizeof( aiWheelPrimes ) / sizeof( aiWheelPrimes[ 0 ] );
    while( true )
    {
        xA = 1;
        Number xE = 1;
        for( size_t i = 0; i < uPrimeCount; ++i )
        {
            xA.InplaceModMul( (2z).ModExp( aiWheelPrimes[ i ], xNumber ), xNumber );
        }

        xA = xA.ModExp( xNumber.MostSignificantBitPosition(), xNumber );

        const Number xGCD = xNumber.GCD( xA - 1 );
        if( xGCD == 1 )
        {
            break;
        }

        if( xGCD != xNumber )
        {
            xResult.mbKnownComposite = true;
            const bool bPrimeByWheel = xGCD < GetWheelBound();
            Factorisation xNew( xGCD, bPrimeByWheel );
            xNew.miPower = 1;
            xNew.szFactoringAlgorithm = "Pollard's p-1 method";
            if( bPrimeByWheel )
            {
                xNew.szProofName = "bound set by trial division";
            }
            xRemainingValue /= xGCD;
            xResult.mxKnownFactors.push_back( xNew );
            break;
        }

        uPrimeCount >>= 2;

        if( uPrimeCount < 10 )
        {
            break;
        }
    }

    if( xRemainingValue != xNumber )
    {
        xResult.mxKnownFactors.push_back( Factorisation(
            xRemainingValue, xRemainingValue < GetWheelBound() ) );
    }

    return xResult;
}
