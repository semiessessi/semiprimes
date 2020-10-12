#include <intrin.h>
#include <utility>
#include <vector>

void AddX64_BaseCase( std::vector< uint64_t >& xLimbs, const uint64_t uOperand )
{
    unsigned char ucCarry = _addcarryx_u64(
        0,
        xLimbs[ 0 ],
        uOperand,
        &( xLimbs[ 0 ] ) );

    if( ucCarry == 0 )
    {
        return;
    }

    const size_t uLimbCount = xLimbs.size();
    size_t uLimb = 1;

    while( ( ucCarry != 0 )
        && ( uLimb < uLimbCount ) )
    {
        ucCarry = _addcarryx_u64(
            ucCarry,
            xLimbs[ uLimb ],
            0,
            &( xLimbs[ uLimb ] ) );
        ++uLimb;
    }

    if( ucCarry != 0 )
    {
        xLimbs.push_back( 1 );
    }
}

void AddX64_Generic( std::vector< uint64_t >& xLimbs, const std::vector< uint64_t >& xOperandLimbs )
{
    const size_t uOperandSize = xOperandLimbs.size();
    if( uOperandSize > xLimbs.size() )
    {
        xLimbs.resize( uOperandSize, 0 );
    }

    const size_t uLimbCount = xLimbs.size();
    unsigned char ucCarry = 0;
    size_t uLimb = 0;

    for( ; uLimb < uOperandSize; ++uLimb )
    {
        ucCarry = _addcarryx_u64(
            ucCarry,
            xLimbs[ uLimb ],
            xOperandLimbs[ uLimb ],
            &( xLimbs[ uLimb ] ) );
    }

    for( uLimb = uOperandSize; uLimb < uLimbCount; ++uLimb )
    {
        if( ucCarry == 0 )
        {
            break;
        }

        ucCarry = _addcarryx_u64(
            ucCarry,
            xLimbs[ uLimb ],
            0,
            &( xLimbs[ uLimb ] ) );
    }

    if( ucCarry != 0 )
    {
        xLimbs.push_back( 1 );
    }
}
