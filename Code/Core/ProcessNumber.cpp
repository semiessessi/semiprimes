#include "ProcessNumber.h"

#include "Parameters.h"
#include "Timing.h"
#include "../Algorithms/PowersOf2.h"
#include "../Algorithms/PowersOfN.h"
#include "../Algorithms/SPRP.h"
#include "../Algorithms/TrialDivision.h"
#include "../Algorithms/Wheel.h"
#include "../Number/Factorisation.h"
#include "../Number/Number.h"

#include <cstdio>

namespace
{

template< int X, int N >
struct Helper
{
    static constexpr int i = iWheelPrimeCount - X;
    static constexpr int PreviousPrime =
        ( aiWheelPrimes[ i ] >= N )
            ? aiWheelPrimes[ i - 1 ]
            : Helper< X - 1, N >::PreviousPrime;

    static void ContinueFactorisation( Factorisation& xTest )
    {
        Helper< iWheelPrimeCount - 1, PreviousPrime >::ContinueFactorisation( xTest );
        //if( N <= 1 )
        //{
            // error
        //}
        xTest.ContinueWithAlgorithm( PowersOf< N > );
    }
};

template< int N >
struct Helper< 0, N >
{
    static constexpr int PreviousPrime = 1;

    static void ContinueFactorisation( Factorisation& xFactorisation )
    {

    }
};

template< int X >
struct Helper< X, 2 >
{
    static constexpr int PreviousPrime = 1;

    static void ContinueFactorisation( Factorisation& xFactorisation )
    {

    }
};

}

void ProcessNumber( const Number& xNumber, const Parameters& xParameters )
{
    if( ( xNumber.GetLimbCount() == 1 )
        && ( xNumber.LeastSignificantLimb() == 0 ) )
    {
        puts( "Cannot test zero.\n" );
        return;
    }

    printf( "Testing number %s...\n", xNumber.ToString().c_str() );

    if( xParameters.Timing() )
    {
        StartTiming( xParameters.Verbose() );
    }

    Factorisation xTest( xNumber );

    // remove any powers of 2 first.
    xTest.ContinueWithAlgorithm( PowersOf2 );

    // sprp tests to avoid expensive wheel stuff if possible
    xTest.ContinueWithAlgorithm( SPRPTests );

    // prepare for wheel
    Helper< iWheelPrimeCount - 1, ( 2 * 3 * 5 * 7 * 11 ) >::ContinueFactorisation( xTest );
    // do wheel
    xTest.ContinueWithAlgorithm( WheelUpTo< 11 > );

    if( xParameters.Timing() )
    {
        StopTiming();
    }

    xTest.Report();
}
