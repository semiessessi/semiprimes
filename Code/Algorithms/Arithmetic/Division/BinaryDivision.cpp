#include "../../../Number/Number.h"

Number BinaryDivision( const Number& xNumerator, const Number& xDenominator, Number& xRemainder )
{
    Number xQuotient;
    xRemainder = 0;
    const size_t uBitCount = xNumerator.MostSignificantBitPosition() + 1;
    for( size_t i = uBitCount; i != 0; --i )
    {
        size_t uIndex = i - 1;
        xRemainder <<= 1;
        xRemainder |= xNumerator.GetBit( uIndex ) ? 1 : 0;
        if( xRemainder >= xDenominator )
        {
            xRemainder -= xDenominator;
            xQuotient.SetBit( uIndex );
        }
    }

    return xQuotient;
}
