#include "Factorisation.h"

#include <cstdio>

Factorisation::Factorisation( const Number& xNumber, const bool bPrime )
: mxKnownFactors()
, mxNumber( xNumber )
, miPower( 1 )
, mbKnownPrime( bPrime )
, mbKnownComposite( false )
{
}

void Factorisation::Report( const bool bVerbose ) const
{
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
        puts( "Factorisation: " );
        if( bVerbose )
        {
            puts( "==========================" );
        }
        else
        {
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
                printf( " (%s)\n*\n", szType );
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
