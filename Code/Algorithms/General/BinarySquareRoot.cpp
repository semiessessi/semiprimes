#include "../../Number/Number.h"

Number BinarySquareRoot( const Number& xNumber, Number& xRemainder )
{
    Number xResult = 0;
    xRemainder = xNumber;
    const uint64_t uPowerOf4BitCount =
        xNumber.MostSignificantBitPosition() & 0xFFFFFFFFFFFFFFFEULL;
    Number xTestValue = 1z << uPowerOf4BitCount;
        //( ( uPowerOf4BitCount < 1 ) ? 1 : uPowerOf4BitCount );
    while( xTestValue > 0 )
    {
        xRemainder -= xTestValue;
        if( xRemainder >= xResult )
        {
            
            xRemainder -= xResult;
            xResult >>= 1;
            xResult += xTestValue;
        }
        else
        {
            xRemainder += xTestValue;
            xResult >>= 1;
        }

        xTestValue >>= 2;
    }

    return xResult;
}
