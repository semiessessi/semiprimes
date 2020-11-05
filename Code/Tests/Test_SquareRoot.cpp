#include "../Number/Factorisation.h"
#include "../Number/Number.h"
#include "../Algorithms/Factorisation/PollardRho.h"

#include "../Algorithms/General/BabylonianSquareRoot.h"
#include "../Algorithms/General/BinarySquareRoot.h"

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

bool TestBabylonianSquareRoot()
{
    Number xTest =
        11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111z;
    Number xDummy;
    while( xTest > 1 )
    {
        if( BinarySquareRoot( xTest, xDummy )
            != BabylonianSquareRoot_NoRemainder( xTest ) )
        {
            return false;
        }
        xTest /= 10;
    }

    xTest =
        0x10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000z;

    while( xTest > 1 )
    {
        if( BinarySquareRoot( xTest, xDummy )
            != BabylonianSquareRoot_NoRemainder( xTest ) )
        {
            return false;
        }
        xTest >>= 1;
    }

    return true;
}
