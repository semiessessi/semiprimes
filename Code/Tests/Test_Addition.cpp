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
        ( ( xBig1 + 1ULL ) == xBig2 )
        && ( ( xBig3 + 1ULL ) == xBig4 )
        && ( ( xBig5 + 1ULL ) == xBig6 );
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
    if( (
        ( ( xBig1 + xAddend ) == xBig2 )
        && ( ( xBig3 + xAddend2 ) == xBig4 )
        && ( ( xBig5 + xAddend ) == xBig6 ) ) == false )
    {
        return false;
    }

    const Number xTestAgain = 0x100000000000000FFFFFFFFFFFFFFFFFz;
    if( ( xTestAgain + xTestAgain ) != 0x200000000000001ffffffffffffffffez )
    {
        return false;
    }

    return true;
}

bool BigSubBorrowTest()
{
    const Number xBig1 =
        0xFFFFFFFFFFFFFFFF0000000000000000z;
    const Number xBig2 =
        0x10000000000000000000000000001z;
    if( ( xBig1 - 1ULL )
        != 0xFFFFFFFFFFFFFFFEFFFFFFFFFFFFFFFFz )
    {
        return false;
    }

    if( ( xBig1 - xBig2 )
        != 0xfffefffffffffffeffffffffffffffffz )
    {
        return false;
    }

    return true;
}

bool SpecificSubTest()
{
    const Number xFirst = 0x48573ee2112346670fc810976a856e0f80807ca0a14z;
    const Number xSecond = 0x2ac3a4edbbfb8014e3ba83411e915e8000000000000z;

    if( ( xFirst - xSecond )
        != 0x1d9399f45527c6522c0d8d564bf40f8f80807ca0a14z )
    {
        return false;
    }

    Number xPlaceSub = 0xFFFFFFFFFFFFFFFFFFFFFFz;
    xPlaceSub.InplaceSubAtLimbOffset( 1, 1 );
    if( ( 0xFFFFFFFFFFFFFFFFFFFFFFz - 0x10000000000000000z )
        != xPlaceSub )
    {
        return false;
    }

    xPlaceSub = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFz;
    xPlaceSub.InplaceSubAtLimbOffset( 0x10000000000000000z, 1 );
    if( ( 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFz
        - 0x100000000000000000000000000000000z )
            != xPlaceSub )
    {
        return false;
    }

    return true;
}
