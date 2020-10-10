#include "../Number/Number.h"

bool SimpleAddCarryTest()
{
    const Number xBig1 =
        0xFFFFFFFFFFFFFFFFz;
    const Number xBig2 =
        0x10000000000000000z;
    const Number xBig3 =
        0xFFFFFFFFFFFFFFFFFFz;
    const Number xBig4 =
        0x1000000000000000000z;
    const Number xBig5 =
        0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFz;
    const Number xBig6 =
        0x1000000000000000000000000000000000000000000000000000000000000z;
    return
        ( ( xBig1 + 1 ) == xBig2 )
        && ( ( xBig3 + 1 ) == xBig4 )
        && ( ( xBig5 + 1 ) == xBig6 );
}

bool BigAddCarryTest()
{
    const Number xAddend = 0x10000000000000000z;
    const Number xAddend2 = 0x100000000000000000z;
    const Number xBig1 =
        0xFFFFFFFFFFFFFFFF0000000000000000z;
    const Number xBig2 =
        0x100000000000000000000000000000000z;
    const Number xBig3 =
        0xFFFFFFFFFFFFFFFFF00000000000000000z;
    const Number xBig4 =
        0x10000000000000000000000000000000000z;
    const Number xBig5 =
        0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000000000000000z;
    const Number xBig6 =
        0x10000000000000000000000000000000000000000000000000000000000000000000000000000z;
    return
        ( ( xBig1 + xAddend ) == xBig2 )
        && ( ( xBig3 + xAddend2 ) == xBig4 )
        && ( ( xBig5 + xAddend ) == xBig6 );
}
