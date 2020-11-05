#include "ProcessNumber.h"

#include "Parameters.h"
#include "Timing.h"
#include "../Algorithms/Factorisation/Fermat.h"
#include "../Algorithms/Factorisation/PollardPMinus1.h"
#include "../Algorithms/Factorisation/PollardRho.h"
#include "../Algorithms/Primality/PowersOf2.h"
#include "../Algorithms/Primality/PowersOfN.h"
#include "../Algorithms/Primality/SPRP.h"
#include "../Algorithms/Primality/TrialDivision.h"
#include "../Algorithms/Primality/Wheel.h"
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
    void SetWheelBound( const Number & xNumber );

    SetWheelBound( 0 );

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

    // sprp tests to identify composites
    xTest.ContinueWithAlgorithm( SPRPTests );

    // first pass fermat first, because its hard to find big factors that it can find (!)
    xTest.ContinueWithAlgorithm( Fermat );

    // remove any powers of 2 first.
    xTest.ContinueWithAlgorithm( PowersOf2 );

    // sprp tests to avoid expensive wheel stuff if possible
    xTest.ContinueWithAlgorithm( SPRPTests );

    // prepare for wheel
    Helper< iWheelPrimeCount - 1, ( 2 * 3 * 5 * 7 * 11 ) >::ContinueFactorisation( xTest );

    // do wheel
    xTest.ContinueWithAlgorithm( WheelUpTo< 11 > );

    xTest.ContinueWithAlgorithm( PollardPMinus1, true );

    // sprp tests to identify composites
    xTest.ContinueWithAlgorithm( SPRPTests );

    xTest.ContinueWithAlgorithm( PollardRho, true );

    // sprp tests to identify composites
    xTest.ContinueWithAlgorithm( SPRPTests );

    xTest.ContinueWithAlgorithm( Fermat, true );

    // sprp tests to identify composites
    xTest.ContinueWithAlgorithm( SPRPTests );

    if( xParameters.Timing() )
    {
        StopTiming();
    }

    xTest.Report( xParameters.Verbose() );
}
