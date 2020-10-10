#include "Number.h"

#include <intrin.h>

bool Number::GetBit( const uint64_t uIndex ) const
{
    return ( mxLimbs[ uIndex >> 6 ] & ( 1uLL << ( uIndex & 63 ) ) ) != 0;
}

void Number::SetBit( const uint64_t uIndex, const bool bValue )
{
    const uint64_t uLimbIndex = uIndex >> 6;
    if( mxLimbs.size() <= uLimbIndex )
    {
        mxLimbs.resize( uLimbIndex + 1 );
    }

    if( bValue )
    {
        mxLimbs[ uLimbIndex ] |= ( 1uLL << ( uIndex & 63 ) );
    }
    else
    {
        mxLimbs[ uLimbIndex ] &= ~( 1uLL << ( uIndex & 63 ) );
    }
}

uint64_t Number::MostSignificantBitPosition() const
{
    const uint64_t uBase = ( mxLimbs.size() - 1 ) * 64;
    const uint64_t uMSL = MostSignificantLimb();
    unsigned long uMSLMSB = 0;
    _BitScanReverse64( &uMSLMSB, uMSL );
    return uBase + uMSLMSB;
}

Number& Number::operator &=( const uint64_t uOperand )
{
    mxLimbs.resize( 1 );
    mxLimbs[ 0 ] &= uOperand;
    return *this;
}

Number& Number::operator |=( const uint64_t uOperand )
{
    mxLimbs[ 0 ] |= uOperand;
    return *this;
}

Number& Number::operator ^=( const uint64_t uOperand )
{
    mxLimbs[ 0 ] ^= uOperand;
    return *this;
}

uint64_t Number::operator &( const uint64_t uOperand ) const
{
    return mxLimbs[ 0 ] & uOperand;
}
