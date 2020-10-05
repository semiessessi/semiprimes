#ifndef SUBTRACTION_X64_H
#define SUBTRACTION_X64_H

#include <vector>

void SubX64_BaseCase( std::vector< uint64_t >& xLimbs, uint64_t uOperand );
void SubX64_SmallFromLarge( std::vector< uint64_t >& xLarger, const std::vector< uint64_t >& xSmaller );

#endif
