#ifndef SUBTRACTION_X64_H
#define SUBTRACTION_X64_H

#include <vector>

void SubX64_BaseCase( std::vector< uint64_t >& xLimbs, uint64_t uOperand );
void SubX64_BaseCase_Placed( std::vector< uint64_t >& xLimbs, uint64_t uOperand, uint64_t uPlace );
void SubX64_SmallFromLarge( std::vector< uint64_t >& xLarger, const std::vector< uint64_t >& xSmaller );
void SubX64_SmallFromLarge_Placed( std::vector< uint64_t >& xLarger, const std::vector< uint64_t >& xSmaller, uint64_t uPlace );

#endif
