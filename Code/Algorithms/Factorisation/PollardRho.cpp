
#include "../../Number/Factorisation.h"
#include "../../Number/Number.h"

static const int kiRhoTestLimit = 10000;

Factorisation PollardRho( const Number& xNumber )
{
    Number xX = 2;
    Number xY = 2;
    Number xD = 1;
    Number xRemainingValue = xNumber;
    Factorisation xResult( xNumber );
    for( int i = 0; i < kiRhoTestLimit; ++i )
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
            xNew.miPower = 0;
            while( ( xRemainingValue % xD ) == 0z )
            {
                ++xNew.miPower;
                xRemainingValue /= xD;
            }
            xResult.mxKnownFactors.push_back( xNew );

            break;
        }
    }

    if( xRemainingValue > 1 )
    {
        xResult.mxKnownFactors.push_back( Factorisation( xRemainingValue ) );
    }

    return xResult;
}