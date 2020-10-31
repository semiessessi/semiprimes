#include "Number.h"

#include "../Algorithms/Arithmetic/Multiplication/MultiplyLimbX64.h"
#include "../Algorithms/Arithmetic/Multiplication/GrammarSchoolX64.h"
#include "../Algorithms/General/BinarySquareRoot.h"
#include "../Algorithms/General/EuclideanGCD.h"

Number Number::operator -() const
{
    Number xCopy( *this );
    xCopy.mbNegative = !xCopy.mbNegative;
    return xCopy;
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
    // handle the possible factor of -1 from the signs of the operands
    mbNegative = xOperand.mbNegative != mbNegative;
    MultiplyX64_GrammarSchool( mxLimbs, xOperand.mxLimbs );
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

Number& Number::operator %=( const Number& xOperand )
{
    DivMod( Number( *this ), xOperand, *this );
    return *this;
}

int64_t Number::operator %( const int64_t iOperand ) const
{
    return Mod( *this, iOperand );
}

uint64_t Number::GetPerfectPower() const
{
    uint64_t uLog2 = MostSignificantBitPosition();
    for( uint64_t u = 1; u < uLog2; ++u )
    {
        // todo...
    }
    return 1;
}

bool Number::IsPerfectSquare() const
{
    Number xRemainder;
    SquareRoot( xRemainder );
    return xRemainder == 0;
}

Number Number::SquareRoot() const
{
    Number xRemainder;
    return SquareRoot( xRemainder );
}

Number Number::SquareRoot( Number& xRemainder ) const
{
    return BinarySquareRoot( *this, xRemainder );
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

Number Number::ModMul(
    const Number& xNumerator,
    const Number& xMultiplicand,
    const Number& xDenominator )
{
    // SE - TODO: better algorithms?
// .. avoid the copy?
    Number xProduct = xNumerator;
    xProduct *= xMultiplicand;
    return xProduct % xDenominator;
}

void Number::InplaceModMul(
    const uint64_t uMultiplicand,
    const uint64_t uDenominator )
{
    *this *= uMultiplicand;
    *this %= uDenominator;
}

void Number::InplaceModMul(
    const Number& xMultiplicand,
    const Number& xDenominator )
{
    *this *= xMultiplicand;
    *this %= xDenominator;
}

Number Number::GCD( const Number& xOther ) const
{
    return GCD_Euclidean( *this, xOther );
}
