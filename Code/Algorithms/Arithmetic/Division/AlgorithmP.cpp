#include "../../../Number/Number.h"

// this algorithm is based on polynomial long division where we note that the
// base, b = 2^64, can be seen as the variable in a polynomial formed by the
// digit representation of a number...

// each step is treated as a new division and the polynomial product
// approximated by normal multiplication, noting that the 
Number AlgorithmP(
    const Number& xNumerator,
    const Number& xDenominator,
    Number& xRemainder ) noexcept
{
    Number xQuotient = 0;
    Number xTest = 0;
    xRemainder = xNumerator;
    const uint64_t uM = xRemainder.GetLimbCount();
    const uint64_t uN = xDenominator.GetLimbCount();
    xRemainder.AddZeroLeadingLimb();
    for( int iLimb = static_cast< int >( uM - uN ); iLimb >= 0; --iLimb )
    {
        // divide the leading term only, i.e. the coefficient of
        // the largest power of b
        uint64_t uDummy;
        uint64_t uQuotientLimb = 0xFFFFFFFFFFFFFFFF;
        if( xRemainder.GetLimb( iLimb + uN )
            < xDenominator.MostSignificantLimb() )
        {
            uQuotientLimb = _udiv128(
                xRemainder.GetLimb( iLimb + uN ), // this is the previous limb effectively.
                xRemainder.GetLimb( iLimb + uN - 1 ),
                xDenominator.MostSignificantLimb(),
                &uDummy );
        }
        // else the quotient limb must be the biggest possible.

        // work out the remainder by multiply and subtract
        xTest = xDenominator * uQuotientLimb;
        // trim leading zeroes.
        // adjust it so its positive
        while( xTest.GreaterOrEqualToWithOffset( xRemainder, iLimb ) )
        {
            xTest.InplaceSubAtLimbOffset( xDenominator, iLimb );
            --uQuotientLimb;
        }

        xQuotient.SetLimb( iLimb, uQuotientLimb );
        xRemainder -= xTest;
    }

    return xQuotient;
}
