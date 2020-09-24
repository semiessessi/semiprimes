#include "Timing.h"

#include <chrono>
#include <cstdint>
#include <cstdio>

static std::chrono::steady_clock::time_point sxStart;
static std::chrono::steady_clock::time_point sxEnd;

void StartTiming( const bool bVerbose )
{
    sxStart = std::chrono::high_resolution_clock::now();

    if( bVerbose )
    {
        puts( "Starting timer." );
    }
}

void StopTiming()
{
    sxEnd = std::chrono::high_resolution_clock::now();

    int64_t iDuration =
        std::chrono::duration_cast< std::chrono::nanoseconds >(
            sxEnd - sxStart ).count();

    printf(
        "Took %d.%09d seconds\n",
        iDuration / 1000000000,
        iDuration % 1000000000 );
}
