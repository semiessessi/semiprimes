#include "SPRP.h"

#include "../Number/Factorisation.h"
#include "../Number/Number.h"

#include <intrin.h>

uint64_t ModMul( const uint64_t uNumber, const uint64_t uMultiplicand, const uint64_t uModulus )
{
    uint64_t uUpperPart = 0;
    uint64_t uLowerPart = _umul128(
        uNumber, uMultiplicand, &uUpperPart );
    // only divide if necessary.
    if( ( uUpperPart != 0 ) || ( uLowerPart >= uModulus ) )
    {
        _udiv128(
            uUpperPart,
            uLowerPart,
            uModulus,
            &uLowerPart );
    }

    return uLowerPart;
}

uint64_t ModExpRightToLeft( const uint64_t uNumber, const uint64_t uExponent, const uint64_t uModulus )
{
    uint64_t uReturnValue = 1;
    uint64_t uRemainingPower = uExponent;
    while( true )
    {
        if( ( uRemainingPower & 0x1 ) == 1 )
        {
            uReturnValue = ModMul( uReturnValue, uNumber, uModulus );
        }
        uRemainingPower >>= 1;
        if( uRemainingPower == 0 )
        {
            break;
        }
        uReturnValue = ModMul( uReturnValue, uReturnValue, uModulus );
    }
    
    return uReturnValue;
}

template< int N >
bool SmallSPRP( const uint64_t uNumber )
{
    // find a * 2^b + 1 == uNumber
    uint64_t uA = ( uNumber - 1 ) >> 1;
    uint64_t uB = 1;

    while( ( uA & 0x1 ) == 0 )
    {
        ++uB;
        uA >>= 1;
    }

    uint64_t uPowerTest = ModExpRightToLeft( N, uA, uNumber );
    if( uPowerTest == 1 )
    {
        return true;
    }

    const uint64_t uMinusOne = uNumber - 1;
    if( uPowerTest == uMinusOne )
    {
        return true;
    }

    for( uint64_t i = 0; i < uB; ++i )
    {
        uPowerTest = ModMul( uPowerTest, uPowerTest, uNumber );
        if( uPowerTest == uMinusOne )
        {
            return true;
        }
    }

    return false;
}

Factorisation SPRPTests( const Number& xNumber )
{
    Factorisation xResult( xNumber );
    if( xNumber.GetLimbCount() == 1 )
    {
        uint64_t uNumber = xNumber.LeastSignificantLimb();
        
        xResult.mbKnownComposite = !SmallSPRP< 2 >( uNumber );
        if( xResult.mbKnownComposite == true )
        {
            return xResult;
        }

        if( uNumber < 2047 )
        {
            xResult.mbKnownPrime = !xResult.mbKnownComposite;
            return xResult;
        }

        xResult.mbKnownComposite = !SmallSPRP< 3 >( uNumber );
        if( xResult.mbKnownComposite == true )
        {
            return xResult;
        }

        if( uNumber < 1373653 )
        {
            xResult.mbKnownPrime = !xResult.mbKnownComposite;
            return xResult;
        }

        xResult.mbKnownComposite = !SmallSPRP< 5 >( uNumber );
        if( xResult.mbKnownComposite == true )
        {
            return xResult;
        }

        if( uNumber < 25326001 )
        {
            xResult.mbKnownPrime = !xResult.mbKnownComposite;
            return xResult;
        }

        xResult.mbKnownComposite = !SmallSPRP< 7 >( uNumber );
        if( xResult.mbKnownComposite == true )
        {
            return xResult;
        }

        if( uNumber < 3215031751 )
        {
            xResult.mbKnownPrime = !xResult.mbKnownComposite;
            return xResult;
        }

        xResult.mbKnownComposite = !SmallSPRP< 11 >( uNumber );
        if( xResult.mbKnownComposite == true )
        {
            return xResult;
        }

        if( uNumber < 2152302898747 )
        {
            xResult.mbKnownPrime = !xResult.mbKnownComposite;
            return xResult;
        }

        xResult.mbKnownComposite = !SmallSPRP< 13 >( uNumber );
        if( xResult.mbKnownComposite == true )
        {
            return xResult;
        }

        if( uNumber < 3474749660383 )
        {
            xResult.mbKnownPrime = !xResult.mbKnownComposite;
            return xResult;
        }

        xResult.mbKnownComposite = !SmallSPRP< 17 >( uNumber );
        if( xResult.mbKnownComposite == true )
        {
            return xResult;
        }

        if( uNumber < 341550071728321 )
        {
            xResult.mbKnownPrime = !xResult.mbKnownComposite;
            return xResult;
        }


        xResult.mbKnownComposite = !SmallSPRP< 19 >( uNumber );
        if( xResult.mbKnownComposite == true )
        {
            return xResult;
        }

        xResult.mbKnownComposite = !SmallSPRP< 23 >( uNumber );
        if( xResult.mbKnownComposite == true )
        {
            return xResult;
        }

        if( uNumber < 3825123056546413051 )
        {
            xResult.mbKnownPrime = !xResult.mbKnownComposite;
            return xResult;
        }

        xResult.mbKnownComposite = !SmallSPRP< 29 >( uNumber );
        if( xResult.mbKnownComposite == true )
        {
            return xResult;
        }

        xResult.mbKnownComposite = !SmallSPRP< 31 >( uNumber );
        if( xResult.mbKnownComposite == true )
        {
            return xResult;
        }

        xResult.mbKnownComposite = !SmallSPRP< 37 >( uNumber );
        xResult.mbKnownPrime = !xResult.mbKnownComposite;
        return xResult;
    }

    // SE - TODO: test bigger numbers.

    return xResult;
}
