#include "../../../Number/Number.h"

#include <intrin.h>

// this is based on Knuth's Algorithm D
// the original implementation does something clever and a bit faster to
// fix up the initial guess at the quotient digit.
// this alternative implementation does something simpler in its place
// and is still guaranteed to be faster than binary division

#define OVERFLOW_CARE (1)

Number AlgorithmD( const Number& xNumerator, const Number& xDenominator, Number& xRemainder )
{
    Number xQuotient = 0;
    // 'normalise' the divisor and dividend so the high order bit is set on the divisor
    // 
    unsigned long uShifts = 0;
    _BitScanReverse64( &uShifts, xDenominator.MostSignificantLimb() );
    uShifts = 63ULL - uShifts;
    xRemainder = xNumerator;
    xRemainder <<= uShifts;
    Number xDivisor = xDenominator;
    xDivisor <<= uShifts;
    Number xApproximationTest = 0;
    Number xReducedDividend = 0;

    const uint64_t uM = xRemainder.GetLimbCount();
    const uint64_t uN = xDivisor.GetLimbCount();
    // unconditionally add an extra limb for the division loop to be safe.
    xRemainder.AddZeroLeadingLimb();

    // 'school' division
    for( int iJ = static_cast< int >( uM - uN ); iJ >= 0; --iJ )
    {
        // the leading zero makes this 'safe' the first time in...
        // then subtractions keep it safe. (i think)
        uint64_t uMostSignificantLimb = xDivisor.MostSignificantLimb();
#if OVERFLOW_CARE
        const bool bOverflow = xRemainder.GetLimb( uN + iJ ) >= uMostSignificantLimb;
        uint64_t uApproximateQuotient = 0xFFFFFFFFFFFFFFFF;
        if( !bOverflow )
        {
#else
        uint64_t
#endif
            uApproximateQuotient = _udiv128(
                xRemainder.GetLimb( uN + iJ ),
                xRemainder.GetLimb( uN + iJ - 1 ),
                uMostSignificantLimb, &uMostSignificantLimb );
#if OVERFLOW_CARE
        }
#endif

        // multiply to test the quotient guess
        // ... but if the result is negative we need to adjust it
        xApproximationTest = xDivisor;
        xApproximationTest *= uApproximateQuotient;
        const bool bNegative = xApproximationTest.GreaterOrEqualToWithOffset( xRemainder, iJ );
        if( bNegative )
        {
            xApproximationTest -= xDivisor;
            const bool bStillNegative = xApproximationTest.GreaterOrEqualToWithOffset( xRemainder, iJ );
            uApproximateQuotient -= bStillNegative ? 2 : 1;
            if( bStillNegative )
            {
                xApproximationTest -= xDivisor;
            }
        }
       
        if( uApproximateQuotient != 0 )
        {
            xQuotient.SetLimb( iJ, uApproximateQuotient );
        }

        // subtract the test from the dividend and its done.
        xRemainder.InplaceSubAtLimbOffset( xApproximationTest, iJ );

        // SE - NOTE: this feels sloppy.
        // put back limbs we might need (!)
        if( xRemainder.GetLimbCount() < ( uN + iJ ) )
        {
            xRemainder.ZeroFillLimbResize( uN + iJ );
        }
    }

    // SE - TODO: are we ever left with leading zeros where we had to subtract?
    // i don't think so - i think that only happens for big digits... ?

    // fixup remainder.
    xRemainder >>= uShifts;

    return xQuotient;
}
