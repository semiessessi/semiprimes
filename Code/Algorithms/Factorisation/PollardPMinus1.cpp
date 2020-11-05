
#include "../Primality/Erastothenes.h"
#include "../../Number/Factorisation.h"
#include "../../Number/Number.h"

Number GetWheelBound();

Factorisation PollardPMinus1( const Number& xNumber )
{
    Factorisation xResult( xNumber );
    const uint64_t uSmoothnessBound = 500000;
    Number xRemainingValue = xNumber;
    Number xA = 2;

    InitialisePrimesUpTo( uSmoothnessBound );
    size_t uPrimeCount = GetSievedPrimeCount();
    while( true )
    {
        xA = 1;
        Number xE = 1;
        for( size_t i = 0; i < uPrimeCount; ++i )
        {
            xA.InplaceModMul( ( 2z ).ModExp( GetSievedPrimes()[ i ], xNumber ), xNumber );
        }

        xA = xA.ModExp( xNumber.MostSignificantBitPosition(), xNumber );

        const Number xGCD = xNumber.GCD( xA - 1ULL );
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
        const bool bPrimeByWheel = xRemainingValue < GetWheelBound();
        Factorisation xNew( xRemainingValue, bPrimeByWheel );
        xNew.szFactoringAlgorithm = "Pollard's p-1 method";
        if( bPrimeByWheel )
        {
            xNew.szProofName = "bound set by trial division";
        }
        xResult.mxKnownFactors.push_back( xNew );
    }

    return xResult;
}
