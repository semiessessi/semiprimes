#include "Number.h"

#include <utility>

Number::Number()
: mxLimbs( { 0 } )
, mbNegative( false )
{
}

Number::Number( const Number& xNumber )
: mxLimbs( xNumber.mxLimbs )
, mbNegative( xNumber.mbNegative )
{
}

Number::Number( Number&& xNumber ) noexcept
: mxLimbs( std::move( xNumber.mxLimbs ) )
, mbNegative( xNumber.mbNegative )
{
}

Number& Number::operator =( const Number& xNumber )
{
    mxLimbs = xNumber.mxLimbs;
    mbNegative = xNumber.mbNegative;
    return *this;
}

Number& Number::operator =( Number&& xNumber )
{
    mxLimbs = std::move( xNumber.mxLimbs );
    mbNegative = xNumber.mbNegative;
    return *this;
}
