#ifndef ADDITION_x64_H
#define ADDITION_x64_H

#include <vector>

void AddX64_BaseCase( std::vector< uint64_t >& xLimbs, const uint64_t uOperand );
void AddX64_Generic( std::vector< uint64_t >& xLimbs, const std::vector< uint64_t >& xOperandLimbs );

#endif
