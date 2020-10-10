#include "../Number/Number.h"

bool SimpleAddCarryTest()
{
    const Number xBig1 =
        0xFFFFFFFFFFFFFFFFz;
    const Number xBig2 =
        0x10000000000000000z;
    return ( xBig1 + 1 ) == xBig2;
}
