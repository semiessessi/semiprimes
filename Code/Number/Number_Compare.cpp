#include "Number.h"

bool Number::operator >( const Number& xOperand ) const
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

bool Number::operator ==( const Number& xOperand ) const
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