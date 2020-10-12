#include "PowersOf2.h"

#include "../../Number/Factorisation.h"
#include "../../Number/Number.h"

Factorisation PowersOf2( const Number& xNumber )
{
    int iPowers = 0;
    Number xWorkingValue = xNumber;
    // go fast if whole limbs are zeroed out
    while( xWorkingValue.LeastSignificantLimb() == 0 )
    {
        iPowers += 64;
        xWorkingValue.InplaceLimbShiftRight( 1 );
    }

    // test remaining bits
    while( ( xWorkingValue.LeastSignificantLimb() != 0 )
        && ( ( xWorkingValue & 0x1 ) == 0 ) )
    {
        //xWorkingValue >>= 1;
        xWorkingValue /= 2;
        ++iPowers;
    }

    Factorisation xResult( xNumber );
    xResult.mbKnownComposite = iPowers > 0;
    if( xResult.mbKnownComposite )
    {
        Factorisation xTwoFactorisation( 2z );
        xTwoFactorisation.mbKnownPrime = true;
        xTwoFactorisation.miPower = iPowers;
        xResult.mxKnownFactors.push_back( xTwoFactorisation );
        if( xWorkingValue > 1 )
        {
            xResult.mxKnownFactors.push_back( Factorisation( xWorkingValue ) );
        }
    }

    return xResult;
}
