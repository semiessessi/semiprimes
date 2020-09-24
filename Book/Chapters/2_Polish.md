[TOC](../TOC.md)

# 2 - Polish

* [2.1 Interface](./2_Polish.md#21-interface)
   * [2.1.1 Improving parameters](./2_Polish.md#211-improving-parameters)

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
            mxNumbers.push_back( Number( pszParameters[ i ] ) );
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
    const Parameters xParameters( iArgumentCount, pszArguments );
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