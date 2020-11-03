#include "../Number/Number.h"
#include "../Algorithms/Arithmetic/Division/AlgorithmD.h"
#include "../Algorithms/Arithmetic/Division/BinaryDivision.h"

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

bool AlgorithmDTests()
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
    Number xRemainder = 0;
    Number xNuisance = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFz;
    Number xLesserNuisance = 0x800000000000000000000000000000000000000000000000z;
    if( BinaryDivision( xNuisance, xLesserNuisance, xRemainder )
        != AlgorithmD( xNuisance, xLesserNuisance, xRemainder ) )
    {
        return false;
    }

    // compare Algorithm D with Binary Division...
    for( int i = 0; i < uLength; ++i )
    {
        if( BinaryDivision( Number( szString + i ), xBigModulus, xRemainder )
            != AlgorithmD( Number( szString + i ), xBigModulus, xRemainder ) )
        {
            return false;
        }
    }

    return true;
}