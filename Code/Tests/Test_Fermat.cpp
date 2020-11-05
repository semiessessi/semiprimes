#include "../Number/Factorisation.h"
#include "../Number/Number.h"
#include "../Algorithms/Factorisation/Fermat.h"

bool TestFermat()
{
    const Number xTest1 =
        10403z;

    Factorisation xResult = Fermat( xTest1 );
    if( ( xResult.mxKnownFactors.size() != 2 )
        || ( xResult.mxKnownFactors[ 0 ].mxNumber != 0x65 )
        || ( xResult.mxKnownFactors[ 1 ].mxNumber != 0x67 ) )
    {
        return false;
    }

    return true;
}
