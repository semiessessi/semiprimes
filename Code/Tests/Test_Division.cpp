#include "../Number/Number.h"

bool ModTests()
{
    const char* const szString =
        "111111111111111111111111111111111111111111111111111"
        "111111111111111111111111111111111111111111111111111"
        "111111111111111111111111111111111111111111111111111"
        "111111111111111111111111111111111111111111111111111"
        "111111111111111111111111111111111111111111111111111"
        "111111111111111111111111111111111111111111111111111"
        "111111111111111111111111111111111111111111111111111"
        "111111111111111111111111111111111111111111111111111";
    const Number xBigModulus =
        1000000000000000000000000000000000000000000000000000z;
    const Number xBigResult =
        111111111111111111111111111111111111111111111111111z;
    const size_t uLength = strlen( szString );
    const size_t uLesserLength = strlen( "1000000000000000000000000000000000000000000000000000" );
    for( int i = 0; i < uLength; ++i )
    {
        if( ( Number( szString + i ) % 10 ) != 1 )
        {
            return false;
        }

        if( i < ( uLength - uLesserLength ) )
        {
            if( ( Number( szString + i ) % xBigModulus ) != xBigResult )
            {
                return false;
            }
        }
    }

    return true;
}
