#include "../../Number/Number.h"

Number BinarySquareRoot( const Number& xNumber )
{
    Number xResult = 0;
    Number xRemainder = 0;
    const uint64_t uPowerOf4BitCount =
        xNumber.MostSignificantBitPosition() & 0xFFFFFFFFFFFFFFFEULL;
    Number xWorkingValue = xNumber;
    Number xTestValue = 1z << uPowerOf4BitCount;
    while( xTestValue > 0 )
    {
        if( xWorkingValue > ( xResult + xTestValue ) )
        {
            xWorkingValue -= xTestValue;
            xWorkingValue -= xResult;
            xResult >>= 1;
            xResult += xTestValue;
        }
        else
        {
            xResult >>= 1;
        }

        xTestValue >>= 2;
    }

    return xResult;
}
