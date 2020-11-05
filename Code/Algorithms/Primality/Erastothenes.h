#ifndef ERASTOTHENES_H
#define ERASTOTHENES_H

#include <cstdint>

void InitialisePrimesUpTo( const uint64_t uLimit );
uint64_t* GetSievedPrimes();
uint64_t GetSievedPrimeCount();

#endif
