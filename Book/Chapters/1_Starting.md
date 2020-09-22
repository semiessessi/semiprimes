[TOC](../TOC.md)

# 1 - Starting

## 1.1 First Steps

The first step is to create a 'do-nothing' program, with suitable project files to build and run it, from which we can grow the rest of the project.

### 1.1.1 The null entrypoint program

```
int main( const int iArgumentCount, const char* const* const pszArguments )
{
	return 0;
}
```

### 1.1.2 Taking parameters

To do anything useful we need to process numbers of arbitrary length as input and display them as output.

It is also helpful to allow parameters from the command line.

Something like this...

```
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

```
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

```
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

Number operator "" _z( const char* const szToken )
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
