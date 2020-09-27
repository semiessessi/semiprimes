[TOC](../TOC.md)

# 2 - Polish

* [2.1 Interface](./2_Polish.md#21-interface)
   * [2.1.1 Improving parameters](./2_Polish.md#211-improving-parameters)
   * [2.1.2 Handling numbers](./2_Polish.md#212-handling-numbers)
      * [2.1.2.1 Refactoring](./2_Polish.md#2121-refactoring)
      * [2.1.2.2 More command line handling](./2_Polish.md#2122-more-command-line-handling)
* [2.2 Functionality](./2_Polish.md#22-functionality)
   * [2.2.1 Better wheels](./2_Polish.md#221-better-wheels)
      * [2.2.1.1 Wheel up to 5](./2_Polish.md#2211-wheel-up-to-5)
      * [2.2.1.2 Wheel up to n](./2_Polish.md#2212-wheel-up-to-n)
* [2.3 Performance](./2_Polish.md#23-performance)
   * [2.3.1 Profiling](./2_Polish.md#231-profiling)
      * [2.3.1.1 Reducing allocations](./2_Polish.md#2311-reducing-allocations)
      * [2.3.1.2 Mod with no resizing](./2_Polish.md#2312-mod-with-no-resizing)
      * [2.3.1.3 Bug fixing](./2_Polish.md#2313-bug-fixing)
      * [2.3.1.4 Reducing copies](./2_Polish.md#2314-reducing-copies)

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

```cpp
Factorisation Wheel5( const Number& xNumber )
{
    const unsigned int auDiffs[] = { 6, 4, 2, 4, 2, 4, 6, 2 };
    Number xWorkingValue = xNumber;
    Factorisation xResult( xNumber );
    uint64_t uTest = 31;
    int iDiff = 0;
    while( xWorkingValue > ( ( uTest * uTest ) - 1 ) )
    {
        if( ( xWorkingValue % uTest ) == 0 )
        {
            xResult.mbKnownComposite = true;
            Factorisation xNew( uTest, true );
            xNew.miPower = 0;
            while( ( xWorkingValue % uTest ) == 0 )
            {
                ++xNew.miPower;
                xWorkingValue /= uTest;
            }
            xResult.mxKnownFactors.push_back( xNew );
        }

        uTest += auDiffs[ iDiff ];
        iDiff = ( iDiff + 1 ) & 7;

        if( uTest > uWheel5Cutoff )
        {
            xResult.mxKnownFactors.push_back( Factorisation( xWorkingValue ) );
            return xResult;
        }
    }

    if( xResult.mxKnownFactors.empty() )
    {
        xResult.mbKnownPrime = true;
    }
    else if( xWorkingValue > 1 )
    {
        xResult.mxKnownFactors.push_back( Factorisation( xWorkingValue, true ) );
    }

    return xResult;
}
```

### 2.2.1.2 Wheel up to n

Implementing a wheel up to n is a little tricky without repeated code, but enables a small increase in efficiency by allowing larger wheels without entering enormous constants.

```cpp
#ifndef WHEEL_INL
#define WHEEL_INL

#include "../Number/Factorisation.h"
#include "../Number/Number.h"

#include "TrialDivision.h"

// SE - TODO: test these values
static constexpr int aiWheelPrimes[] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43,
    47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103,
    107, 109, 113, 127, 131, 137, 139, 149,151, 157, 163,
    167, 176, 179, 181, 191, 193, 197, 199, 211, 223, 227,
    229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
    283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353,
    359, 367, 373, 379, 383, 389, 397, 401, 409,
    419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541,
    547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659,
    661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809,
    811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
    947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069,
    1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153, 1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223,
    1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289, 1291, 1297, 1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373,
    1381, 1399, 1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451, 1453, 1459, 1471, 1481, 1483, 1487, 1489, 1493, 1499, 1511,
    1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583, 1597, 1601, 1607, 1609, 1613, 1619, 1621, 1627, 1637, 1657,
    1663, 1667, 1669, 1693, 1697, 1699, 1709, 1721, 1723, 1733, 1741, 1747, 1753, 1759, 1777, 1783, 1787, 1789, 1801, 1811,
    1823, 1831, 1847, 1861, 1867, 1871, 1873, 1877, 1879, 1889, 1901, 1907, 1913, 1931, 1933, 1949, 1951, 1973, 1979, 1987,
    1993, 1997, 1999, 2003, 2011, 2017, 2027, 2029, 2039, 2053, 2063, 2069, 2081, 2083, 2087, 2089, 2099, 2111, 2113, 2129,
    2131, 2137, 2141, 2143, 2153, 2161, 2179, 2203, 2207, 2213, 2221, 2237, 2239, 2243, 2251, 2267, 2269, 2273, 2281, 2287,
    2293, 2297, 2309, 2311, 2333, 2339, 2341, 2347, 2351, 2357, 2371, 2377, 2381, 2383, 2389, 2393, 2399, 2411, 2417, 2423,
    2437, 2441, 2447, 2459, 2467, 2473, 2477, 2503, 2521, 2531, 2539, 2543, 2549, 2551, 2557, 2579, 2591, 2593, 2609, 2617,
};

static constexpr int iWheelPrimeCount =
    sizeof( aiWheelPrimes ) / sizeof( aiWheelPrimes[ 0 ] );

template< int N >
class Wheel
{

public:

    Factorisation operator ()( const Number& xNumber ) const;

private:

    static void GenerateWheel();

    template< int X >
    struct Hack
    {
        static constexpr int i = iWheelPrimeCount - X;
        static constexpr int PreviousPrime =
            ( aiWheelPrimes[ i ] >= N )
                ? aiWheelPrimes[ i - 1 ]
                : Hack< X - 1 >::PreviousPrime;
    };

    template<>
    struct Hack< 0 >
    {
        static constexpr int PreviousPrime = 1;
    };


public:
    static constexpr int PreviousPrime = Hack< iWheelPrimeCount - 1 >::PreviousPrime;
    static const int SieveLength = ( 2 * Wheel< PreviousPrime >::SieveLength * N ) / 2;

private:

    static int saiDifferences[ SieveLength ];
    static int saiSieve[ SieveLength ];
    static int siWheelLength;

};

template< int N >
int Wheel< N >::saiDifferences[ Wheel< N >::SieveLength ] = { 0 };
template< int N >
int Wheel< N >::saiSieve[ Wheel< N >::SieveLength ] = { 0 };
template< int N >
int Wheel< N >::siWheelLength = 1;

template<>
class Wheel< 2 >
{
public:

    static constexpr int SieveLength = 1;

    Factorisation operator ()( const Number& xNumber ) const { return TrialDivision( xNumber ); }
};

template< int N >
Factorisation WheelUpTo( const Number& xNumber )
{
    return Wheel< N >()( xNumber );
}

template< int N >
Factorisation Wheel< N >::operator()( const Number& xNumber ) const
{
    GenerateWheel();

    static const uint64_t uWheelLimit = 200000;

    Number xWorkingValue = xNumber;
    Factorisation xResult( xNumber );
    uint64_t uTest = SieveLength * 2 + 1;;
    int iDiff = 0;
    while( xWorkingValue > ( ( uTest * uTest ) - 1 ) )
    {
        if( ( xWorkingValue % uTest ) == 0 )
        {
            xResult.mbKnownComposite = true;
            Factorisation xNew( uTest, true );
            xNew.miPower = 0;
            while( ( xWorkingValue % uTest ) == 0 )
            {
                ++xNew.miPower;
                xWorkingValue /= uTest;
            }
            xResult.mxKnownFactors.push_back( xNew );
        }

        uTest += saiDifferences[ iDiff ];
        ++iDiff;
        if( iDiff >= siWheelLength )
        {
            iDiff = 0;
        }

        if( uTest > uWheelLimit )
        {
            xResult.mxKnownFactors.push_back( Factorisation( xWorkingValue ) );
            return xResult;
        }
    }

    if( xResult.mxKnownFactors.empty() )
    {
        xResult.mbKnownPrime = true;
    }
    else if( xWorkingValue > 1 )
    {
        xResult.mxKnownFactors.push_back( Factorisation( xWorkingValue, true ) );
    }

    return xResult;
}

template< int N >
void Wheel< N >::GenerateWheel()
{
    if( siWheelLength > 1 )
    {
        return;
    }

    int iStart = SieveLength * 2 + 1;
    int iEnd = iStart + SieveLength;
    for( int i = 0; i < SieveLength; ++i )
    {
        saiSieve[ i ] = iStart + 2 * i;
    }

    const int iTotalPrimeCount = sizeof( aiWheelPrimes ) / sizeof( aiWheelPrimes[ 0 ] );
    int iWheelPrimeCount = 0;
    for( iWheelPrimeCount = 0; iWheelPrimeCount < iTotalPrimeCount; ++iWheelPrimeCount )
    {
        if( aiWheelPrimes[ iWheelPrimeCount ] > N )
        {
            break;
        }
    }

    for( int i = 1; i < iWheelPrimeCount; ++i )
    {
        const int iCurrentPrime = aiWheelPrimes[ i ];
        const int iStart = ( iCurrentPrime - 1 ) / 2;
        for( int j = iStart; j < SieveLength; j += iCurrentPrime )
        {
            saiSieve[ j ] = 0;
        }
    }

    int iDiff = 0;
    siWheelLength = 0;
    for( int i = 1; i < SieveLength; ++i )
    {
        if( saiSieve[ i ] == 0 )
        {
            saiDifferences[ iDiff ] += 2;
        }
        else
        {
            saiDifferences[ iDiff ] += 2;
            ++iDiff;
            ++siWheelLength;
        }
    }

    saiDifferences[ iDiff ] += 2;
    ++siWheelLength;
}

#endif
```

ProcessNumber can then be modified to call this and reduce the number of repeated calls to templated functions to remove powers of primes.

```cpp
namespace
{

template< int X, int N >
struct Helper
{
    static constexpr int i = iWheelPrimeCount - X;
    static constexpr int PreviousPrime =
        ( aiWheelPrimes[ i ] >= N )
            ? aiWheelPrimes[ i - 1 ]
            : Helper< X - 1, N >::PreviousPrime;

    static void ContinueFactorisation( Factorisation& xTest )
    {
        Helper< iWheelPrimeCount - 1, PreviousPrime >::ContinueFactorisation( xTest );
        //if( N <= 1 )
        //{
            // error
        //}
        xTest.ContinueWithAlgorithm( PowersOf< N > );
    }
};

template< int N >
struct Helper< 0, N >
{
    static constexpr int PreviousPrime = 1;

    static void ContinueFactorisation( Factorisation& xFactorisation )
    {

    }
};

template< int X >
struct Helper< X, 2 >
{
    static constexpr int PreviousPrime = 1;

    static void ContinueFactorisation( Factorisation& xFactorisation )
    {

    }
};

}

void ProcessNumber( const Number& xNumber, const Parameters& xParameters )
{
    printf( "Testing number %s...\n", xNumber.ToString().c_str() );

    if( xParameters.Timing() )
    {
        StartTiming( xParameters.Verbose() );
    }

    Factorisation xTest( xNumber );

    xTest.ContinueWithAlgorithm( PowersOf2 );

    Helper< iWheelPrimeCount - 1, ( 2 * 3 * 5 * 7 * 11 ) >::ContinueFactorisation( xTest );
    xTest.ContinueWithAlgorithm( WheelUpTo< 11 > );

    if( xParameters.Timing() )
    {
        StopTiming();
    }

    xTest.Report();
}
```

# 2.3 Performance

## 2.3.1 Profiling

### 2.3.1.1 Reducing allocations

```cpp
Number Number::DivMod(
    const Number xNumerator,
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

    return xReturnValue;
}
```

### 2.3.1.2 Mod with no resizing

```cpp
uint64_t Number::Mod(
    const Number xNumerator,
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
```

### 2.3.1.3 Bug fixing

Entering zero, or an empty string causes a crash which can be fixed by checking for that case, as well as some extra protective code in the limb shift right.

```cpp
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
    
    // START FIX

    // shrink
    if( uNewLimbCount > 0 )
    {
        mxLimbs.resize( uNewLimbCount );
    }
    else
    {
        mxLimbs[ 0 ] = 0;
    }

    // END FIX
}
```


```cpp
void ProcessNumber( const Number& xNumber, const Parameters& xParameters )
{
    // START FIX
    if( ( xNumber.GetLimbCount() == 1 )
        && ( xNumber.LeastSignificantLimb() == 0 ) )
    {
        puts( "Cannot test zero.\n" );
        return;
    }
    // END FIX
    
    printf( "Testing number %s...\n", xNumber.ToString().c_str() );

    if( xParameters.Timing() )
    {
        StartTiming( xParameters.Verbose() );
    }

    Factorisation xTest( xNumber );

    xTest.ContinueWithAlgorithm( PowersOf2 );

    Helper< iWheelPrimeCount - 1, ( 2 * 3 * 5 * 7 * 11 ) >::ContinueFactorisation( xTest );
    xTest.ContinueWithAlgorithm( WheelUpTo< 11 > );

    if( xParameters.Timing() )
    {
        StopTiming();
    }

    xTest.Report();
}
```

### 2.3.1.4 Reducing copies

Changing the function signature of the div/mod functions reduces the number of copies performed:

Note the & operator used here...

```cpp
static Number DivMod(
    const Number& xNumerator,
    const int64_t iDenominator,
    int64_t& iRemainder );
static Number DivMod(
    const Number& xNumerator,
    const uint64_t uDenominator,
    uint64_t& uRemainder );
static Number DivMod(
    const Number& xNumerator,
    const Number& xDenominator,
    Number& xRemainder );

static uint64_t Mod(
    const Number& xNumerator,
    const uint64_t uDenominator );
```