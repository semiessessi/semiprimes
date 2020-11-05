#include "../../../Number/Number.h"

#include <intrin.h>

// just enough 128-bit arithmetic to work with
class uint128d_t
{
    friend Number AlgorithmD( const Number& xNumerator, const Number& xDenominator, Number& xRemainder );

public:

    uint128d_t( const uint64_t u = 0 )
    : muHighPart( 0 )
    , muLowPart( u )
    {

    }

    uint128d_t( const uint64_t uHigh, const uint64_t uLow )
    : muHighPart( uHigh )
    , muLowPart( uLow )
    {

    }

    bool operator >( const uint128d_t& xOther ) const
    {
        return ( muHighPart > xOther.muHighPart )
            ? true
            : ( muHighPart == xOther.muHighPart ) && ( muLowPart > xOther.muLowPart );
    }

    uint128d_t& operator +=( const uint128d_t& xOther )
    {
        const unsigned char ucCarry =
            _addcarryx_u64( 0, muLowPart, xOther.muLowPart, &muLowPart );
        _addcarryx_u64( ucCarry, muHighPart, xOther.muHighPart, &muHighPart );
        return *this;
    }

    uint128d_t& operator -=( const uint128d_t& xOther )
    {
        const unsigned char ucCarry =
            _subborrow_u64( 0, muLowPart, xOther.muLowPart, &muLowPart );
        _subborrow_u64( ucCarry, muHighPart, xOther.muHighPart, &muHighPart );
        return *this;
    }

    uint128d_t& operator *=( const uint64_t& uMultiplicand )
    {
        uint64_t uCarry;
        muLowPart = _umul128(
            muLowPart, uMultiplicand, &uCarry );
        muHighPart += _umul128(
            muHighPart + uCarry, uMultiplicand, &uCarry );
        return *this;
    }

    uint128d_t operator +( const uint128d_t& xOther ) const
    {
        uint128d_t xResult = *this;
        xResult += xOther;
        return xResult;
    }

    uint128d_t operator -( const uint128d_t& xOther ) const
    {
        uint128d_t xResult = *this;
        xResult -= xOther;
        return xResult;
    }

    uint128d_t operator *( const uint64_t xOther ) const
    {
        uint128d_t xResult = *this;
        xResult *= xOther;
        return xResult;
    }

    uint128d_t Divide( const uint64_t uDivisor, uint64_t& uRemainder )
    {
        bool bOverflow = muHighPart > uDivisor;
        uint128d_t uQuotient = *this;
        uQuotient.InplaceDivide( uDivisor, uRemainder );
        return uQuotient;
    }

    uint128d_t& InplaceDivide( const uint64_t uDivisor, uint64_t& uRemainder )
    {
        bool bOverflow = muHighPart > uDivisor;
        if( bOverflow )
        {
            uRemainder = 0;
            muHighPart = _udiv128(
                uRemainder, muHighPart, uDivisor, &uRemainder );
            muLowPart = _udiv128(
                uRemainder, muLowPart, uDivisor, &uRemainder );
        }
        else
        {
            muHighPart = 0;
            muLowPart = _udiv128(
                muHighPart, muLowPart, uDivisor, &uRemainder );
        }

        return *this;
    }

    uint64_t LowLimb() const { return muLowPart; }
    uint64_t HighLimb() const { return muHighPart; }

private:

    uint64_t muHighPart;
    uint64_t muLowPart;
};

class int128d_t
{

public:

    int128d_t( const uint64_t u = 0 )
    : muAbsoluteValue( 0, u )
    , mbNegative( false )
    {

    }

    int128d_t( const uint64_t uHigh, const uint64_t uLow )
    : muAbsoluteValue( uHigh, uLow )
    , mbNegative( false )
    {

    }

    int128d_t( const uint128d_t uValue )
    : muAbsoluteValue( uValue )
    , mbNegative( false )
    {

    }

    bool operator >( const int128d_t& xOther ) const
    {
        return ( mbNegative != xOther.mbNegative )
            ? xOther.mbNegative
            : ( mbNegative
                ? ( muAbsoluteValue > xOther.muAbsoluteValue )
                : ( xOther.muAbsoluteValue > muAbsoluteValue ) );
    }

    int128d_t operator -( const int128d_t& xOther ) const
    {
        int128d_t xResult = *this;
        if( xOther > * this )
        {
            xResult.muAbsoluteValue = xOther.muAbsoluteValue - muAbsoluteValue;
            xResult.mbNegative = true;
        }
        return xResult;
    }

    uint64_t LowLimb() const { return muAbsoluteValue.LowLimb(); }
    uint64_t HighLimb() const { return muAbsoluteValue.HighLimb(); }

private:

    uint128d_t muAbsoluteValue;
    bool mbNegative;
};

// this is based on something I believe to be 'Knuth's Algorithm D'
// .. finding good reference on the internet is difficult so the
// rough algorithm has been adapted to 128/64-bit arithmetic
Number AlgorithmD( const Number& xNumerator, const Number& xDenominator, Number& xRemainder )
{
    Number xQuotient = 0;
    xRemainder = 0;

    // 'normalise' the divisor and dividend so the high order bit is set on the divisor
    // 
    unsigned long uShifts = 0;
    _BitScanReverse64( &uShifts, xDenominator.MostSignificantLimb() );
    uShifts = 63ULL - uShifts;
    Number xDividend = xNumerator << uShifts;
    Number xDivisor = xDenominator << uShifts;
    Number xApproximationTest = 0;

    const uint64_t uM = xDividend.GetLimbCount();
    const uint64_t uN = xDivisor.GetLimbCount();

    // unconditionally add an extra limb for the  divisionloop to be safe.
    xDividend.AddZeroLeadingLimb();

    // 'school' division
    for( int iJ = static_cast< int >( uM - uN ); iJ >= 0; --iJ )
    {
        uint128d_t uDoubleLimb( xDividend.GetLimb( uN + iJ ), xDividend.GetLimb( uN + iJ - 1 ) );
        // note the top part can be any value, so the worst case large result has the high bits as:
        //   0xFFFFFFFFFFFFFFFF
        // the divisor being normalised is somewhere between values:
        //   0x8000000000000000-0xFFFFFFFFFFFFFFFF
        // this overflows a 128/64 -> 64 divisiom

        // the leading zero makes this 'safe' the first time in...
        // the top part is always zeroes.

        uint128d_t uApproximateRemainder = 0;
        uint64_t uMostSignificantLimb = xDivisor.MostSignificantLimb();
        // SE - NOTE: i feel this division can avoid the second div by careful
        // handling of the overflow case
        uint128d_t uApproximateQuotient =
            uDoubleLimb.Divide( uMostSignificantLimb, uApproximateRemainder.muLowPart );

        // SE - TOOD: this seems overly generic and amenable to careful construction
        
        // this loop fixes the cases where the quotient is overestimated,
        // including the overflow case, and adjusts our quotient digit and
        // remainder accordingly.
        while( ( uApproximateQuotient.HighLimb() > 0 )
            || ( uApproximateQuotient * xDivisor.GetLimb( uN - 2 )
                > uint128d_t( uApproximateRemainder.LowLimb(),
                    xDividend.GetLimb( iJ + uN - 2 ) ) ) )
        {
            uApproximateQuotient -= 1;
            uApproximateRemainder += uMostSignificantLimb;
            if( uApproximateRemainder.HighLimb() == 0 )
            {
                continue;
            }
        }

        // multiply to test if its right, noting the approximate quotient fits in 64-bits
        // ... but if the result is negative we need to be careful later.
        xApproximationTest = xDivisor * uApproximateQuotient.LowLimb();
        const bool bNegative = xApproximationTest > xDividend;

        // set the value of the quotient for this limb
        //xQuotient.SetLimb( iJ, uApproximateQuotient.LowLimb() );

        if( bNegative )
        {
            // if its negative adjust it back by one (assume the result is positive)
            // and adjust the approximation test value, then substract
            xQuotient.SetLimb( iJ, uApproximateQuotient.LowLimb() - 1 );
            xApproximationTest -= xDivisor;
            xDividend -= xApproximationTest;
        }
        else
        {
            // we got the guess right...
            xQuotient.SetLimb( iJ, uApproximateQuotient.LowLimb() );
            // subtract the test from the dividend and its done.
            xDividend -= xApproximationTest;
        }
    }

    return xQuotient;
}
