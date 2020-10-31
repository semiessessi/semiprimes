#include "Timing.h"

#include <chrono>
#include <cstdint>
#include <cstdio>

static std::chrono::steady_clock::time_point sxStart;
static std::chrono::steady_clock::time_point sxEnd;
static std::chrono::steady_clock::time_point sxSampler;

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
        "Took %lld.%09lld seconds\n",
        iDuration / 1000000000,
        iDuration % 1000000000 );
}

int64_t GetTimingNS()
{
    sxSampler = std::chrono::high_resolution_clock::now();

    return
        std::chrono::duration_cast< std::chrono::nanoseconds >(
            sxSampler - sxStart ).count();
}
