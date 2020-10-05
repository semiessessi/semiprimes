#include "Number.h"

#include "../Algorithms/Arithmetic/AdditionX64.h"
#include "../Algorithms/Arithmetic/SubtractionX64.h"

#include <intrin.h>
#include <utility>

Number::Number()
: mxLimbs( { 0 } )
, mbNegative( false )
{
}

Number::Number( const int iValue )
: mxLimbs( { static_cast< uint64_t >( ( iValue > 0 ) ? iValue : -iValue ) } )
, mbNegative( iValue < 0 )
{
}

Number::Number( const unsigned int uValue )
: mxLimbs( { uValue } )
, mbNegative( false )
{
}

Number::Number( const int64_t iValue )
: mxLimbs( { static_cast< uint64_t >( ( iValue > 0 ) ? iValue : -iValue ) } )
, mbNegative( iValue < 0 )
{
}

Number::Number( const uint64_t uValue )
: mxLimbs( { uValue } )
, mbNegative( false )
{
}

Number::Number( const std::string& xString )
: mxLimbs( { 0 } ) // initialise limb vector
, mbNegative( xString[ 0 ] == '-' ) // SE - TODO: robustness against dodgy inputs
{
    const size_t uStart = ( mbNegative || ( xString[ 0 ] == '+' ) ) ? 1 : 0;
    const size_t uLength = xString.length();
    for( size_t uPosition = uStart; uPosition < uLength; ++uPosition )
    {
        *this *= 10;
        *this += static_cast< int64_t >( xString[ uPosition ] ) - '0';
    }
}

Number::Number( const Number& xNumber )
: mxLimbs( xNumber.mxLimbs )
, mbNegative( xNumber.mbNegative )
{
}

Number::Number( Number&& xNumber ) noexcept
: mxLimbs( std::move( xNumber.mxLimbs ) )
, mbNegative( xNumber.mbNegative )
{
}

Number& Number::operator =( const Number& xNumber )
{
    mxLimbs = xNumber.mxLimbs;
    mbNegative = xNumber.mbNegative;
    return *this;
}

Number& Number::operator =( Number&& xNumber ) noexcept
{
    mxLimbs = std::move( xNumber.mxLimbs );
    mbNegative = xNumber.mbNegative;
    return *this;
}

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

Number Number::operator -() const
{
    Number xCopy( *this );
    xCopy.mbNegative = !xCopy.mbNegative;
    return xCopy;
}

uint64_t Number::operator &( const uint64_t uOperand ) const
{
    return mxLimbs[ 0 ] & uOperand;
}

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

Number& Number::operator -=( const Number& xOperand )
{
    // is xOperand largest?
    /*
    if( ( mbNegative == false )
        && ( mxLimbs.size() == 1 )
        && ( static_cast< uint64_t >( iOperand ) > mxLimbs[ 0 ] ) )
    {
        mbNegative = true;
        mxLimbs[ 0 ] = iOperand - mxLimbs[ 0 ];
        return *this;
    }
    */

    unsigned char ucBorrow = 0;
    size_t uLimb = 1;
    ucBorrow = _subborrow_u64(
        ucBorrow,
        mxLimbs[ 0 ],
        xOperand.mxLimbs[ 0 ],
        &( mxLimbs[ 0 ] ) );
    const size_t uLimbCount = mxLimbs.size();
    bool bContinueBorrow = ( ucBorrow > 0 )
        && ( uLimbCount <= uLimb );
    while( bContinueBorrow )
    {
        ucBorrow = _subborrow_u64(
            ucBorrow,
            mxLimbs[ uLimb ],
            xOperand.mxLimbs[ uLimb ],
            &( mxLimbs[ uLimb ] ) );
        ++uLimb;
        bContinueBorrow = ( ucBorrow > 0 )
            && ( uLimb < uLimbCount );
    }


    // this should not happen due to removing the case where iOperand is larger...
    //if( bContinueBorrow )
    //{
        // SE - TODO: flag some problem!
    //}

    return *this;
}

Number& Number::operator *=( const int64_t iOperand )
{
    // handle the possible factor of -1 from the signs of the operands
    mbNegative = ( iOperand < 0 ) != mbNegative;

    const uint64_t uOperand = static_cast< uint64_t >( iOperand );
    const size_t uLimbCount = mxLimbs.size();
    uint64_t uUpperPart = 0;
    uint64_t uCarry = 0;
    for( size_t uLimb = 0; uLimb < uLimbCount; ++uLimb )
    {
        mxLimbs[ uLimb ] = _umul128(
            uOperand, mxLimbs[ uLimb ], &uUpperPart )
                + uCarry;   // add the previous carry as we go along
                            // this shouldn't overflow since the biggest pair
                            // of numbers multiply to:
                            // (2^64-1)(2^64-1) = 2^128 - 2.2^64 + 1
                            // ??? maybe? should verify that more.

        uCarry = uUpperPart;
    }

    if( uCarry > 0 )
    {
        mxLimbs.push_back( uCarry );
    }

    return *this;
}

Number& Number::operator *=( const Number& xOperand )
{
    // SE - TODO: ...

    return *this;
}

Number& Number::operator /=( const int64_t iOperand )
{
    static int64_t iDeadRemainder; // :(
    *this = DivMod( *this, iOperand, iDeadRemainder );
    return *this;
}

Number& Number::operator /=( const Number& xOperand )
{
    static Number xDeadRemainder; // :(
    *this = DivMod( *this, xOperand, xDeadRemainder );
    return *this;
}

int64_t Number::operator %( const int64_t iOperand ) const
{
    return Mod( *this, iOperand );
}

void Number::InplaceLimbShiftLeft( const size_t uLimbs )
{
    // maintain zero as zero when shifted
    if( mxLimbs.size() == 1 )
    {
        if( mxLimbs[ 0 ] == 0 )
        {
            return;
        }
    }

    // add new limbs and copy
    mxLimbs.resize( mxLimbs.size() + uLimbs );
    size_t uLimb = mxLimbs.size();
    while( uLimb > uLimbs )
    {
        --uLimb;
        mxLimbs[ uLimb ] = mxLimbs[ uLimb - uLimbs ];
    }

    // fill zeroes...
    for( size_t uLimb = 0; uLimb < uLimbs; ++uLimb )
    {
        mxLimbs[ uLimb ] = 0;
    }
}

void Number::InplaceLimbShiftRight( const size_t uLimbs )
{
    // copy
    const size_t uShiftAmount = 
        ( uLimbs > mxLimbs.size() ) ? mxLimbs.size() : uLimbs;
    const size_t uLimbCount = mxLimbs.size();
    const size_t uNewLimbCount = uLimbCount - uLimbs;
    for( size_t uLimb = 0; uLimb < uNewLimbCount; ++uLimb )
    {
        mxLimbs[ uLimb ] = mxLimbs[ uLimb + uLimbs ];
    }

    // shrink
    if( uNewLimbCount > 0 )
    {
        mxLimbs.resize( uNewLimbCount );
    }
    else
    {
        mxLimbs.resize( 0 );
        mxLimbs[ 0 ] = 0;
    }
}

std::string Number::ToString() const
{
    std::string xReturnValue = "";
    if( mbNegative )
    {
        xReturnValue += "-";
    }

    Number xWorkingValue = *this;
    while( xWorkingValue > 0 )
    {
        xReturnValue = std::to_string( xWorkingValue % 10 ) + xReturnValue;
        xWorkingValue /= 10;
    }

    return xReturnValue;
}

Number Number::DivMod(
    const Number& xNumerator,
    const int64_t iDenominator,
    int64_t& iRemainder )
{
    const bool bNegativeDenominator = ( iDenominator < 0 );
    Number xReturnValue = DivMod( xNumerator,
        static_cast< uint64_t >(
            bNegativeDenominator
                ? -iDenominator
                : iDenominator ),
        reinterpret_cast< uint64_t& >( iRemainder ) );
    iRemainder = ( xNumerator.mbNegative ) ? -iRemainder : iRemainder;
    xReturnValue.mbNegative =
         bNegativeDenominator
            ? !xNumerator.mbNegative
            : xNumerator.mbNegative;
    return xReturnValue;
}

Number Number::DivMod(
    const Number& xNumerator,
    const uint64_t uDenominator,
    uint64_t& uRemainder )
{
    Number xReturnValue = 0;
    xReturnValue.mxLimbs.reserve( xNumerator.mxLimbs.size() );
    size_t uLimb = xNumerator.mxLimbs.size();
    uRemainder = 0;
    while( uLimb != 0 )
    {
        --uLimb;
        xReturnValue.InplaceLimbShiftLeft( 1 );
        xReturnValue += _udiv128(
            uRemainder,
            xNumerator.mxLimbs[ uLimb ],
            uDenominator,
            &uRemainder );
    }

    xReturnValue.mbNegative = xNumerator.mbNegative;

    return xReturnValue;
}

Number Number::DivMod(
    const Number& xNumerator,
    const Number& xDenominator,
    Number& xRemainder )
{
    // SE - TODO: division innit...
    return 0z;
}

uint64_t Number::Mod(
    const Number& xNumerator,
    const uint64_t uDenominator )
{
    uint64_t uRemainder = 0;
    for( size_t uLimb = xNumerator.mxLimbs.size();
        uLimb != 0; --uLimb )
    {
        _udiv128(
            uRemainder,
            xNumerator.mxLimbs[ uLimb - 1 ],
            uDenominator,
            &uRemainder );
    }

    return uRemainder;
}

uint64_t Number::ModMul(
    const Number& xNumerator,
    const uint64_t uMultiplicand,
    const uint64_t uDenominator )
{
    // SE - TODO: better algorithms?
    // .. avoid the copy?
    Number xProduct = xNumerator;
    xProduct *= uMultiplicand;
    return xProduct % uDenominator;
}

#pragma warning( disable : 4455 )
Number operator ""z( const char* const szToken )
{
    return Number( std::string( szToken ) );
}
#pragma warning( default : 4455 )
