
#include "../../Number/Factorisation.h"
#include "../../Number/Number.h"

static const int kiRhoTestLimit = 500000;
static const int kiSubTestLimit = 100;

#define MOD_INNER_LOOP (1)

uint64_t GetWheelBound();

Factorisation PollardRho( const Number& xNumber )
{
    Number xX = 2;
    Number xY = 2;
    Number xD = 1;
    Number xRemainingValue = xNumber;
    Factorisation xResult( xNumber );
    for( int i = 0; i < kiRhoTestLimit; i += kiSubTestLimit )
    {
        for( int j = i; j < i + kiSubTestLimit; ++j )
        {
            xX = ( xX * xX + 1 ) % xNumber;
            xY = ( xY * xY + 1 ) % xNumber;
            xY = ( xY * xY + 1 ) % xNumber;
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
        if( xD != 1 )
        {
            xResult.mbKnownComposite = true;
            Factorisation xNew( xD, xD < GetWheelBound() );
            xNew.miPower = 1;
            xRemainingValue /= xD;
            xResult.mxKnownFactors.push_back( xNew );

            break;
        }

        if( xD == xNumber )
        {
            // rewind...
            for( int j = i; j < i + kiSubTestLimit; ++j )
            {
                xX = ( xX * xX + 1 ) % xNumber;
                xY = ( xY * xY + 1 ) % xNumber;
                xY = ( xY * xY + 1 ) % xNumber;
                xD = xNumber.GCD(
                    ( xX > xY )
                    ? xX - xY
                    : xY - xX );
                if( xD != 1 )
                {
                    xResult.mbKnownComposite = true;
                    Factorisation xNew( xD, false );
                    xNew.miPower = 1;
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
    }

    if( xRemainingValue > 1 )
    {
        xResult.mxKnownFactors.push_back( xRemainingValue );
    }

    return xResult;
}