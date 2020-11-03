#ifndef NUMBER_H
#define NUMBER_H

#pragma warning( disable : 4530 )

#include <cstdint>
#include <string>
#include <vector>

class Number
{

public:

    Number();
    Number( const int iValue );
    Number( const unsigned int uValue );
    Number( const int64_t iValue );
    Number( const uint64_t uValue );
    Number( const std::string& xString );
    Number( const std::vector<uint64_t>& xLimbs, const bool bNegative = false );
    Number( const Number& xNumber );
    Number( Number&& xNumber ) noexcept;

    Number& operator=( const Number& xNumber );
    Number& operator=( Number&& xNumber ) noexcept;

    bool operator >( const Number& xOperand ) const;
    bool operator >( const uint64_t uOperand ) const { return ( mxLimbs.size() > 1 ) || ( mxLimbs[ 0 ] > uOperand ); }
    bool operator <( const Number& xOperand ) const { return xOperand  > *this ; }
    //bool operator <( const uint64_t uOperand ) const { return -*this > -uOperand; }
    bool operator <=( const Number& xOperand ) const { return !( * this > xOperand ); }
    bool operator <=( const uint64_t uOperand ) const { return ( mxLimbs.size() == 1 ) && ( uOperand > mxLimbs[ 0 ] ); }
    bool operator >=( const Number& xOperand ) const { return !( *this < xOperand ); }
    bool operator >=( const uint64_t uOperand ) const { return ( mxLimbs.size() > 1 ) || ( mxLimbs[ 0 ] >= uOperand ); }
    bool operator ==( const Number& xOperand ) const;
    bool operator ==( const uint64_t uOperand ) const { return ( mxLimbs.size() == 1 ) && ( mxLimbs[ 0 ] == uOperand ); }
    bool operator !=( const Number& xOperand ) const { return !( *this == xOperand ); }
    bool operator !=( const uint64_t uOperand ) const { return ( mxLimbs.size() != 1 ) || ( mxLimbs[ 0 ] != uOperand ); }

    Number& operator <<=( const uint64_t uOperand );
    Number& operator >>=( const uint64_t uOperand );

    Number& operator &=( const uint64_t uOperand );
    Number& operator |=( const uint64_t uOperand );
    Number& operator ^=( const uint64_t uOperand );
    uint64_t operator &( const uint64_t uOperand ) const;

    Number operator -() const;

    Number& operator +=( const int64_t iOperand );
    Number& operator +=( const uint64_t iOperand );
    Number& operator +=( const Number& xOperand );
    Number& operator -=( const int64_t iOperand );
    Number& operator -=( const uint64_t iOperand );
    Number& operator -=( const Number& xOperand );
    Number& operator *=( const int64_t iOperand );
    Number& operator *=( const uint64_t uOperand );
    Number& operator *=( const Number& xOperand );
    Number& operator /=( const int64_t xOperand );
    Number& operator /=( const Number& xOperand );
    //Number& operator %=( const int64_t iOperand );
    Number& operator %=( const Number& iOperand );
    int64_t operator %( const int64_t iOperand ) const;

    Number& operator ++() { return *this += 1ULL; }
    Number& operator --() { return *this -= 1ULL; }

#define OPERATOR_FROM_INPLACE( op ) \
    Number operator op( const Number& xOperand ) const \
    { Number xReturnValue = *this; xReturnValue op##= xOperand; return xReturnValue; } \
    Number operator op( const int64_t xOperand ) const \
    { Number xReturnValue = *this; xReturnValue op##= xOperand; return xReturnValue; }
#define OPERATOR_FROM_INPLACE_NOINT( op ) \
    Number operator op( const Number& xOperand ) const \
    { Number xReturnValue = *this; xReturnValue op##= xOperand; return xReturnValue; }
#define OPERATOR_FROM_INPLACE_NOZ( op ) \
    Number operator op( const int64_t xOperand ) const \
    { Number xReturnValue = *this; xReturnValue op##= xOperand; return xReturnValue; }

    OPERATOR_FROM_INPLACE( + )
    OPERATOR_FROM_INPLACE( - )
    OPERATOR_FROM_INPLACE( * )
    OPERATOR_FROM_INPLACE( / )
    OPERATOR_FROM_INPLACE_NOZ( >> )
    OPERATOR_FROM_INPLACE_NOZ( << )
    OPERATOR_FROM_INPLACE_NOINT( % )
    
    void InplaceMultiplyBy2();
    void InplaceLimbShiftLeft( const size_t uLimbs );
    void InplaceLimbShiftRight( const size_t uLimbs );
    void InplaceNegate() { mbNegative = !mbNegative; }

    bool GetBit( const uint64_t uIndex ) const;
    void SetBit( const uint64_t uIndex, const bool bValue = true );

    uint64_t& GetLimb( const uint64_t uIndex ) { return mxLimbs[ uIndex ]; }
    uint64_t GetLimb( const uint64_t uIndex ) const { return mxLimbs[ uIndex ]; }

    uint64_t GetPerfectPower() const;
    bool IsPerfectSquare() const;
    Number SquareRoot() const;
    Number SquareRoot( Number& xRemainder ) const;

    size_t GetLimbCount() const { return mxLimbs.size(); }
    uint64_t LeastSignificantLimb() const { return mxLimbs[ 0 ]; }
    uint64_t MostSignificantLimb() const { return mxLimbs.back(); }
    uint64_t MostSignificantBitPosition() const;
    void AddZeroLeadingLimb() { mxLimbs.push_back( 0 ); }

    std::string ToString() const;

    static Number DivMod(
        const Number& xNumerator,
        const int64_t iDenominator,
        int64_t& iRemainder );
    static Number DivMod(
        const Number& xNumerator,
        const uint64_t uDenominator,
        uint64_t& uRemainder );
    static Number DivMod(
        const Number& xNumerator,
        const Number& xDenominator,
        Number& xRemainder );

    static uint64_t Mod(
        const Number& xNumerator,
        const uint64_t uDenominator );

    static uint64_t ModMul(
        const Number& xNumerator,
        const uint64_t uMultiplicand,
        const uint64_t uDenominator );
    static Number ModMul(
        const Number& xNumerator,
        const Number& xMultiplicand,
        const Number& xDenominator );

    void InplaceModMul(
        const uint64_t uMultiplicand,
        const uint64_t uDenominator );
    void InplaceModMul(
        const Number& xMultiplicand,
        const Number& xDenominator );

    Number ModExp( const Number& xExponent, const Number& xModulus ) const;

    Number GCD( const Number& xOther ) const;

private:

    std::vector< uint64_t > mxLimbs;
    bool mbNegative;
};

#pragma warning( disable : 4455 )
Number operator ""z( const char* const szToken );
#pragma warning( default : 4455 )

#endif
