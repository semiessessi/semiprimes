#ifndef TIMING_H
#define TIMING_H

#include <cstdint>

void StartTiming( const bool bVerbose );
void StopTiming();
int64_t GetTimingNS();

#endif
