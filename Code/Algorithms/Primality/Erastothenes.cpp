#include <cstdint>
#include <vector>

#include "Wheel.h"

uint64_t guPrimeCount = 0;
std::vector< uint64_t > gauPrimes;

void InitialisePrimesUpTo( const uint64_t uLimit )
{
    if( guPrimeCount == 0 )
    {
        // initial initialisation
        guPrimeCount = sizeof( aiWheelPrimes ) / sizeof( aiWheelPrimes[ 0 ] );
        // assume the limit is big enough
        gauPrimes.resize( uLimit >> 2, 0 );
        for( int i = 0; i < guPrimeCount; ++i )
        {
            gauPrimes[ i ] = aiWheelPrimes[ i ];
        }
    }

    // already got enough...
    if( gauPrimes[ guPrimeCount - 1 ] > uLimit )
    {
        return;
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
