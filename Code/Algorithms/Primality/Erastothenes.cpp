#include <cstdint>
#include <vector>

#include "Wheel.h"

void InitialisePrimesUpTo( const uint64_t uLimit );

uint64_t guPrimeCount = 0;
std::vector< uint64_t > gauPrimes;
// wheel primes go beyond 2048
// 2048 = ( 1 << 11 )
// in princple up to 1ULL << ( 22 ) should be fine.
static const uint64_t kuChunkCount =
#ifdef _DEBUG
    ( 1ULL << 18 ) // 256K
#else
    ( 1ULL << 20 ) // 1M
#endif
    ;

std::vector< uint64_t > gauSieve;

// sieve next lot of primes
void SieveNextPrimes( const uint64_t uStart )
{
    gauSieve.resize( kuChunkCount );
    // for each prime in the sieve already...
    // entries in the array are odd numbers

    // round to next odd number
    uint64_t uBegin = ( uStart & ~0x1ULL ) | 1ULL;
    // work out end point for the range to sieve
    uint64_t uEnd = uStart + ( kuChunkCount << 1 );
    
    // work out limit for primes to sieve with
    uint64_t uSqrtEnd = static_cast< uint64_t >(
        sqrtl( static_cast< long double >( uEnd ) ) );
    uint64_t uSievePrime = 1;
    // initialise the values
    for( uint64_t u = 0; u < kuChunkCount; ++u )
    {
        gauSieve[ u ] = uBegin + ( u << 1 );
    }

    while( gauPrimes[ uSievePrime ] < uSqrtEnd )
    {
        uint64_t uPrime = gauPrimes[ uSievePrime ];
        uint64_t uStartPosition = uBegin % uPrime;
        uStartPosition = ( ( uStartPosition & 0x1 )
            ? ( ( uPrime - uStartPosition ) >> 1 )
            : ( uPrime - ( uStartPosition >> 1 ) ) );
        for( uint64_t i = uStartPosition; i < kuChunkCount; i+= uPrime )
        {
            gauSieve[ i ] = 0;
        }
        ++uSievePrime;
    }

    // pick out remaining numbers into the primes list.
    for( uint64_t u = 0; u < kuChunkCount; ++u )
    {
        if( gauSieve[ u ] != 0 )
        {
            gauPrimes[ guPrimeCount ] = gauSieve[ u ];
            ++guPrimeCount;
        }
    }
}

uint64_t* GetSievedPrimes()
{
    return &( gauPrimes[ 0 ] );
}

uint64_t GetSievedPrimeCount()
{
    return guPrimeCount;
}

void InitialisePrimesUpTo( const uint64_t uLimit )
{
    if( guPrimeCount == 0 )
    {
        // initial initialisation
        guPrimeCount = sizeof( aiWheelPrimes ) / sizeof( aiWheelPrimes[ 0 ] );
        // assume the limit is big enough
        gauPrimes.resize( ( uLimit + kuChunkCount ) >> 2, 0 );
        for( int i = 0; i < guPrimeCount; ++i )
        {
            gauPrimes[ i ] = aiWheelPrimes[ i ];
        }
    }

    // already got enough...
    uint64_t uStart = gauPrimes[ guPrimeCount - 1 ];
    if( uStart > uLimit )
    {
        return;
    }

    // otherwise wheel up to the amount we need.
    uint64_t uAmount = ( ( uLimit - uStart ) / kuChunkCount ) + 1;
    for( uint64_t u = 0; u < uAmount; ++u )
    {
        SieveNextPrimes( uStart );
        // continue from last prime.
        // (is continuing the range cleaner?)
        uStart = gauPrimes[ guPrimeCount - 1 ];
        if( uStart > uLimit )
        {
            break;
        }
    }

}
