#include "../Number/Factorisation.h"
#include "../Number/Number.h"
#include "../Algorithms/Factorisation/PollardPMinus1.h"

bool TestPMinus1()
{
    const Number xTest1 =
        10403z;

    Factorisation xResult = PollardPMinus1( xTest1 );

    return ( xResult.mxKnownFactors.size() == 2 )
        && ( xResult.mxKnownFactors[ 0 ].mxNumber == 0x67 )
        && ( xResult.mxKnownFactors[ 1 ].mxNumber == 0x65 );
}
