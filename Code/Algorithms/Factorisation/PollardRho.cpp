
#include "../../Number/Factorisation.h"
#include "../../Number/Number.h"
//#include "../Arithmetic/Division/RepeatedMod.h"

static const int kiRhoTestLimit =
#if _DEBUG
    25000
#else
    1250000
#endif
;
static const int kiSubTestLimit = 100;

#define MOD_INNER_LOOP (1)

Number GetWheelBound();

Factorisation PollardRho( const Number& xNumber )
{
    Number xX = 2;
    Number xY = 2;
    Number xD = 1;
    //Number xR = GeneralisedReciprocal( xNumber );
    Number xRemainingValue = xNumber;
    Factorisation xResult( xNumber );
    for( int i = 0; i < kiRhoTestLimit; i += kiSubTestLimit )
    {
        for( int j = i; j < i + kiSubTestLimit; ++j )
        {
            xX = ( xX * xX + 1ULL ) % xNumber;
            xY = ( xY * xY + 1ULL );//% xNumber;
            xY = ( xY * xY + 1ULL ) % xNumber;
            xD *= ( xX > xY )
                ? xX - xY
                : xY - xX;
#if MOD_INNER_LOOP
            const Number xMod = xD % xNumber;
            if( xMod == 0 )
            {
                xD = ( xX > xY )
                    ? xX - xY
                    : xY - xX;
                break;
            }
            xD = xMod; // keeps muls faster??
#endif
        }

        xD = xNumber.GCD( xD );

        if( xD == xNumber )
        {
            // rewind...
            for( int j = i; j < i + kiSubTestLimit; ++j )
            {
                xX = ( xX * xX + 1ULL ) % xNumber;
                xY = ( xY * xY + 1ULL ) % xNumber;
                xY = ( xY * xY + 1ULL ) % xNumber;
                xD = xNumber.GCD(
                    ( xX > xY )
                    ? xX - xY
                    : xY - xX );
                if( xD != 1 )
                {
                    xResult.mbKnownComposite = true;
                    const bool bPrimeByWheel = xD < GetWheelBound();
                    Factorisation xNew( xD, bPrimeByWheel );
                    xNew.miPower = 1;
                    xNew.szFactoringAlgorithm = "Pollard's rho";
                    if( bPrimeByWheel )
                    {
                        xNew.szProofName = "bound set by trial division";
                    }
                    xRemainingValue /= xD;
                    xResult.mxKnownFactors.push_back( xNew );

                    break;
                }
            }

            if( xD != 1 )
            {
                break;
            }
        }

        if( xD != 1 )
        {
            xResult.mbKnownComposite = true;
            const bool bPrimeByWheel = xD < GetWheelBound();
            Factorisation xNew( xD, bPrimeByWheel );
            xNew.miPower = 1;
            xNew.szFactoringAlgorithm = "Pollard's rho";
            if( bPrimeByWheel )
            {
                xNew.szProofName = "bound set by trial division";
            }
            xRemainingValue /= xD;
            xResult.mxKnownFactors.push_back( xNew );
            break;
        }
    }

    if( xRemainingValue > 1 )
    {
        const bool bPrimeByWheel = xRemainingValue < GetWheelBound();
        Factorisation xNew( xRemainingValue, bPrimeByWheel );
        if( bPrimeByWheel )
        {
            xNew.szProofName = "bound set by trial division";
        }
        xNew.szFactoringAlgorithm = "Pollard's rho";
        xResult.mxKnownFactors.push_back( xNew );
    }

    return xResult;
}