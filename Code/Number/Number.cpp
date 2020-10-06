#include "Number.h"

#include "../Algorithms/Arithmetic/Multiplication/MultiplyLimbX64.h"

Number Number::operator -() const
{
    Number xCopy( *this );
    xCopy.mbNegative = !xCopy.mbNegative;
    return xCopy;
}

uint64_t Number::operator &( const uint64_t uOperand ) const
{
    return mxLimbs[ 0 ] & uOperand;
}

Number& Number::operator *=( const int64_t iOperand )
{
    // handle the possible factor of -1 from the signs of the operands
    mbNegative = ( iOperand < 0 ) != mbNegative;

    const uint64_t uOperand = static_cast< uint64_t >( iOperand );
    MultiplyX64_BaseCase( mxLimbs, uOperand );

    return *this;
}

Number& Number::operator *=( const uint64_t uOperand )
{
    MultiplyX64_BaseCase( mxLimbs, uOperand );
    return *this;
}

Number& Number::operator *=( const Number& xOperand )
{
    // SE - TODO: ...

    return *this;
}

Number& Number::operator /=( const int64_t iOperand )
{
    static int64_t iDeadRemainder; // :(
    *this = DivMod( *this, iOperand, iDeadRemainder );
    return *this;
}

Number& Number::operator /=( const Number& xOperand )
{
    static Number xDeadRemainder; // :(
    *this = DivMod( *this, xOperand, xDeadRemainder );
    return *this;
}

int64_t Number::operator %( const int64_t iOperand ) const
{
    return Mod( *this, iOperand );
}

std::string Number::ToString() const
{
    std::string xReturnValue = "";
    if( mbNegative )
    {
        xReturnValue += "-";
    }

    Number xWorkingValue = *this;
    while( xWorkingValue > 0 )
    {
        xReturnValue = std::to_string( xWorkingValue % 10 ) + xReturnValue;
        xWorkingValue /= 10;
    }

    return xReturnValue;
}

uint64_t Number::ModMul(
    const Number& xNumerator,
    const uint64_t uMultiplicand,
    const uint64_t uDenominator )
{
    // SE - TODO: better algorithms?
    // .. avoid the copy?
    Number xProduct = xNumerator;
    xProduct *= uMultiplicand;
    return xProduct % uDenominator;
}
