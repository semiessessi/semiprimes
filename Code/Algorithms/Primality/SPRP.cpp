#include "SPRP.h"

#include "../../Number/Factorisation.h"
#include "../../Number/Number.h"

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
    uint64_t uBase = uNumber % uModulus;
    while( true )
    {
        if( ( uRemainingPower & 0x1 ) == 1 )
        {
            uReturnValue = ModMul( uReturnValue, uBase, uModulus );
        }
        uRemainingPower >>= 1;
        if( uRemainingPower == 0 )
        {
            break;
        }
        uBase = ModMul( uBase, uBase, uModulus );
    }
    
    return uReturnValue;
}

Number ModExpRightToLeft( const uint64_t uNumber, const Number& xExponent, const Number& xModulus )
{
    return Number( uNumber ).ModExp( xExponent, xModulus );
}

template< int N >
bool SmallSPRP( const uint64_t uNumber )
{
    // find a * 2^b + 1 == uNumber
    uint64_t uA = ( uNumber - 1 ) >> 1;
    uint64_t uB = 1;

    if( uA < 2 )
    {
        return false;
    }

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

template< int N >
bool SPRP( const Number& xNumber )
{
    // find a * 2^b + 1 == xNumber
    Number xA = ( xNumber - 1 ) >> 1;
    uint64_t uB = 1;

    if( xA < 2 )
    {
        return false;
    }

    while( ( xA & 0x1 ) == 0 )
    {
        ++uB;
        xA >>= 1;
    }

    Number xPowerTest = ModExpRightToLeft( N, xA, xNumber );
    if( xPowerTest == 1 )
    {
        return true;
    }

    const Number xMinusOne = xNumber - 1;
    if( xPowerTest == xMinusOne )
    {
        return true;
    }

    for( uint64_t i = 0; i < uB; ++i )
    {
        xPowerTest.InplaceModMul( Number( xPowerTest ), xNumber );
        if( xPowerTest == xMinusOne )
        {
            return true;
        }
    }

    return false;
}

// for testing
bool SPRP2( const Number& xNumber )
{
    return SPRP< 2 >( xNumber );
}

bool SmallSPRP2( const Number& xNumber )
{
    if( xNumber.GetLimbCount() == 1 )
    {
        return SmallSPRP< 2 >( xNumber.LeastSignificantLimb() );
    }
    return false;
}

Factorisation SPRPTests( const Number& xNumber )
{
    Factorisation xResult( xNumber );
    xResult.szProofName = "strong Fermat probable prime tests";
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

    xResult.mbKnownComposite = !SPRP< 2 >( xNumber );
    if( xResult.mbKnownComposite == true )
    {
        return xResult;
    }

    // SE - TODO: PSW thingy

    // SE - TODO: refactor

    xResult.mbKnownComposite = !SPRP< 3 >( xNumber );
    if( xResult.mbKnownComposite == true )
    {
        return xResult;
    }
    xResult.mbKnownComposite = !SPRP< 5 >( xNumber );
    if( xResult.mbKnownComposite == true )
    {
        return xResult;
    }
    xResult.mbKnownComposite = !SPRP< 7 >( xNumber );
    if( xResult.mbKnownComposite == true )
    {
        return xResult;
    }
    xResult.mbKnownComposite = !SPRP< 11 >( xNumber );
    if( xResult.mbKnownComposite == true )
    {
        return xResult;
    }
    xResult.mbKnownComposite = !SPRP< 13 >( xNumber );
    if( xResult.mbKnownComposite == true )
    {
        return xResult;
    }
    xResult.mbKnownComposite = !SPRP< 17 >( xNumber );
    if( xResult.mbKnownComposite == true )
    {
        return xResult;
    }
    xResult.mbKnownComposite = !SPRP< 19 >( xNumber );
    if( xResult.mbKnownComposite == true )
    {
        return xResult;
    }
    xResult.mbKnownComposite = !SPRP< 23 >( xNumber );
    if( xResult.mbKnownComposite == true )
    {
        return xResult;
    }
    xResult.mbKnownComposite = !SPRP< 29 >( xNumber );
    if( xResult.mbKnownComposite == true )
    {
        return xResult;
    }
    xResult.mbKnownComposite = !SPRP< 31 >( xNumber );
    if( xResult.mbKnownComposite == true )
    {
        return xResult;
    }
    xResult.mbKnownComposite = !SPRP< 37 >( xNumber );
    if( xResult.mbKnownComposite == true )
    {
        return xResult;
    }

    return xResult;
}
