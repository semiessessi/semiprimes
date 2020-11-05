#include "../Number/Factorisation.h"
#include "../Number/Number.h"
#include "../Algorithms/Factorisation/PollardRho.h"

bool TestSquareRootNumber( const Number& xA )
{
    Number xLowTest = xA.SquareRoot();
    Number xHighTest = xLowTest + 1ULL;
    xLowTest = xLowTest * xLowTest;
    xHighTest = xHighTest * xHighTest;

    return ( xLowTest <= xA ) && ( xHighTest > xA );
}

bool TestSquareRoot()
{
    Number xTest =
        11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111z;

    while( xTest > 1 )
    {
        if( !TestSquareRootNumber( xTest ) )
        {
            return false;
        }
        xTest /= 10;
    }

    xTest =
        0x10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000z;

    while( xTest > 1 )
    {
        if( !TestSquareRootNumber( xTest ) )
        {
            return false;
        }
        xTest >>= 1;
    }

    return true;
}
