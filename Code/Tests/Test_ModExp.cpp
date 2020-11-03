#include <cstdint>

uint64_t ModExpRightToLeft(
    const uint64_t uNumber, const uint64_t uExponent, const uint64_t uModulus );

bool ModExpTests()
{
    uint64_t xTest = 24;

    while( xTest > 1 )
    {
        const uint64_t uResult =
            ModExpRightToLeft( 2, xTest, 0xFFFFFFFFFFFFFFFFULL );
        if( uResult != ( 1ULL << xTest ) )
        {
            return false;
        }

        --xTest;
    }

    const uint64_t uResult =
        ModExpRightToLeft( 2, 9613893, 615289153 );
    if( uResult != 204725292 )
    {
        return false;
    }

    return true;
}
