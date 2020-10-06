#include "Number.h"

#include <intrin.h>

Number Number::DivMod(
    const Number& xNumerator,
    const int64_t iDenominator,
    int64_t& iRemainder )
{
    const bool bNegativeDenominator = ( iDenominator < 0 );
    Number xReturnValue = DivMod( xNumerator,
        static_cast< uint64_t >(
            bNegativeDenominator
            ? -iDenominator
            : iDenominator ),
        reinterpret_cast< uint64_t& >( iRemainder ) );
    iRemainder = ( xNumerator.mbNegative ) ? -iRemainder : iRemainder;
    xReturnValue.mbNegative =
        bNegativeDenominator
        ? !xNumerator.mbNegative
        : xNumerator.mbNegative;
    return xReturnValue;
}

Number Number::DivMod(
    const Number& xNumerator,
    const uint64_t uDenominator,
    uint64_t& uRemainder )
{
    Number xReturnValue = 0;
    xReturnValue.mxLimbs.reserve( xNumerator.mxLimbs.size() );
    size_t uLimb = xNumerator.mxLimbs.size();
    uRemainder = 0;
    while( uLimb != 0 )
    {
        --uLimb;
        xReturnValue.InplaceLimbShiftLeft( 1 );
        xReturnValue += _udiv128(
            uRemainder,
            xNumerator.mxLimbs[ uLimb ],
            uDenominator,
            &uRemainder );
    }

    xReturnValue.mbNegative = xNumerator.mbNegative;

    return xReturnValue;
}

Number Number::DivMod(
    const Number& xNumerator,
    const Number& xDenominator,
    Number& xRemainder )
{
    // SE - TODO: division innit...
    return 0z;
}

uint64_t Number::Mod(
    const Number& xNumerator,
    const uint64_t uDenominator )
{
    uint64_t uRemainder = 0;
    for( size_t uLimb = xNumerator.mxLimbs.size();
        uLimb != 0; --uLimb )
    {
        _udiv128(
            uRemainder,
            xNumerator.mxLimbs[ uLimb - 1 ],
            uDenominator,
            &uRemainder );
    }

    return uRemainder;
}
