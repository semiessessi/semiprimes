#ifndef ADDITION_x64_H
#define ADDITION_x64_H

#include <vector>

inline void AddX64_BaseCase( std::vector< uint64_t >& xLimbs, const uint64_t uOperand ) noexcept;
inline void AddX64_Generic( std::vector< uint64_t >& xLimbs, const std::vector< uint64_t >& xOperandLimbs ) noexcept;
inline void AddX64_Generic_Placed( std::vector< uint64_t >& xLimbs, const std::vector< uint64_t >& xOperandLimbs, uint64_t uPlace ) noexcept;

#include "AdditionX64.inl"

#endif
