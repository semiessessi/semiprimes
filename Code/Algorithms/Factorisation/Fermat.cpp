
#include "../../Number/Factorisation.h"
#include "../../Number/Number.h"

Number GetWheelBound();

static const int kiFermatTestLimit =
#if _DEBUG
    50000
#else
    2500000
#endif
;

Factorisation Fermat( const Number& xNumber )
{
    Factorisation xResult( xNumber );

    Number xRemainder = 0;
    Number xFinalRemainder = 0;
    Number xTest = xNumber.SquareRoot( xRemainder );
    if( xRemainder == 0 )
    {
        const bool bWheelPrime = xTest < GetWheelBound();
        Factorisation xNew( xTest, bWheelPrime );
        xNew.szFactoringAlgorithm = "perfect square test";
        if( bWheelPrime )
        {
            xNew.szProofName = "bound set by trial division";
        }
        xNew.miPower = 2;
        xResult.mxKnownFactors.push_back( xNew );

        return xResult;
    }

    ++xTest;
    xRemainder = xTest * xTest - xNumber;

    for( int i = 0; i < kiFermatTestLimit; ++i )
    {
        do
        {
            // perfect square checks by modulo arithmetic
            uint64_t uTest = xRemainder & 0x15;// 0x63;
            if( ( /*( uTest == 49 ) || ( uTest < 57 )                                // & 63
                || ( uTest == 33 ) || ( uTest == 36 ) || ( uTest < 41 )
                || ( uTest == 16 ) || ( uTest == 17 ) || ( uTest < 25 )
                || */( uTest == 4 ) || ( uTest == 9 ) || ( uTest < 2 ) ) == false )  // & 15
            {
                break;
            }

            const Number xSquareRoot = xRemainder.SquareRoot( xFinalRemainder );
            if( xFinalRemainder == 0 )
            {
                const bool bWheelPrime = ( xTest - xSquareRoot ) < GetWheelBound();
                Factorisation xNew( xTest - xSquareRoot, bWheelPrime );
                xNew.szFactoringAlgorithm = "Fermat's method";
                if( bWheelPrime )
                {
                    xNew.szProofName = "bound set by trial division";
                }
                xResult.mxKnownFactors.push_back( xNew );
                const bool bSecondWheelPrime = ( xTest + xSquareRoot ) < GetWheelBound();
                xNew.mxNumber = xTest + xSquareRoot;
                xNew.mbKnownPrime = bSecondWheelPrime;
                if( !bWheelPrime )
                {
                    xNew.szProofName = "";
                }
                xResult.mxKnownFactors.push_back( xNew );

                return xResult;
            }
        } while( false );

        // iterate
        xRemainder += ( xTest << 1 );
        ++xRemainder;
        ++xTest;
        //xRemainder = xTest * xTest - xNumber;
    }

    return xResult;
}
