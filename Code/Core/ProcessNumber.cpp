#include "ProcessNumber.h"

#include "Parameters.h"
#include "Timing.h"
#include "../Algorithms/PowersOf2.h"
#include "../Algorithms/PowersOfN.h"
#include "../Algorithms/TrialDivision.h"
#include "../Algorithms/Wheel.h"
#include "../Number/Factorisation.h"
#include "../Number/Number.h"

#include <cstdio>

void ProcessNumber( const Number& xNumber, const Parameters& xParameters )
{
    printf( "Testing number %s...\n", xNumber.ToString().c_str() );

    if( xParameters.Timing() )
    {
        StartTiming( xParameters.Verbose() );
    }

    Factorisation xTest( xNumber );

    xTest.ContinueWithAlgorithm( PowersOf2 );
    xTest.ContinueWithAlgorithm( PowersOf< 3 > );
    xTest.ContinueWithAlgorithm( PowersOf< 5 > );
    xTest.ContinueWithAlgorithm( PowersOf< 7 > );
    xTest.ContinueWithAlgorithm( PowersOf< 11 > );
    xTest.ContinueWithAlgorithm( PowersOf< 13 > );
    xTest.ContinueWithAlgorithm( PowersOf< 17 > );
    xTest.ContinueWithAlgorithm( PowersOf< 19 > );
    xTest.ContinueWithAlgorithm( PowersOf< 23 > );
    xTest.ContinueWithAlgorithm( PowersOf< 29 > );
    xTest.ContinueWithAlgorithm( Wheel5 );

    if( xParameters.Timing() )
    {
        StopTiming();
    }

    xTest.Report();
}
