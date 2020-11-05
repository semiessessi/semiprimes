#include "Number.h"

bool Number::operator >( const Number& xOperand ) const noexcept
{
    // sign checks
    if( xOperand.mbNegative != mbNegative )
    {
        return xOperand.mbNegative;
    }

    // size checks
    if( mxLimbs.size() > xOperand.mxLimbs.size() )
    {
        return !mbNegative;
    }

    if( mxLimbs.size() < xOperand.mxLimbs.size() )
    {
        return mbNegative;
    }

    // actual comparison
    size_t uLimb = mxLimbs.size();
    bool bResult = false;
    bool bEqual = true;
    while( bEqual && ( uLimb != 0 ) )
    {
        --uLimb;
        bResult = mxLimbs[ uLimb ] > xOperand.mxLimbs[ uLimb ];
        bEqual = mxLimbs[ uLimb ] == xOperand.mxLimbs[ uLimb ];
    }

    return mbNegative ? ( bEqual || !bResult ) : bResult;
}

bool Number::operator ==( const Number& xOperand ) const noexcept
{
    if( mbNegative != xOperand.mbNegative )
    {
        return false;
    }

    if( mxLimbs.size() != xOperand.mxLimbs.size() )
    {
        return false;
    }

    for( size_t i = 0; i < mxLimbs.size(); ++i )
    {
        if( mxLimbs[ i ] != xOperand.mxLimbs[ i ] )
        {
            return false;
        }
    }

    return true;
}

bool Number::GreaterOrEqualToWithOffset( const Number& xOperand, const uint64_t uPlace ) const noexcept
{
    // no sign checks ...

    // this might happen.
    size_t uMySize = mxLimbs.size();
    if( mxLimbs.back() == 0 )
    {
        --uMySize;
    }

    size_t uOtherSize = xOperand.mxLimbs.size();
    if( xOperand.mxLimbs.back() == 0 )
    {
        --uOtherSize;
    }

    // size checks
    if( uMySize + uPlace > uOtherSize )
    {
        return true;
    }

    if( uMySize + uPlace < uOtherSize )
    {
        return false;
    }

    // actual comparison
    size_t uLimb = uMySize;
    while( uLimb != 0 )
    {
        --uLimb;
        if( mxLimbs[ uLimb ] < xOperand.mxLimbs[ uLimb + uPlace ] )
        {
            return false;
        }

        if( mxLimbs[ uLimb ] > xOperand.mxLimbs[ uLimb + uPlace ] )
        {
            return true;
        }
    }

    // equal if all remaining digits are zero
    for( size_t i = 0; i < uPlace; ++i )
    {
        if( xOperand.mxLimbs[ i ] != 0 )
        {
            return false;
        }
    }

    return true;
}