#include "../Number/Number.h"

bool MulTests()
{
    const Number xBig1 =
        0xFFFFFFFFFFFFFFFFz;
    const Number xBig2 =
        0xFFFFFFFFFFFFFFFF0z;
    const uint64_t uSmall =
        0x10;
    if( ( xBig1 * uSmall ) != xBig2 )
    {
        return false;
    }

    const Number xBig10Power =
        1000000000000000000000000000000000000000000000000000z;
    const Number xBigMultiplicand =
        111111111111111111111111111111111111111111111111111z;
    const Number xBigResult =
        111111111111111111111111111111111111111111111111111000000000000000000000000000000000000000000000000000z;
    if( ( xBig10Power * xBigMultiplicand ) != xBigResult )
    {
        return false;
    }

    return true;
}
