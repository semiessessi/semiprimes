#ifndef MULTIPLY_LIMB_X64_H
#define MULTIPLY_LIMB_X64_H

#include <vector>

inline void MultiplyX64_BaseCase( std::vector< uint64_t >& xLimbs, const uint64_t uOperand );

#include "MultiplyLimbX64.inl"

#endif
