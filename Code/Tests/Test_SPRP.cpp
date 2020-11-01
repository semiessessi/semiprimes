//#include "../Algorithms/Primality/SPRP.h"
#include "../Number/Number.h"

bool SPRP2( const Number& xNumber );
bool SmallSPRP2( const Number& xNumber );

bool SPRPTests()
{
    Number xTestBase = 615289153;

    while( xTestBase > 0 )
    {
        if( SmallSPRP2( xTestBase ) != SPRP2( xTestBase ) )
        {
            return false;
        }

        xTestBase >>= 1;
    }

    if( SPRP2( 2047 ) == false )
    {
        return false;
    }

    if( SmallSPRP2( 615289153 ) == false )
    {
        return false;
    }

    if( SPRP2( 615289153 ) == false )
    {
        return false;
    }

    return true;
}
