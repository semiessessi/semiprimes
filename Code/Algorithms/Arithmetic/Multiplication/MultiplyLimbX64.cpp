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
            uOperand, xLimbs[ uLimb ], &uUpperPart );
        const uint64_t uAddCarry = _addcarryx_u64(
            0, xLimbs[ uLimb ], uCarry, &( xLimbs[ uLimb ] ) );
        uCarry = uUpperPart + uAddCarry;
    }

    if( uCarry > 0 )
    {
        xLimbs.push_back( uCarry );
    }
}
