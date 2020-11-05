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

    const Number xBig3 =
        0x100000000000000010z;
    const Number xBig4 =
        0x100000000000000010z;
    const Number xResult =
        0x10000000000000002000000000000000100z;
    if( ( xBig3 * xBig4 ) != xResult )
    {
        return false;
    }

    const Number xBig5 =
        0x1000000000000000FFFFFFFFFFFFFFFFz;
    const Number xBig6 =
        0x1000000000000000FFFFFFFFFFFFFFFFz;
    const Number xResult2 =
        0x1000000000000002000000000000000dffffffffffffffe0000000000000001z;
    if( ( xBig5 * xBig6 ) != xResult2 )
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

    Number xDoubley = xBigMultiplicand;
    xDoubley.InplaceMultiplyBy2();
    if( xDoubley != xBigMultiplicand * 2ULL )
    {
        return false;
    }

    return true;
}
