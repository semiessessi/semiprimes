#include "../Number/Number.h"

static const Number kxTest = 0xFFFFAAAABBBBCCCCDDDDEEEE1111222233334444z;

bool LeftShiftTests()
{
    if( ( kxTest << 4 )
        != 0xFFFFAAAABBBBCCCCDDDDEEEE11112222333344440z )
    {
        return false;
    }

    return true;
}

bool RightShiftTests()
{
    if( ( kxTest >> 4 )
        != 0xFFFFAAAABBBBCCCCDDDDEEEE111122223333444z )
    {
        return false;
    }

    return true;
}
