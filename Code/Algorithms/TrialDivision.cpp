#include "TrialDivision.h"

#include "../Number/Factorisation.h"
#include "../Number/Number.h"

static const uint64_t uTrialDivisionCutoff = 100000;

Factorisation TrialDivision( const Number& xNumber )
{
    Number xWorkingValue = xNumber;
    Factorisation xResult( xNumber );
    uint64_t uTest = 3;
    while( xWorkingValue > ( ( uTest * uTest ) - 1 ) )
    {
        if( ( xWorkingValue % uTest ) == 0 )
        {
            xResult.mbKnownComposite = true;
            Factorisation xNew( uTest, true );
            xNew.miPower = 0;
            while( ( xWorkingValue % uTest ) == 0 )
            {
                ++xNew.miPower;
                xWorkingValue /= uTest;
            }
            xResult.mxKnownFactors.push_back( xNew );
        }

        uTest += 2;

        if( uTest > uTrialDivisionCutoff )
        {
            xResult.mxKnownFactors.push_back( Factorisation( xWorkingValue ) );
            return xResult;
        }
    }

    if( xResult.mxKnownFactors.empty() )
    {
        xResult.mbKnownPrime = true;
    }
    else if( xWorkingValue > 1 )
    {
        xResult.mxKnownFactors.push_back( Factorisation( xWorkingValue, true ) );
    }

    return xResult;
}
