[TOC](../TOC.md)

# 1 - Starting

## 1.1 First Steps

The first step is to create a 'do-nothing' program, with suitable project files to build and run it, from which we can grow the rest of the project.

### 1.1.1 The null entrypoint program

```cpp 
int main( const int iArgumentCount, const char* const* const pszArguments )
{
    return 0;
}
```

### 1.1.2 Taking parameters

To do anything useful we need to process numbers of arbitrary length as input and display them as output.

It is also helpful to allow parameters from the command line.

Something like this...

```cpp 
#include <cstdio>
#include <cstring>

bool CheckFlag(
    const char* const szFlag,
    const int iArgumentCount,
    const char* const* const pszArguments )
{
    for( int i = 0; i < iArgumentCount; ++i )
    {
        if( _stricmp( pszArguments[ 1 ], szFlag ) == 0 )
        {
            return true;
        }
    }

    return false;
}

int main(
    const int iArgumentCount,
    const char* const* const pszArguments )
{
    if( CheckFlag( "-v", iArgumentCount, pszArguments )
        || CheckFlag( "-verbose", iArgumentCount, pszArguments ) )
    {
        // SE - TODO: set verbosity enabled
    }

    if( CheckFlag( "-t", iArgumentCount, pszArguments )
        || CheckFlag( "-timing", iArgumentCount, pszArguments ) )
    {
        // SE - TODO: set timing enabled
    }

    if( CheckFlag( "-1", iArgumentCount, pszArguments )
        || CheckFlag( "-interactive", iArgumentCount, pszArguments ) )
    {
        // SE - TODO: run interactive mode
    }

    // SE - TODO: do prime number thing to spare parameters
    return 0;
}
```

### 1.1.3 Number class

Writing the shape of the string to number and number to string conversion gives a first task to inform the functionality required in the class.


Header:

```cpp 
#ifndef NUMBER_H
#define NUMBER_H

#include <cstdint>
#include <string>
#include <vector>

class Number
{

public:

    Number();
    Number( const std::string& xString );
    Number( const Number& xNumber );
    Number( Number&& xNumber ) noexcept;

    Number& operator=( const Number& xNumber );
    Number& operator=( Number&& xNumber ) noexcept;

    std::string ToString() const;

private:

    std::vector<int64_t> mxLimbs;
    bool mbNegative;
};

#pragma warning( disable : 4455 )
Number operator ""z( const char* const szToken );
#pragma warning( default : 4455 )

#endif

```

Implementation:

```cpp 
#include "Number.h"

#include <complex>
#include <utility>

Number::Number()
: mxLimbs( { 0 } )
, mbNegative( false )
{
}

Number::Number( const std::string& xString )
: mbNegative( xString[ 0 ] == '-' ) // SE - TODO: robustness against dodgy inputs
{
    const size_t uStart = ( mbNegative || ( xString[ 0 ] == '+' ) ) ? 1 : 0;
    const size_t uLength = xString.length();
    for( size_t uPosition = uStart; uPosition < uLength; ++uPosition )
    {
        // SE - TODO: operator implementations.
        //*this *= 10;
        //*this += xString[ uPosition ] - '0';
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

Number operator ""z( const char* const szToken )
{
    return Number( std::string( szToken ) );
}

std::string Number::ToString() const
{
    // SE - TODO: number to string
    std::string xReturnValue = "";
    if( mbNegative )
    {
        xReturnValue += "-";
    }

    Number xWorkingValue = *this;
    // SE - TODO: operator implementations.
    //while( xWorkingValue > 0 )
    {
        //xReturnValue += '0' + static_cast< char >( xWorkingValue % 10 );
        //xWorkingValue /= 10;
    }

    return xReturnValue;
}

```

Filling out the required operators, and leaving a few stubs and unimplemented details for later should be enough to allow testing the string conversion.

```cpp
#include "Number.h"

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
: mbNegative( xString[ 0 ] == '-' ) // SE - TODO: robustness against dodgy inputs
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
        return mbNegative;
    }

    if( mxLimbs.size() < xOperand.mxLimbs.size() )
    {
        return !mbNegative;
    }

    // actual comparison
    size_t uLimb = mxLimbs.size() - 1;
    bool bResult = false;
    bool bEqual = true;
    while( bEqual && ( uLimb >= 0 ) )
    {
        bResult = mxLimbs[ uLimb ] > xOperand.mxLimbs[ uLimb ];
        bEqual = mxLimbs[ uLimb ] == xOperand.mxLimbs[ uLimb ];
        --uLimb;
    }

    return mbNegative ? ( bEqual || !bResult ) : bResult;
}

Number& Number::operator+=( const int64_t iOperand )
{
    // SE - TODO: handle the signed cases.

    unsigned char ucCarry = 0;
    size_t uLimb = 0;
    bool bContinueCarry = true;
    const size_t uLimbCount = mxLimbs.size();
    do
    {
        if( uLimbCount <= uLimb )
        {
            mxLimbs.push_back( 1 );
            break;
        }

        ucCarry = _addcarryx_u64(
            ucCarry,
            mxLimbs[ uLimb ],
            iOperand,
            &( mxLimbs[ uLimb ] ) );
        ++uLimb;
        bContinueCarry = ( ucCarry > 0 )
            && ( uLimbCount <= uLimb );
    }
    while( bContinueCarry );

    if( bContinueCarry )
    {
        mxLimbs.push_back( 1 );
    }

    return *this;
}

Number& Number::operator+=( const Number& xOperand )
{
    // SE - TODO: handle the signed cases.

    const size_t uOperandSize = xOperand.mxLimbs.size();
    if( uOperandSize > mxLimbs.size() )
    {
        mxLimbs.resize( uOperandSize );
    }
    const size_t uLimbCount = mxLimbs.size();
    unsigned char ucCarry = 0;
    for( size_t uLimb = 0; uLimb < uLimbCount; ++uLimb )
    {
        ucCarry = _addcarryx_u64(
            ucCarry,
            mxLimbs[ uLimb ],
            xOperand.mxLimbs[ uLimb ],
            &( mxLimbs[ uLimb ] ) );
    }
    
    if( ucCarry != 0 )
    {
        mxLimbs.push_back( 1 );
    
    }
    return *this;
}

Number& Number::operator*=( const int64_t iOperand )
{
    // handle the possible factor of -1 from the signs of the operands
    mbNegative = ( iOperand < 0 ) == mbNegative;

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

Number& Number::operator/=( const int64_t iOperand )
{
    static int64_t iDeadRemainder; // :(
    *this = DivMod( *this, iOperand, iDeadRemainder );
    return *this;
}

Number& Number::operator/=( const Number& xOperand )
{
    static Number xDeadRemainder; // :(
    *this = DivMod( *this, xOperand, xDeadRemainder );
    return *this;
}

int64_t Number::operator %( const int64_t iOperand ) const
{
    int64_t iRemainder = 0;
    DivMod( *this, iOperand, iRemainder );
    return iRemainder;
}

void Number::InplaceLimbShiftLeft( const size_t uLimbs )
{
    // add new limbs and copy
    mxLimbs.resize( mxLimbs.size() + uLimbs );
    size_t uLimb = mxLimbs.size();
    while( uLimb != 0 )
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
    size_t uLimbCount = mxLimbs.size();
    for( size_t uLimb = 0; uLimb < uLimbCount; ++uLimb )
    {
        mxLimbs[ uLimb ] = mxLimbs[ uLimb + uLimbs ];
    }

    // shrink
    mxLimbs.resize( mxLimbs.size() - uLimbs );
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
        xReturnValue += '0' + static_cast< char >( xWorkingValue % 10 );
        xWorkingValue /= 10;
    }

    return xReturnValue;
}

Number Number::DivMod(
    const Number xNumerator,
    const int64_t iDenominator,
    int64_t& iRemainder )
{
    Number xReturnValue = DivMod( xNumerator,
        static_cast< uint64_t >( ( iDenominator < 0 ) ? -iDenominator : iDenominator ),
        reinterpret_cast< uint64_t& >( iRemainder ) );
    iRemainder = ( xNumerator.mbNegative ) ? -iRemainder : iRemainder;
    return xReturnValue;
}

Number Number::DivMod(
    const Number xNumerator,
    const uint64_t uDenominator,
    uint64_t& uRemainder )
{
    Number xReturnValue = 0;
    size_t uLimb = xNumerator.mxLimbs.size();
    uRemainder = 0;
    while( uLimb != 0 )
    {
        --uLimb;
        xReturnValue.InplaceLimbShiftLeft( 1 );
        // _udiv128(unsigned __int64 /* highdividend */, unsigned __int64 /* lowdividend */, unsigned __int64 /* divisor */, unsigned __int64* /* remainder */);
        xReturnValue += _udiv128( uRemainder, xNumerator.mxLimbs[ uLimb ], uDenominator, &uRemainder );
    }

    return xReturnValue;
}

Number Number::DivMod(
    const Number xNumerator,
    const Number xDenominator,
    Number& xRemainder )
{
    // SE - TODO: division innit...
    return 0z;
}

#pragma warning( disable : 4455 )
Number operator ""z( const char* const szToken )
{
    return Number( std::string( szToken ) );
}
#pragma warning( default : 4455 )

```

### 1.1.4 Interactive mode



### 1.1.5 Testing, debugging and fixing

