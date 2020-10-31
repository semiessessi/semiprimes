#include "Factorisation.h"

#include <algorithm>
#include <cstdio>

const char* const kszDefaultName = "";

void Tidy( Factorisation& xFactorisation )
{
    std::sort(
        xFactorisation.mxKnownFactors.begin(),
        xFactorisation.mxKnownFactors.end(),
        []( const Factorisation& xA, const Factorisation& xB ) -> bool { return xA.mxNumber < xB.mxNumber; } );
}

Factorisation::Factorisation( const Number& xNumber, const bool bPrime )
: mxKnownFactors()
, mxNumber( xNumber )
, szProofName( kszDefaultName )
, szFactoringAlgorithm( kszDefaultName )
, miPower( 1 )
, miFactoringTimeNS( 0 )
, miProofTimeNS( 0 )
, mbKnownPrime( bPrime )
, mbKnownComposite( false )
{
}

void Factorisation::Report( const bool bVerbose )
{
    Tidy( *this );

    const std::string xNumberString = mxNumber.ToString();
    if( mbKnownPrime && ( miPower == 1 ) )
    {
        printf( "%s is prime!\n", xNumberString.c_str() );
        return;
    }

    bool bComplete = true;
    if( mbKnownComposite )
    {
        printf( "%s is a composite\n", xNumberString.c_str() );
        if( bVerbose )
        {
            puts( "\n========================" );
            puts( "Details of factorisation" );
            puts( "========================\n" );
        }
        else
        {
            puts( "Factorisation: " );
            printf( " " );
        }

        for( size_t uFactor = 0; uFactor < mxKnownFactors.size(); ++uFactor )
        {
            if( mxKnownFactors[ uFactor ].miPower == 1 )
            {
                printf( "%s", mxKnownFactors[ uFactor ].mxNumber.ToString().c_str() );
            }
            else
            {
                printf( "%s^%d",
                    mxKnownFactors[ uFactor ].mxNumber.ToString().c_str(),
                    mxKnownFactors[ uFactor ].miPower );
            }

            if( bVerbose )
            {
                const char* const szType =
                    mxKnownFactors[ uFactor ].mbKnownComposite
                        ? "composite"
                        : ( mxKnownFactors[ uFactor ].mbKnownPrime
                            ? "prime"
                            : "unknown" );
                printf( " (%s", szType );
                if( mxKnownFactors[ uFactor ].mbKnownPrime
                    && ( mxKnownFactors[ uFactor ].szProofName[ 0 ] != 0 ) )
                {
                    printf( " - proven by %s", mxKnownFactors[ uFactor ].szProofName );
                }
                else if( mxKnownFactors[ uFactor ].mbKnownComposite
                    && ( mxKnownFactors[ uFactor ].szProofName[ 0 ] != 0 ) )
                {
                    printf( " - proven by %s", mxKnownFactors[ uFactor ].szProofName );
                }

                if( mxKnownFactors[ uFactor ].szFactoringAlgorithm[ 0 ] != 0 )
                {
                    printf( " - found using %s", mxKnownFactors[ uFactor ].szFactoringAlgorithm );
                }

                printf( ")\n%s\n", ( uFactor != ( mxKnownFactors.size() - 1 ) )
                        ? "*"
                        : "" );
            }
            else
            {

                if( mxKnownFactors[ uFactor ].mbKnownComposite )
                {
                    printf( "(C)" );
                }

                if( !mxKnownFactors[ uFactor ].mbKnownComposite && !mxKnownFactors[ uFactor ].mbKnownPrime )
                {
                    printf( "(?)" );
                    bComplete = false;
                }

                if( uFactor != ( mxKnownFactors.size() - 1 ) )
                {
                    printf( " * " );
                }
            }
        }

        puts( "" );

        if( bComplete == false )
        {
            puts( "NOTE: TESTS WERE NOT COMPLETED" );
        }

        return;
    }

    if( !mbKnownPrime && !mbKnownComposite )
    {
        printf( "Could not determine if %s was prime or not!\n", xNumberString.c_str() );
    }
}
