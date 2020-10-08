#include "../../../Number/Number.h"

Number BinaryDivision( const Number& xNumerator, const Number& xDenominator, Number& xRemainder )
{
    Number xQuotient;
    xRemainder = 0;
    const size_t uBitCount = xNumerator.MostSignificantBitPosition();
    for( size_t i = 0; i < uBitCount; ++i )
    {
        xRemainder <<= 1;
        xRemainder |= xNumerator.GetBit( uBitCount - i - 1 ) ? 1 : 0;
        if( xRemainder > xDenominator )
        {
            xRemainder -= xDenominator;
            xQuotient.SetBit( uBitCount - i - 1 );
        }
    }

    return xQuotient;
}
