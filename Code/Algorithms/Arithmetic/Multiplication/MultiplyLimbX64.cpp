#include <intrin.h>
#include <vector>

void MultiplyX64_BaseCase( std::vector< uint64_t >& xLimbs, const uint64_t uOperand )
{
    const size_t uLimbCount = xLimbs.size();
    uint64_t uUpperPart = 0;
    uint64_t uCarry = 0;
    for( size_t uLimb = 0; uLimb < uLimbCount; ++uLimb )
    {
        xLimbs[ uLimb ] = _umul128(
            uOperand, xLimbs[ uLimb ], &uUpperPart )
            + uCarry;   // add the previous carry as we go along
                        // this shouldn't overflow since the biggest pair
                        // of numbers multiply to:
                        // (2^64-1)(2^64-1) = 2^128 - 2.2^64 + 1
                        // ??? maybe? should verify that more.

        uCarry = uUpperPart;
    }

    if( uCarry > 0 )
    {
        xLimbs.push_back( uCarry );
    }
}
