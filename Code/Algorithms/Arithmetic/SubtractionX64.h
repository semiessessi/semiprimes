#ifndef SUBTRACTION_X64_H
#define SUBTRACTION_X64_H

#include <vector>

inline void SubX64_BaseCase( std::vector< uint64_t >& xLimbs, uint64_t uOperand ) noexcept;
inline void SubX64_BaseCase_Placed( std::vector< uint64_t >& xLimbs, uint64_t uOperand, uint64_t uPlace ) noexcept;
inline void SubX64_SmallFromLarge( std::vector< uint64_t >& xLarger, const std::vector< uint64_t >& xSmaller ) noexcept;
inline void SubX64_SmallFromLarge_Placed( std::vector< uint64_t >& xLarger, const std::vector< uint64_t >& xSmaller, uint64_t uPlace ) noexcept;
inline void SubX64_SmallFromLarge_Placed_NoShrink( std::vector< uint64_t >& xLarger, const std::vector< uint64_t >& xSmaller, uint64_t uPlace ) noexcept;

#include "SubtractionX64.inl"

#endif
