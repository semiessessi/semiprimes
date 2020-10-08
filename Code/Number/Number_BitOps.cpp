#include "Number.h"

bool Number::GetBit( const uint64_t uIndex ) const
{
    return ( mxLimbs[ uIndex >> 6 ] & ( 1uLL << ( uIndex & 63 ) ) ) != 0;
}

void Number::SetBit( const uint64_t uIndex, const bool bValue )
{
    if( bValue )
    {
        mxLimbs[ uIndex >> 6 ] |= ( 1uLL << ( uIndex & 63 ) );
    }
    else
    {
        mxLimbs[ uIndex >> 6 ] &= ~( 1uLL << ( uIndex & 63 ) );
    }
}

uint64_t Number::MostSignificantBitPosition() const
{
    const uint64_t uBase = ( mxLimbs.size() - 1 ) * 64;
    const uint64_t uMSL = MostSignificantLimb();
    // find the last bit with binary search
    uint64_t uPosition = 0;
    uPosition += ( uMSL & 0xFFFFFFFF00000000uLL ) ? 32 : 0;
    uPosition += ( uMSL & 0xFFFF0000FFFF0000uLL ) ? 16 : 0;
    uPosition += ( uMSL & 0xFF00FF00FF00FF00uLL ) ? 8 : 0;
    uPosition += ( uMSL & 0xF0F0F0F0F0F0F0F0uLL ) ? 4 : 0;
    uPosition += ( uMSL & 0xCCCCCCCCCCCCCCCCuLL ) ? 2 : 0;
    uPosition += ( uMSL & 0xAAAAAAAAAAAAAAAAuLL ) ? 1 : 0;
    return uPosition + uBase;
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
