#include "Number.h"

#include <utility>

Number::Number()
: mxLimbs( { 0 } )
, mbNegative( false )
{
}

Number::Number( const int iValue )
: mxLimbs( { static_cast< uint64_t >( ( iValue > 0 ) ? iValue : -iValue ) } )
, mbNegative( iValue < 0 )
{
}

Number::Number( const unsigned int uValue )
: mxLimbs( { uValue } )
, mbNegative( false )
{
}

Number::Number( const int64_t iValue )
: mxLimbs( { static_cast< uint64_t >( ( iValue > 0 ) ? iValue : -iValue ) } )
, mbNegative( iValue < 0 )
{
}

Number::Number( const uint64_t uValue )
: mxLimbs( { uValue } )
, mbNegative( false )
{
}

Number::Number( const std::string& xString )
: mxLimbs( { 0 } ) // initialise limb vector
, mbNegative( xString[ 0 ] == '-' ) // SE - TODO: robustness against dodgy inputs
{
    const size_t uStart = ( mbNegative || ( xString[ 0 ] == '+' ) ) ? 1 : 0;
    const size_t uLength = xString.length();
    if( ( uLength >= ( 2 + uStart ) ) && xString[ uStart + 1 ] == 'x' )
    {
        // hex.
        for( size_t uPosition = uStart; uPosition < uLength; ++uPosition )
        {
            *this *= static_cast< uint64_t >( 16 );
            if( static_cast< int64_t >( xString[ uPosition ] ) >= 'a' )
            {
                *this += static_cast< int64_t >( xString[ uPosition ] ) - 'a' + 10;
            }
            else if( static_cast< int64_t >( xString[ uPosition ] ) >= 'A' )
            {
                *this += static_cast< int64_t >( xString[ uPosition ] ) - 'A' + 10;
            }
            else
            {
                *this += static_cast< int64_t >( xString[ uPosition ] ) - '0';
            }
        }
        return;
    }
    
    for( size_t uPosition = uStart; uPosition < uLength; ++uPosition )
    {
        *this *= static_cast< uint64_t >( 10 );
        *this += static_cast< int64_t >( xString[ uPosition ] ) - '0';
    }
}

Number::Number( const std::vector< uint64_t >& xLimbs, const bool bNegative )
: mxLimbs( xLimbs )
, mbNegative( bNegative )
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

Number& Number::operator =( Number&& xNumber ) noexcept
{
    mxLimbs = std::move( xNumber.mxLimbs );
    mbNegative = xNumber.mbNegative;
    return *this;
}

#pragma warning( disable : 4455 )
Number operator ""z( const char* const szToken )
{
    return Number( std::string( szToken ) );
}
#pragma warning( default : 4455 )
