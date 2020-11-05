#include "../Number/Factorisation.h"
#include "../Number/Number.h"
#include "../Algorithms/Factorisation/PollardRho.h"

bool TestRho()
{
    const Number xTest1 =
        10403z;

    Factorisation xResult = PollardRho( xTest1 );

    return ( xResult.mxKnownFactors.size() == 2 )
        && ( xResult.mxKnownFactors[ 0 ].mxNumber == 0x67 )
        && ( xResult.mxKnownFactors[ 1 ].mxNumber == 0x65 );
}
