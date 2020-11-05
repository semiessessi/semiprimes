#include "Number.h"

#include "../Algorithms/Arithmetic/AdditionX64.h"
#include "../Algorithms/Arithmetic/SubtractionX64.h"

#include <intrin.h>

Number& Number::operator +=( const int64_t iOperand )
{
    if( iOperand < 0 )
    {
        return operator -=( -iOperand );
    }

    // SE - TODO: handle the signed cases.

    AddX64_BaseCase( mxLimbs, static_cast< uint64_t >( iOperand ) );

    return *this;
}

Number& Number::operator +=( const uint64_t uOperand )
{
    // SE - TODO: handle the signed cases.

    AddX64_BaseCase( mxLimbs, uOperand );

    return *this;
}

Number& Number::operator +=( const Number& xOperand )
{
    if( xOperand.mbNegative != mbNegative )
    {
        // signs differ, subtract instead
        return operator -=( -xOperand );
    }

    AddX64_Generic( mxLimbs, xOperand.mxLimbs );

    return *this;
}

Number& Number::operator -=( const int64_t iOperand )
{
    // SE - TODO: handle the signed cases.

    if( iOperand < 0 )
    {
        return operator +=( -iOperand );
    }

    // is iOperand largest?
    if( ( mbNegative == false )
        && ( mxLimbs.size() == 1 )
        && ( static_cast< uint64_t >( iOperand ) > mxLimbs[ 0 ] ) )
    {
        mbNegative = true;
        mxLimbs[ 0 ] = iOperand - mxLimbs[ 0 ];
        return *this;
    }

    SubX64_BaseCase( mxLimbs, static_cast< uint64_t >( iOperand ) );

    return *this;
}

Number& Number::operator -=( const uint64_t uOperand )
{
    // SE - TODO: handle the signed cases.
    // is iOperand largest?
    if( ( mbNegative == false )
        && ( mxLimbs.size() == 1 )
        && ( uOperand > mxLimbs[ 0 ] ) )
    {
        mbNegative = true;
        mxLimbs[ 0 ] = uOperand - mxLimbs[ 0 ];
        return *this;
    }

    SubX64_BaseCase( mxLimbs, uOperand );

    return *this;
}

Number& Number::operator -=( const Number& xOperand )
{

    //if( mbNegative != xOperand.mbNegative )
    //{
        // SE - TODO: handle signs
    //}

    const bool bLargest = mbNegative
        ? ( *this <= xOperand )
        : ( *this >= xOperand );
    if( bLargest )
    {
        SubX64_SmallFromLarge( mxLimbs, xOperand.mxLimbs );
        return *this;
    }

    // SE - TODO: remove copy... ???
    Number xCopy = *this;
    *this = xOperand;
    SubX64_SmallFromLarge( mxLimbs, xCopy.mxLimbs );
    InplaceNegate();

    return *this;
}

void Number::InplaceSubAtLimbOffset( const uint64_t uOther, const uint64_t uPlace )
{
    SubX64_BaseCase_Placed( mxLimbs, uOther, uPlace );
}

void Number::InplaceSubAtLimbOffset( const Number& xOther, const uint64_t uPlace )
{
    SubX64_SmallFromLarge_Placed( mxLimbs, xOther.mxLimbs, uPlace );
}