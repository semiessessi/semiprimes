
#include "../Primality/Erastothenes.h"
#include "../../Number/Factorisation.h"
#include "../../Number/Number.h"

Number GetWheelBound();

Factorisation PollardPMinus1( const Number& xNumber )
{
    Factorisation xResult( xNumber );
    const uint64_t uSmoothnessBound =
#ifdef _DEBUG
        50000
#else
        1000000
#endif
        ;
    Number xRemainingValue = xNumber;
    Number xA = 2;
    Number xGCD = 1;

    InitialisePrimesUpTo( uSmoothnessBound );
    size_t uPrimeCount = GetSievedPrimeCount();
    while( true )
    {
        xA = 1;
        Number xE = 1;
        for( size_t i = 0; i < uPrimeCount; ++i )
        {
            xE = xA.ModExp( GetSievedPrimes()[ i ], xNumber );
            if( xE == 1 )
            {
                break;
            }

            // early out
            if( ( uPrimeCount & 0x1FFF ) == 0 )
            {
                xGCD = xNumber.GCD( xA - 1ULL );
                if( xGCD != 1 )
                {
                    break;
                }
            }
        }

        if( xGCD == 1 )
        {
            xA = xA.ModExp( xNumber.MostSignificantBitPosition(), xNumber );
            xGCD = xNumber.GCD( xA - 1ULL );
        }

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
        xNew.szFactoringAlgorithm = "cofactor from Pollard's p-1 method";
        if( bPrimeByWheel )
        {
            xNew.szProofName = "bound set by trial division";
        }
        xResult.mxKnownFactors.push_back( xNew );
    }

    return xResult;
}
