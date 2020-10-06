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
    Number( const Number& xNumber );
    Number( Number&& xNumber ) noexcept;

    Number& operator=( const Number& xNumber );
    Number& operator=( Number&& xNumber ) noexcept;

    bool operator >( const Number& xOperand ) const;
    bool operator >( const uint64_t uOperand ) const { return ( mxLimbs.size() > 1 ) || ( mxLimbs[ 0 ] > uOperand ); }
    bool operator <( const Number& xOperand ) const { return -*this > -xOperand; }
    //bool operator <( const uint64_t uOperand ) const { return -*this > -uOperand; }
    bool operator <=( const Number& xOperand ) const { return xOperand > * this; }
    bool operator <=( const uint64_t uOperand ) const { return ( mxLimbs.size() == 1 ) && ( uOperand > mxLimbs[ 0 ] ); }
    bool operator >=( const Number& xOperand ) const { return xOperand < *this; }
    bool operator >=( const uint64_t uOperand ) const { return ( mxLimbs.size() > 1 ) || ( mxLimbs[ 0 ] >= uOperand ); }
    bool operator ==( const Number& xOperand ) const;
    bool operator ==( const uint64_t uOperand ) const { return ( mxLimbs.size() == 1 ) && ( mxLimbs[ 0 ] == uOperand ); }
    bool operator !=( const Number& xOperand ) const { return !( *this == xOperand ); }
    bool operator !=( const uint64_t uOperand ) const { return ( mxLimbs.size() != 1 ) || ( mxLimbs[ 0 ] != uOperand ); }

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
    int64_t operator %( const int64_t iOperand ) const;

#define OPERATOR_FROM_INPLACE( op ) \
    Number operator op( const Number& xOperand ) const \
    { Number xReturnValue = *this; xReturnValue op##= xOperand; return xReturnValue; } \
    Number operator op( const int64_t xOperand ) const \
    { Number xReturnValue = *this; xReturnValue op##= xOperand; return xReturnValue; }

    OPERATOR_FROM_INPLACE( + )
    OPERATOR_FROM_INPLACE( - )
    OPERATOR_FROM_INPLACE( * )
    OPERATOR_FROM_INPLACE( / )
    
    void InplaceLimbShiftLeft( const size_t uLimbs );
    void InplaceLimbShiftRight( const size_t uLimbs );
    void InplaceNegate() { mbNegative = !mbNegative; }

    size_t GetLimbCount() const { return mxLimbs.size(); }
    uint64_t LeastSignificantLimb() const { return mxLimbs[ 0 ]; }

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

private:

    std::vector< uint64_t > mxLimbs;
    bool mbNegative;
};

#pragma warning( disable : 4455 )
Number operator ""z( const char* const szToken );
#pragma warning( default : 4455 )

#endif
