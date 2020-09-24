[TOC](../TOC.md)

# 2 - Polish

* [2.1 Interface](./2_Polish.md#21-interface)
   * [2.1.1 Improving parameters](./2_Polish.md#211-improving-parameters)
   * [2.1.2 Handling numbers](./2_Polish.md#212-handling-numbers)
      * [2.1.2.1 Refactoring](./2_Polish.md#2121-refactoring)
      * [2.1.2.2 More command line handling](./2_Polish.md#2122-more-command-line-handling)
* [2.2 Functionality](./2_Polish.md#22-functionality)
   * [2.2.1 Better wheels](./2_Polish.md#221-better-wheels)
      * [2.2.1.1 Wheel up to 5](./1_Starting.md#2211-wheel-up-to-5)
* [2.3 Performance](./2_Polish.md#23-performance)

## 2.1 Interface

### 2.1.1 Improving Parameters

Improving the parameter parsing from the command line and picking out remaining parameters as potential numbers can be done by refactoring the entry point and using a class holding maps and arrays for the values and options.

```cpp
#include "Parameters.h"

bool CheckFlag(
    const char* const szFlag,
    const int iArgumentCount,
    const char* const pszArgument )
{
    return ( _stricmp( pszArgument, szFlag ) == 0 );
}

Parameters::Parameters(
    const int iParameterCount,
    const char* const* const pszParameters )
{
    mxFlags[ "help" ] = false;
    mxFlags[ "timing" ] = false;
    mxFlags[ "verbose" ] = false;
    mxFlags[ "interactive" ] = false;
    for( int i = 0; i < iParameterCount; ++i )
    {
        if( CheckFlag( "-v", iParameterCount, pszParameters[ i ] )
            || CheckFlag( "-verbose", iParameterCount, pszParameters[ i ] ) )
        {
            mxFlags[ "verbose" ] = true;
        }
        else if( CheckFlag( "-t", iParameterCount, pszParameters[ i ] )
            || CheckFlag( "-timing", iParameterCount, pszParameters[ i ] ) )
        {
            mxFlags[ "timing" ] = true;
        }
        else if( CheckFlag( "-h", iParameterCount, pszParameters[ i ] )
            || CheckFlag( "/?", iParameterCount, pszParameters[ i ] )
            || CheckFlag( "-help", iParameterCount, pszParameters[ i ] ) )
        {
            mxFlags[ "help" ] = true;
        }
        else if( CheckFlag( "-i", iParameterCount, pszParameters[ i ] )
            || CheckFlag( "-interactive", iParameterCount, pszParameters[ i ] ) )
        {
            mxFlags[ "interactive" ] = true;
        }
        else
        {
            // SE - TODO: fancier parameters, e.g. trial division limit
            mxNumbers.push_back( Number( std::string( pszParameters[ i ] ) ) );
        }
    }
}

```

The entry point then looks like this:

```cpp
#include "Parameters.h"

void Help();
void InteractiveMode( const bool bVerbose, const bool bTiming );

int main(
    const int iArgumentCount,
    const char* const* const pszArguments )
{
    const Parameters xParameters( iArgumentCount - 1, pszArguments + 1 );
    if( xParameters.Help() )
    {
        Help();
        return 0;
    }

    if( xParameters.Interactive() )
    {
        InteractiveMode( xParameters.Verbose(), xParameters.Timing() );
        return 0;
    }

    // SE - TODO: do prime number thing to spare parameters
    return 0;
}
```

## 2.1.2 Handling numbers

### 2.1.2.1 Refactoring

We create a new function to do the testing that is already being done in interactive mode so that we can use it there and for the command line parameters.

```cpp
#include "ProcessNumber.h"

#include "Parameters.h"
#include "Timing.h"
#include "../Algorithms/PowersOf2.h"
#include "../Algorithms/PowersOfN.h"
#include "../Algorithms/TrialDivision.h"
#include "../Algorithms/Wheel.h"
#include "../Number/Factorisation.h"
#include "../Number/Number.h"

#include <cstdio>

void ProcessNumber( const Number& xNumber, const Parameters& xParameters )
{
    printf( "Testing number %s...\n", xNumber.ToString().c_str() );

    if( xParameters.Timing() )
    {
        StartTiming( xParameters.Verbose() );
    }

    Factorisation xTest( xNumber );

    xTest.ContinueWithAlgorithm( PowersOf2 );
    xTest.ContinueWithAlgorithm( PowersOf< 3 > );
    xTest.ContinueWithAlgorithm( PowersOf< 5 > );
    xTest.ContinueWithAlgorithm( PowersOf< 7 > );
    xTest.ContinueWithAlgorithm( PowersOf< 11 > );
    xTest.ContinueWithAlgorithm( PowersOf< 13 > );
    xTest.ContinueWithAlgorithm( PowersOf< 17 > );
    xTest.ContinueWithAlgorithm( PowersOf< 19 > );
    xTest.ContinueWithAlgorithm( Wheel3 );

    if( xParameters.Timing() )
    {
        StopTiming();
    }

    xTest.Report();
}
```

Interactive mode then looks like this:

```cpp
#include "../Core/Parameters.h"
#include "../Core/ProcessNumber.h"
#include "../Number/Number.h"

#include <cstdio>

void InteractiveMode( const Parameters& xParameters )
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

        const Number xNumber( szBuffer );
        ProcessNumber( xNumber, xParameters );
    }

    puts( "Interactive session terminated." );
}
```

### 2.1.2.2 More command line handling

The command line numbers can now be handled also and the entry point now looks like this:

```cpp
#include "Parameters.h"
#include "ProcessNumber.h"

void Help();
void InteractiveMode( const Parameters& xParameters );

int main(
    const int iArgumentCount,
    const char* const* const pszArguments )
{
    const Parameters xParameters( iArgumentCount - 1, pszArguments + 1 );
    if( xParameters.Help() )
    {
        Help();
        return 0;
    }

    for( int i = 0; i < xParameters.NumberCount(); ++i )
    {
        ProcessNumber( xParameters.GetNumber( i ), xParameters );
    }

    if( xParameters.Interactive() )
    {
        InteractiveMode( xParameters );
        return 0;
    }
}
```

# 2.2 Functionality

## 2.2.1 Better wheels

### 2.2.1.1 Wheel up to 5

# 2.3 Performance