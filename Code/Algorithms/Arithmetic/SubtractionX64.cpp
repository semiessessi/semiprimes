#include <intrin.h>
#include <utility>
#include <vector>

void SubX64_BaseCase( std::vector< uint64_t >& xLimbs, uint64_t uOperand )
{
    unsigned char ucBorrow = 0;
    size_t uLimb = 1;
    ucBorrow = _subborrow_u64(
        ucBorrow,
        xLimbs[ 0 ],
        uOperand,
        &( xLimbs[ 0 ] ) );
    const size_t uLimbCount = xLimbs.size();
    bool bContinueBorrow = ( ucBorrow > 0 )
        && ( uLimbCount <= uLimb );
    while( bContinueBorrow )
    {
        ucBorrow = _subborrow_u64(
            ucBorrow,
            xLimbs[ uLimb ],
            0,
            &( xLimbs[ uLimb ] ) );
        ++uLimb;
        bContinueBorrow = ( ucBorrow > 0 )
            && ( uLimb < uLimbCount );
    }
}

void SubX64_SmallFromLarge( std::vector< uint64_t >& xGreater, const std::vector< uint64_t >& xSmaller )
{
    unsigned char ucBorrow = 0;
    size_t uLimb = 1;
    ucBorrow = _subborrow_u64(
        ucBorrow,
        xGreater[ 0 ],
        xSmaller[ 0 ],
        &( xGreater[ 0 ] ) );
    const size_t uLimbCount = xGreater.size();
    bool bContinueBorrow = ( ucBorrow > 0 )
        && ( uLimbCount <= uLimb );
    while( bContinueBorrow )
    {
        ucBorrow = _subborrow_u64(
            ucBorrow,
            xGreater[ uLimb ],
            xSmaller[ uLimb ],
            &( xGreater[ uLimb ] ) );
        ++uLimb;
        bContinueBorrow = ( ucBorrow > 0 )
            && ( uLimb < uLimbCount );
    }

    // this should not happen
    //if( bContinueBorrow )
    //{
        // SE - TODO: flag some problem!
    //}
}
