#include "Number.h"

Number& Number::operator <<=( const uint64_t uOperand )
{
    if( ( mxLimbs.size() == 1 )
        && ( mxLimbs.back() == 0 ) )
    {
        return *this;
    }

    const uint64_t uMSB = MostSignificantBitPosition();
    const uint64_t uNewMSB = uMSB + uOperand;
    const uint64_t uLimbOffset = uOperand >> 6;
    const uint64_t uLimbsNeeded = ( uNewMSB >> 6 ) + 1;
    const uint64_t uBitOffset = uOperand & 63;
    if( uBitOffset == 0 )
    {
        InplaceLimbShiftLeft( uLimbOffset );
        return *this;
    }

    mxLimbs.resize( uLimbsNeeded, 0 );
    const uint64_t uLimbCount = mxLimbs.size();
    const uint64_t uInverseBitOffset = 64uLL - uBitOffset;
    const uint64_t uNextMask = ( 1uLL << uInverseBitOffset ) - 1uLL;
    const uint64_t uPreviousMask = ~uNextMask;
    for( uint64_t i = uLimbCount - 1; i > uLimbOffset; --i )
    {
        const uint64_t uSourceIndex = i - uLimbOffset;
        mxLimbs[ i ] = ( ( mxLimbs[ uSourceIndex ] & uNextMask ) << uBitOffset )
            | ( ( mxLimbs[ uSourceIndex - 1 ] & uPreviousMask ) >> uInverseBitOffset );
    }

    mxLimbs[ uLimbOffset ] = mxLimbs[ 0 ] << uBitOffset;

    for( uint64_t i = 0; i < uLimbOffset; ++i )
    {
        mxLimbs[ i ] = 0;
    }

    return *this;
}

Number& Number::operator >>=( const uint64_t uOperand )
{
    const uint64_t uMSB = MostSignificantBitPosition();
    if( uOperand >= uMSB )
    {
        mxLimbs.resize( 1 );
        mxLimbs[ 0 ] = 0;
        return *this;
    }

    //const uint64_t uNewMSB = uMSB - uOperand;
    const uint64_t uLimbOffset = uOperand >> 6;
    const uint64_t uBitOffset = uOperand & 63;
    if( uBitOffset == 0 )
    {
        InplaceLimbShiftRight( uLimbOffset );
        return *this;
    }

    const uint64_t uLimbCount = mxLimbs.size() - uLimbOffset;
    const uint64_t uInverseBitOffset = 64uLL - uBitOffset;
    const uint64_t uNextMask = ( 1uLL << uBitOffset ) - 1uLL;
    const uint64_t uPreviousMask = ~uNextMask;
    for( uint64_t i = uLimbOffset + 1; i < uLimbCount; ++i )
    {
        const uint64_t uSourceIndex = i - uLimbOffset;
        mxLimbs[ i - 1 ] = ( ( mxLimbs[ uSourceIndex ] & uNextMask ) << uInverseBitOffset)
            | ( ( mxLimbs[ uSourceIndex - 1 ] & uPreviousMask ) >> uBitOffset );
    }

    mxLimbs.back() >>= uBitOffset;
    
    mxLimbs.resize( mxLimbs.size() - uLimbOffset );
    if( mxLimbs.back() == 0 )
    {
        mxLimbs.pop_back();
    }

    return *this;
}

void Number::InplaceLimbShiftLeft( const size_t uLimbs )
{
    // maintain zero as zero when shifted
    if( mxLimbs.size() == 1 )
    {
        if( mxLimbs[ 0 ] == 0 )
        {
            return;
        }
    }

    // add new limbs and copy
    mxLimbs.resize( mxLimbs.size() + uLimbs );
    size_t uLimb = mxLimbs.size();
    while( uLimb > uLimbs )
    {
        --uLimb;
        mxLimbs[ uLimb ] = mxLimbs[ uLimb - uLimbs ];
    }

    // fill zeroes...
    for( size_t uLimb = 0; uLimb < uLimbs; ++uLimb )
    {
        mxLimbs[ uLimb ] = 0;
    }
}

void Number::InplaceLimbShiftRight( const size_t uLimbs )
{
    // copy
    const size_t uShiftAmount =
        ( uLimbs > mxLimbs.size() ) ? mxLimbs.size() : uLimbs;
    const size_t uLimbCount = mxLimbs.size();
    const size_t uNewLimbCount = uLimbCount - uLimbs;
    for( size_t uLimb = 0; uLimb < uNewLimbCount; ++uLimb )
    {
        mxLimbs[ uLimb ] = mxLimbs[ uLimb + uLimbs ];
    }

    // shrink
    if( uNewLimbCount > 0 )
    {
        mxLimbs.resize( uNewLimbCount );
    }
    else
    {
        mxLimbs.resize( 0 );
        mxLimbs[ 0 ] = 0;
    }
}
