#ifndef ADDITION_x64_H
#define ADDITION_x64_H

#include <vector>

void AddX64_BaseCase( std::vector< uint64_t >& xLimbs, const uint64_t uOperand );
void AddX64_Generic( std::vector< uint64_t >& xLimbs, const std::vector< uint64_t >& xOperandLimbs );
void AddX64_Generic_Placed( std::vector< uint64_t >& xLimbs, const std::vector< uint64_t >& xOperandLimbs, uint64_t uPlace );

#endif
