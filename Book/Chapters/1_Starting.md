[TOC](../TOC.md)

# 1 - Starting

* [1.1](./1_Starting.md#11-first-steps) First steps
   * [1.1.1](./1_Starting.md#111-the-null-entrypoint-program) The null entrypoint program
   * [1.1.2](./1_Starting.md#112-taking-parameters) Taking parameters
   * [1.1.3](./1_Starting.md#113-number-class) Number class
   * [1.1.4](./1_Starting.md#114-interactive-mode) Interactive mode
   * [1.1.5](./1_Starting.md#115-mistakes-are-real) Mistakes are real
   * [1.1.6](./1_Starting.md#116-testing-debugging-and-fixing) Testing, debugging and fixing
* [1.2](./1_Starting.md#12-easy-tests) Easy tests
   * [1.2.1](./1_Starting.md#121-a-little-polish) A little polish
   * [1.2.2](./1_Starting.md#122-representing-test-results) Representing test results
   * [1.2.3](./1_Starting.md#123-removing-powers-of-2) Removing powers of 2
   * [1.2.4](./1_Starting.md#124-reporting-results) Reporting results
   * [1.2.5](./1_Starting.md#125-timing) Timing
   * [1.2.6](./1_Starting.md#126-trial-division) Trial division
   * [1.2.7](./1_Starting.md#127-wheel-factorisation) Wheel factorisation
   
## 1.1 First Steps

TODO: layout goals of program in a nice way, about primality testing, factoring and other things that can be reported when entering a number

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

Stubbing out a loop for the interactive mode is the next step towards making these routines testable.

This can be its own file, InteractiveMode.cpp:

```cpp
#include <cstdio>

void InteractiveMode( const bool bVerbose, const bool bTiming )
{
    // SE - TODO: endless buffer, obvs.
    static char szBuffer[ 4096 ];
    while( true )
    {
        putchar( ':' );
        gets_s( szBuffer );
        // allow to quit
        if( szBuffer[ 0 ] == 'q' )
        {
            return;
        }
    }
}
```
### 1.1.5 Mistakes are real

If we try to test this by calling it from the appropriate place in the entry point function, we will notice the flag doesn't work because the constant in EntryPoint.cpp is wrong and the CheckFlag routine also has a '1' in place of 'i' in its loop.

Fixing these is simple, if easily overlooked:

```cpp
#include <cstdio>
#include <cstring>

void InteractiveMode( const bool bVerbose, const bool bTiming );

bool CheckFlag(
    const char* const szFlag,
    const int iArgumentCount,
    const char* const* const pszArguments )
{
    for( int i = 0; i < iArgumentCount; ++i )
    {
        if( _stricmp( pszArguments[ i ], szFlag ) == 0 )
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
    bool bVerbose = false;
    bool bTiming = false;
    if( CheckFlag( "-v", iArgumentCount, pszArguments )
        || CheckFlag( "-verbose", iArgumentCount, pszArguments ) )
    {
        bVerbose = true;
    }

    if( CheckFlag( "-t", iArgumentCount, pszArguments )
        || CheckFlag( "-timing", iArgumentCount, pszArguments ) )
    {
        bTiming = true;
    }

    if( CheckFlag( "-i", iArgumentCount, pszArguments )
        || CheckFlag( "-interactive", iArgumentCount, pszArguments ) )
    {
        InteractiveMode( bVerbose, bTiming );
        return 0;
    }

    // SE - TODO: do prime number thing to spare parameters
    return 0;
}
```

### 1.1.6 Testing, debugging and fixing

Now that the interactive mode loop works we can try to take a number as input and display it back on the screen. Long numbers will test the multi-precisioness and may reveal problems.

(in InteractiveMode.cpp)

```cpp
#include <cstdio>

#include "../Number/Number.h"

void InteractiveMode( const bool bVerbose, const bool bTiming )
{
    // SE - TODO: endless buffer, obvs.
    static char szBuffer[ 4096 ];
    while( true )
    {
        putchar( ':' );
        gets_s( szBuffer );
        // allow to quit
        if( szBuffer[ 0 ] == 'q' )
        {
            return;
        }

        Number xNumber( szBuffer );
        puts( "String test:" );
        puts( xNumber.ToString().c_str() );
    }
}
```

This shows bugs immediately (output from running program):

```
:111111111111111111111111111111111111111111111111
String test:

:1
String test:
-
:1
String test:
-
:1
String test:
-
:1
String test:
-
:1
String test:
-
:1
String test:
-
:11111111111111111
String test:
-
:1111111111111111111111111111111
String test:
-
:
```

Stepping through the code with a debugger we can find that the number of limbs has not been initialised in the case of the string constructor and repair that problem.

In Number.cpp:

```cpp
Number::Number( const std::string& xString )
: mxLimbs( { 0 } ) // initialise limb vector // <--- here
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
```

The output remains similarly incorrect. Continuing to step through the flow we find that the sign evaluation on the multiply is incorrect.

Notice that I'm debugging complexity of functionality I didn't need yet.

In Number.cpp:

```cpp
Number& Number::operator*=( const int64_t iOperand )
{
    // handle the possible factor of -1 from the signs of the operands
    mbNegative = ( iOperand < 0 ) != mbNegative; // <--- here

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
```

Then a mistake in the left shift loop while condition:

In Number.cpp:

```cpp
void Number::InplaceLimbShiftLeft( const size_t uLimbs )
{
    // START FIX
    
    // maintain zero as zero when shifted
    if( mxLimbs.size() == 1 )
    {
        if( mxLimbs[ 0 ] == 0 )
        {
            return;
        }
    }

    // END FIX
    
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
```

Once this is fixed it becomes obvious that the 'greater than' operator has a bug in detecting the end of a loop with a unsigned integer being compared to zero.

```cpp
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
    size_t uLimb = mxLimbs.size();      // <--- here
    bool bResult = false;
    bool bEqual = true;
    while( bEqual && ( uLimb != 0 ) )   // <--- here
    {
        --uLimb;                        // <--- here
        bResult = mxLimbs[ uLimb ] > xOperand.mxLimbs[ uLimb ];
        bEqual = mxLimbs[ uLimb ] == xOperand.mxLimbs[ uLimb ];
    }

    return mbNegative ? ( bEqual || !bResult ) : bResult;
}
```

The program now appears to function correctly when inputting and displaying integers that are less than 64-bits, implying that some of the operations only have bugs when the number is sufficiently large.

Example output:

```
:11111
String test:
11111
:111111111111111111111
String test:

:1111111111
String test:
1111111111
:11111111111111
String test:
11111111111111
:1111111111111111
String test:
1111111111111111
:1111111111111111111
String test:
1111111111111111111
:111111111111111111111
String test:

:1111111111111111111111111111111111111111111111
String test:

:
```

On inspection, again the comparison operation has a flaw, this time it returns inverted results when checking size by the number of limbs filled with values.

```cpp
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
```

Testing again with better test cases reveals additional problems, but that the algorithms are largely working correctly but the string has the order of digits in reverse, and this is likely the last fix required except for edge cases:

```
:11111111111111111111111111111111
String test:
11111111111111111111111111111111
:1111111111111111111
String test:
1111111111111111111
:1111111111111111111111111111111111111111111111111111111111111111111111111111111111
String test:
1111111111111111111111111111111111111111111111111111111111111111111111111111111111
:11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
String test:
11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
:4984894894564871984894515621
String test:
1265154984891784654984984894
:5151961561651651616541
String test:
1456161561561651691515
:16516516165416516919191919198194198498498494984984911651616197198191651651961651941949465162161061
String test:
16016126156494914915616915615619189179161615611948948949489489489149189191919191961561456161561561
:
```

The fix is straightforwards:

```cpp
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
        xReturnValue = std::to_string( xWorkingValue % 10 ) + xReturnValue; // <--- here
        xWorkingValue /= 10;
    }

    return xReturnValue;
}
```

Finally the output seems reasonable.

```
:1234567890123456789012345678901234567890
String test:
1234567890123456789012345678901234567890
:
```

## 1.2 Easy tests

### 1.2.1 A little polish

The interactive mode can be quickly improved to be more usable.

```cpp

#include <cstdio>

#include "../Number/Number.h"

void InteractiveMode( const bool bVerbose, const bool bTiming )
{
    puts( "Semiprimes Interactive Mode - Enter a number, or q to quit." );

    // SE - TODO: endless buffer, obvs.
    static char szBuffer[ 4096 ];
    while( true )
    {
        putchar( ':' );
        gets_s( szBuffer );
        // allow to quit
        if( ( szBuffer[ 0 ] == 'q' )
            || ( szBuffer[ 0 ] == 'Q' ) )
        {
            return;
        }

        Number xNumber( szBuffer );
        printf( "Testing number %s...\n", xNumber.ToString().c_str() );
        puts( "TODO: some testing!" );
    }
}
```

Providing help flags is also a good idea.

In a new file Help.cpp:

```cpp
#include <cstdio>

void Help()
{
    puts( "Semiprimes - A prime testing and integer factorisation tool" );
    puts( "WARNING: WORK IN PROGRESS" );
    puts( "Usage: " );
    puts( " sp <options> [numbers]" );
    puts( "Options:" );
    puts( " -h -help                show this message" );
    puts( " -i -interactive         provides a prompt for the user to enter numbers" );
    puts( " -t -timing              display timings" );
    puts( " -v -verbose             report many messages about progress" );
}

```

This is easily added to the entry point function:

```cpp
int main(
    const int iArgumentCount,
    const char* const* const pszArguments )
{
    bool bVerbose = false;
    bool bTiming = false;
    if( CheckFlag( "-v", iArgumentCount, pszArguments )
        || CheckFlag( "-verbose", iArgumentCount, pszArguments ) )
    {
        bVerbose = true;
    }

    if( CheckFlag( "-t", iArgumentCount, pszArguments )
        || CheckFlag( "-timing", iArgumentCount, pszArguments ) )
    {
        bTiming = true;
    }

    if( CheckFlag( "-h", iArgumentCount, pszArguments )
        || CheckFlag( "/?", iArgumentCount, pszArguments )
        || CheckFlag( "-help", iArgumentCount, pszArguments ) )
    {
        Help();
        return 0;
    }

    if( CheckFlag( "-i", iArgumentCount, pszArguments )
        || CheckFlag( "-interactive", iArgumentCount, pszArguments ) )
    {
        InteractiveMode( bVerbose, bTiming );
        return 0;
    }

    // SE - TODO: do prime number thing to spare parameters
    return 0;
}
```

## 1.2.2 Representing test results

We need some way to pass the results of various tests on and to display them to the user when the tests are complete, or as complete as currently possible.

A new header/implementation pair defining a struct representing a factorisation.

Header:

```cpp
#ifndef FACTORISATION_H
#define FACTORISATION_H

#include "Number.h"

#include <vector>

struct Factorisation
{
    std::vector<Factorisation> mxKnownFactors;
    Number mxNumber;
    bool mbKnownPrime;
    bool mbKnownComposite;
    
    Factorisation( const Number& xNumber = 0z );
};

#endif
```

Implementation:

```cpp
#include "Factorisation.h"

Factorisation::Factorisation( const Number& xNumber )
: mxKnownFactors()
, mxNumber( xNumber )
, mbKnownPrime( false )
, mbKnownComposite( false )
{
}
```

## 1.2.3 Removing powers of 2

TODO: explain motivation etc.

```cpp
uint64_t Number::operator &( const uint64_t uOperand ) const
{
    return mxLimbs[ 0 ] & uOperand;
}
```

```cpp
uint64_t LeastSignificantLimb() const { return mxLimbs[ 0 ]; }
```

The implementation...

```cpp
#include "PowersOf2.h"

#include "../Number/Factorisation.h"
#include "../Number/Number.h"

Factorisation PowersOf2( const Number& xNumber )
{
    int iPowers = 0;
    Number xWorkingValue = xNumber;
    // go fast if whole limbs are zeroed out
    while( xWorkingValue.LeastSignificantLimb() == 0 )
    {
        iPowers += 64;
        xWorkingValue.InplaceLimbShiftLeft( 1 );
    }

    // test remaining bits
    while( ( xWorkingValue.LeastSignificantLimb() != 0 )
        && ( ( xWorkingValue & 0x1 ) == 0 ) )
    {
        xWorkingValue /= 2;
        ++iPowers;
    }

    Factorisation xResult( xNumber );
    xResult.mbKnownComposite = iPowers != 0;
    if( xResult.mbKnownComposite )
    {
        Factorisation xTwoFactorisation( 2z );
        xTwoFactorisation.mbKnownPrime = true;
        xTwoFactorisation.miPower = iPowers;
        xResult.mxKnownFactors.push_back( xTwoFactorisation );
        // SE - TODO: equality test.
        if( xWorkingValue > 1 )
        {
            xResult.mxKnownFactors.push_back( Factorisation( xWorkingValue ) );
        }
    }

    return xResult;
}
```

## 1.2.4 Reporting results

Outputting using the struct is straightforwards:

```cpp
void Factorisation::Report() const
{
    const std::string xNumberString = mxNumber.ToString();
    if( mbKnownPrime )
    {
        printf( "%s is prime!\n", xNumberString.c_str() );
    }

    bool bComplete = true;
    if( mbKnownComposite )
    {
        printf( "%s is a composite\n", xNumberString.c_str() );
        puts( "Factorisation: " );
        printf( " " );
        for( size_t uFactor = 0; uFactor < mxKnownFactors.size(); ++uFactor )
        {
            if( mxKnownFactors[ uFactor ].miPower == 1 )
            {
                printf( "%s", mxKnownFactors[ uFactor ].mxNumber.ToString().c_str() );
            }
            else
            {
                printf( "%s^%d",
                    mxKnownFactors[ uFactor ].mxNumber.ToString().c_str(),
                    mxKnownFactors[ uFactor ].miPower );
            }

            if( mxKnownFactors[ uFactor ].mbKnownComposite )
            {
                printf( "(C)" );
            }

            if( !mxKnownFactors[ uFactor ].mbKnownComposite && !mxKnownFactors[ uFactor ].mbKnownPrime )
            {
                printf( "(?)" );
                bComplete = false;
            }

            if( uFactor != ( mxKnownFactors.size() - 1 ) )
            {
                printf( " * " );
            }
        }

        puts( "" );

        if( bComplete == false )
        {
            puts( "NOTE: TESTS WERE NOT COMPLETED" );
        }
    }

    if( !mbKnownPrime && !mbKnownComposite )
    {
        printf( "Could not determine if %s was prime or not!\n", xNumberString.c_str() );
    }
}
```

### 1.2.5 Timing

### 1.2.6 Trial division

### 1.2.7 Wheel factorisation
