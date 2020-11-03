#include "../../../Number/Number.h"

#include <intrin.h>


// this is based on something I believe to be 'Knuth's Algorithm D'
// .. finding good reference on the internet is difficult so the
// rough algorithm has been adapted to 
Number AlgorithmD( const Number& xNumerator, const Number& xDenominator, Number& xRemainder )
{
    Number xQuotient = 0;
    xRemainder = 0;

    // 'normalise' the divisor and dividend so the high order bit is set on the divisor
    // 
    unsigned long uShifts = 0;
    _BitScanReverse64( &uShifts, xDenominator.MostSignificantLimb() );
    uShifts = 63ULL - uShifts;
    Number xDividend = xNumerator << uShifts;
    Number xDivisor = xDenominator << uShifts;

    const uint64_t uM = xDividend.GetLimbCount();
    const uint64_t uN = xDivisor.GetLimbCount();

    // unconditionally add an extra limb for the  divisionloop to be safe.
    xDividend.AddZeroLeadingLimb();

    // 'school' division
    for( int iK = static_cast< int >( uM - uN ); iK >= 0; --iK )
    {
        uint64_t uLimbHigh = xDividend.GetLimb( uN + iK );
        uint64_t uLimbLow = xDividend.GetLimb( uN + iK - 1 );
        uint64_t uRHat = 0;
        // note the top part can be any value, so the worst case large result has the high bits as:
        //   0xFFFFFFFFFFFFFFFF
        // the divisor being normalised is somewhere between values:
        //   0x8000000000000000-0xFFFFFFFFFFFFFFFF
        // this overflows a 128/64 -> 64 divisiom

        // the leading zero makes this safe the first time in. the top part is always zeroes.

        bool bOverflow = uLimbHigh > xDivisor.MostSignificantLimb();
        uint64_t uQHat = 0;
        if( bOverflow )
        {
            // overflow case needs correction
            uLimbHigh -= xDivisor.MostSignificantLimb();
            uQHat = _udiv128(
                uLimbHigh, uLimbLow, xDivisor.MostSignificantLimb(), &uRHat );
            //++xQuotient;
            uRHat = xDivisor.GetLimb( uN - 1 );
        }
        else
        {
            // ... its working !!!
            uQHat = _udiv128(
                uLimbHigh, uLimbLow, xDivisor.MostSignificantLimb(), &uRHat );
        }

        // temp.

        xQuotient.InplaceLimbShiftLeft( 1 );
        xQuotient |= uQHat;
    }

    return xQuotient;
}
