#ifndef NUMBER_H
#define NUMBER_H

#pragma warning( disable : 4530 )

#include <cstdint>
#include <string>
#include <vector>

class Number
{

public:

    inline Number() noexcept;
    inline Number( const int iValue ) noexcept;
    inline Number( const unsigned int uValue ) noexcept;
    inline Number( const int64_t iValue ) noexcept;
    inline Number( const uint64_t uValue ) noexcept;
    inline Number( const std::string& xString ) noexcept;
    inline Number( const std::vector<uint64_t>& xLimbs, const bool bNegative = false ) noexcept;
    inline Number( const Number& xNumber ) noexcept;
    inline Number( Number&& xNumber ) noexcept;

    inline Number& operator=( const Number& xNumber ) noexcept;
    inline Number& operator=( Number&& xNumber ) noexcept;

    inline bool operator >( const Number& xOperand ) const noexcept;
    inline bool operator >( const uint64_t uOperand ) const noexcept { return ( mxLimbs.size() > 1 ) || ( mxLimbs[ 0 ] > uOperand ); }
    inline bool operator <( const Number& xOperand ) const noexcept { return xOperand  > *this ; }
    //bool operator <( const uint64_t uOperand ) const { return -*this > -uOperand; }
    inline bool operator <=( const Number& xOperand ) const noexcept { return !( * this > xOperand ); }
    inline bool operator <=( const uint64_t uOperand ) const noexcept { return ( mxLimbs.size() == 1 ) && ( uOperand > mxLimbs[ 0 ] ); }
    inline bool operator >=( const Number& xOperand ) const noexcept { return !( *this < xOperand ); }
    inline bool operator >=( const uint64_t uOperand ) const noexcept { return ( mxLimbs.size() > 1 ) || ( mxLimbs[ 0 ] >= uOperand ); }
    inline bool operator ==( const Number& xOperand ) const noexcept;
    inline bool operator ==( const uint64_t uOperand ) const noexcept { return ( mxLimbs.size() == 1 ) && ( mxLimbs[ 0 ] == uOperand ); }
    inline bool operator !=( const Number& xOperand ) const noexcept { return !( *this == xOperand ); }
    inline bool operator !=( const uint64_t uOperand ) const noexcept { return ( mxLimbs.size() != 1 ) || ( mxLimbs[ 0 ] != uOperand ); }

    inline Number& operator <<=( const uint64_t uOperand ) noexcept;
    inline Number& operator >>=( const uint64_t uOperand ) noexcept;

    inline Number& operator &=( const uint64_t uOperand ) noexcept;
    inline Number& operator |=( const uint64_t uOperand ) noexcept;
    inline Number& operator ^=( const uint64_t uOperand ) noexcept;
    inline uint64_t operator &( const uint64_t uOperand ) const noexcept;

    Number operator -() const noexcept;

    inline Number& operator +=( const int64_t iOperand ) noexcept;
    inline Number& operator +=( const uint64_t iOperand ) noexcept;
    inline Number& operator +=( const Number& xOperand ) noexcept;
    inline Number& operator -=( const int64_t iOperand ) noexcept;
    inline Number& operator -=( const uint64_t iOperand ) noexcept;
    inline Number& operator -=( const Number& xOperand ) noexcept;
    Number& operator *=( const int64_t iOperand ) noexcept;
    Number& operator *=( const uint64_t uOperand ) noexcept;
    Number& operator *=( const Number& xOperand ) noexcept;
    Number& operator /=( const int64_t xOperand ) noexcept;
    Number& operator /=( const Number& xOperand ) noexcept;
    //Number& operator %=( const int64_t iOperand );
    Number& operator %=( const Number& iOperand ) noexcept;
    int64_t operator %( const int64_t iOperand ) const noexcept;

    Number& operator ++() noexcept { return *this += 1ULL; }
    Number& operator --() noexcept { return *this -= 1ULL; }

#define OPERATOR_FROM_INPLACE( op ) \
    Number operator op( const Number& xOperand ) const  noexcept \
    { Number xReturnValue = *this; xReturnValue op##= xOperand; return xReturnValue; } \
    Number operator op( const int64_t iOperand ) const  noexcept \
    { Number xReturnValue = *this; xReturnValue op##= iOperand; return xReturnValue; } \
    Number operator op( const uint64_t uOperand ) const noexcept \
    { Number xReturnValue = *this; xReturnValue op## = uOperand; return xReturnValue; }
#define OPERATOR_FROM_INPLACE_NOINT( op ) \
    Number operator op( const Number& xOperand ) const  noexcept \
    { Number xReturnValue = *this; xReturnValue op##= xOperand; return xReturnValue; }
#define OPERATOR_FROM_INPLACE_NOZ( op ) \
    Number operator op( const int64_t xOperand ) const  noexcept \
    { Number xReturnValue = *this; xReturnValue op##= xOperand; return xReturnValue; }

    OPERATOR_FROM_INPLACE( + )
    OPERATOR_FROM_INPLACE( - )
    OPERATOR_FROM_INPLACE( * )
    OPERATOR_FROM_INPLACE( / )
    OPERATOR_FROM_INPLACE_NOZ( >> )
    OPERATOR_FROM_INPLACE_NOZ( << )
    OPERATOR_FROM_INPLACE_NOINT( % )
    
    inline bool GreaterOrEqualToWithOffset( const Number& xOperand, const uint64_t uPlace ) const noexcept;
    inline void InplaceSubAtLimbOffset( const uint64_t uOther, const uint64_t uPlace ) noexcept;
    inline void InplaceSubAtLimbOffset( const Number& xOther, const uint64_t uPlace ) noexcept;
    inline void InplaceMultiplyBy2() noexcept;
    inline void InplaceLimbShiftLeft( const size_t uLimbs ) noexcept;
    inline void InplaceLimbShiftRight( const size_t uLimbs ) noexcept;
    inline void InplaceNegate() noexcept { mbNegative = !mbNegative; }
    inline void InplaceRemoveLeadingLimb() noexcept { mxLimbs.pop_back(); }

    inline bool GetBit( const uint64_t uIndex ) const noexcept;
    inline void SetBit( const uint64_t uIndex, const bool bValue = true ) noexcept;

    inline uint64_t& GetLimb( const uint64_t uIndex ) noexcept { return mxLimbs[ uIndex ]; }
    inline uint64_t GetLimb( const uint64_t uIndex ) const noexcept { return mxLimbs[ uIndex ]; }
    inline uint64_t GetLimbSafe( const uint64_t uIndex ) const noexcept { if( uIndex < mxLimbs.size() ) { return mxLimbs[ uIndex ]; } return 0; }
    inline void SetLimb( const uint64_t uIndex, const uint64_t uValue ) noexcept
    {
        mxLimbs.resize( ( uIndex < mxLimbs.size() ) ? mxLimbs.size() : uIndex + 1, 0 );
        mxLimbs[ uIndex ] = uValue;
    }
    inline void ZeroFillLimbResize( const size_t i ) noexcept { mxLimbs.resize( i, 0 ); }

    uint64_t GetPerfectPower() const noexcept;
    bool IsPerfectSquare() const noexcept;
    Number SquareRoot() const noexcept;
    Number SquareRoot( Number& xRemainder ) const noexcept;

    inline size_t GetLimbCount() const noexcept { return mxLimbs.size(); }
    inline uint64_t LeastSignificantLimb() const noexcept { return mxLimbs[ 0 ]; }
    inline uint64_t MostSignificantLimb() const noexcept { return mxLimbs.back(); }
    inline uint64_t MostSignificantBitPosition() const noexcept;
    inline void AddZeroLeadingLimb() noexcept { mxLimbs.push_back( 0 ); }

    std::string ToString() const noexcept;

    static inline Number DivMod(
        const Number& xNumerator,
        const int64_t iDenominator,
        int64_t& iRemainder ) noexcept;
    static inline Number DivMod(
        const Number& xNumerator,
        const uint64_t uDenominator,
        uint64_t& uRemainder ) noexcept;
    static inline Number DivMod(
        const Number& xNumerator,
        const Number& xDenominator,
        Number& xRemainder ) noexcept;

    static inline uint64_t Mod(
        const Number& xNumerator,
        const uint64_t uDenominator ) noexcept;

    static uint64_t ModMul(
        const Number& xNumerator,
        const uint64_t uMultiplicand,
        const uint64_t uDenominator ) noexcept;
    static Number ModMul(
        const Number& xNumerator,
        const Number& xMultiplicand,
        const Number& xDenominator ) noexcept;

    void InplaceModMul(
        const uint64_t uMultiplicand,
        const uint64_t uDenominator ) noexcept;
    void InplaceModMul(
        const Number& xMultiplicand,
        const Number& xDenominator ) noexcept;

    Number ModExp( const Number& xExponent, const Number& xModulus ) const noexcept;

    Number GCD( const Number& xOther ) const noexcept;

private:

    std::vector< uint64_t > mxLimbs;
    bool mbNegative;
};

#pragma warning( disable : 4455 )
inline Number operator ""z( const char* const szToken ) noexcept;
#pragma warning( default : 4455 )

#include "Number_Compare.inl"
#include "Number_Copy.inl"

#include "Number_AddSub.inl"
#include "Number_BitOps.inl"
#include "Number_DivMod.inl"
#include "Number_Shift.inl"

#endif
