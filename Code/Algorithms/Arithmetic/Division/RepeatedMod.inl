#include "../../../Number/Number.h"

#include <cstdint>

Number GeneralisedReciprocal( const Number& xNumber )
{
    uint64_t uMSB = xNumber.MostSignificantBitPosition() + 1;
    Number xR = ( 1 << uMSB );
    Number xS = xR;
    while( true )
    {
        xR = ( xR << 1 ) - ( ( xNumber * ( ( xR * xR ) >> uMSB ) ) >> uMSB );
        if( xR < xS )
        {
            break;
        }
        xS = xR;
    }
    Number xY = 1 << ( uMSB << 1 );
    while( xY > xNumber * xR )
    {
        --xR;
        xY += xNumber;
    }

    return xR;
}

Number RepeatedMod( const Number& xNumber, const Number& xReciprocal, const Number& xModulus )
{
    Number xX = xNumber;
    int64_t iS = xReciprocal.MostSignificantBitPosition() << 1;
    Number xDiv = 0;
    do
    {
        Number xD = ( xX * xReciprocal ) >> iS;
        xX -= xD;
        if( xX >= xNumber )
        {
            xX -= xNumber;
            ++xD;
        }
        //xDiv += xD;
    } while( xX < xNumber );

    return xX;
}
