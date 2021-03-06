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
        && ( uLimb < uLimbCount );
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

void SubX64_BaseCase_Placed( std::vector< uint64_t >& xLimbs, uint64_t uOperand, uint64_t uPlace )
{
    unsigned char ucBorrow = 0;
    size_t uLimb = uPlace + 1;
    ucBorrow = _subborrow_u64(
        ucBorrow,
        xLimbs[ uPlace ],
        uOperand,
        &( xLimbs[ uPlace ] ) );
    const size_t uLimbCount = xLimbs.size();
    bool bContinueBorrow = ( ucBorrow > 0 )
        && ( uLimb < uLimbCount );
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
    size_t uLimb = 0;
    const size_t uLimbCount = xGreater.size();
    const size_t uSmallerLimbCount = xSmaller.size();
    for( ; uLimb < uSmallerLimbCount; ++uLimb )
    {
        ucBorrow = _subborrow_u64(
            ucBorrow,
            xGreater[ uLimb ],
            xSmaller[ uLimb ],
            &( xGreater[ uLimb ] ) );
    }

    bool bContinueBorrow = ( ucBorrow > 0 )
        && ( uLimb < uLimbCount );
    while( bContinueBorrow )
    {
        ucBorrow = _subborrow_u64(
            ucBorrow,
            xGreater[ uLimb ],
            0,
            &( xGreater[ uLimb ] ) );
        ++uLimb;
        bContinueBorrow = ( ucBorrow > 0 )
            && ( uLimb < uLimbCount );
    }

    while( ( xGreater.back() == 0 ) && ( xGreater.size() > 1 ) )
    {
        xGreater.pop_back();
    }

    // this should not happen
    //if( bContinueBorrow )
    //{
        // SE - TODO: flag some problem!
    //}
}

void SubX64_SmallFromLarge_Placed( std::vector< uint64_t >& xGreater, const std::vector< uint64_t >& xSmaller, uint64_t uPlace )
{
    unsigned char ucBorrow = 0;
    size_t uLimb = uPlace;
    const size_t uLimbCount = xGreater.size();
    const size_t uSmallerLimbCount = xSmaller.size() + uPlace;
    for( ; uLimb < uSmallerLimbCount; ++uLimb )
    {
        ucBorrow = _subborrow_u64(
            ucBorrow,
            xGreater[ uLimb ],
            xSmaller[ uLimb - uPlace ],
            &( xGreater[ uLimb ] ) );
    }

    bool bContinueBorrow = ( ucBorrow > 0 )
        && ( uLimb < uLimbCount );
    while( bContinueBorrow )
    {
        ucBorrow = _subborrow_u64(
            ucBorrow,
            xGreater[ uLimb ],
            0,
            &( xGreater[ uLimb ] ) );
        ++uLimb;
        bContinueBorrow = ( ucBorrow > 0 )
            && ( uLimb < uLimbCount );
    }

    while( ( xGreater.back() == 0 ) && ( xGreater.size() > 1 ) )
    {
        xGreater.pop_back();
    }
}
