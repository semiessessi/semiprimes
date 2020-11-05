#include "../../Number/Number.h"

// SE - TODO: fix.
Number BabylonianSquareRoot_NoRemainder( const Number& xNumber )
{
    Number xResult = xNumber;
    Number xTestValue = 1;
    bool bTest = true;
    while( bTest )
    {
        xResult += xTestValue;
        xResult >>= 1;
        xTestValue = xNumber / xResult;

        bTest = ( xResult >= xTestValue )
            ? ( ( xResult - xTestValue ) > 1 )
            : ( ( xTestValue - xResult ) > 1 );
    }

    if( xResult > xTestValue )
    {
        // this is a pain i guess...
        if( xResult * xResult == xNumber )
        {
            return xResult;
        }

        return xTestValue;
    }
    
    return xResult;
}

Number BabylonianSquareRoot( const Number& xNumber, Number& xRemainder )
{
    Number xResult = BabylonianSquareRoot_NoRemainder( xNumber );
    xRemainder = xNumber - xResult * xResult;
    return xResult;
}
