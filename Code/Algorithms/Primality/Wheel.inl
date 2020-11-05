#ifndef WHEEL_INL
#define WHEEL_INL

#include "../../Number/Factorisation.h"
#include "../../Number/Number.h"

#include "TrialDivision.h"

#include <utility>

// SE - TODO: test these values
static constexpr int aiWheelPrimes[] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43,
    47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103,
    107, 109, 113, 127, 131, 137, 139, 149,151, 157, 163,
    167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227,
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
    void SetWheelBound( const Number& iBound );

    GenerateWheel();

    const uint64_t uWheelLimit =
#if _DEBUG
        25000000
#else
        1250000000
#endif
            / ( xNumber.GetLimbCount() * xNumber.GetLimbCount() * 2 - 1 );

    Number xWorkingValue = xNumber;
    Factorisation xResult( xNumber );
    uint64_t uTest = SieveLength * 2 + 1;
    int iDiff = 0;
    Number xTestSquare = 0;
    while( xWorkingValue > xTestSquare )
    {
        if( ( xWorkingValue % uTest ) == 0 )
        {
            xResult.mbKnownComposite = true;
            Factorisation xNew( uTest, true );
            xNew.szFactoringAlgorithm = "trial divison with wheel";
            xNew.szProofName = "trial divison with wheel";
            xNew.miPower = 0;
            do
            {
                ++xNew.miPower;
                xWorkingValue /= uTest;
            }
            while( ( xWorkingValue % uTest ) == 0 );
            xResult.mxKnownFactors.push_back( std::move( xNew ) );
        }

        const uint64_t uOldTest = uTest;
        uTest += saiDifferences[ iDiff ];
        ++iDiff;
        if( iDiff >= siWheelLength )
        {
            iDiff = 0;
        }

        if( uTest > uWheelLimit )
        {
            SetWheelBound( ( Number( uOldTest ) * uOldTest ) - 1ULL );

            xResult.mxKnownFactors.push_back( Factorisation( xWorkingValue ) );
            return xResult;
        }

        xTestSquare = uTest;
        xTestSquare *= uTest;
        --xTestSquare;
    }

    SetWheelBound( Number( uTest ) * uTest - 1ULL );

    if( xResult.mxKnownFactors.empty() )
    {
        xResult.mbKnownPrime = true;
        xResult.szProofName = "trial divison with wheel";
    }
    else if( xWorkingValue > 1 )
    {
        xResult.szProofName = "trial divison with wheel";
        xResult.szFactoringAlgorithm = "trial divison with wheel";
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
