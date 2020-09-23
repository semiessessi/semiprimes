
#include <cstdio>

#include "../Number/Factorisation.h"
#include "../Number/Number.h"
#include "../Algorithms/PowersOf2.h"

void InteractiveMode( const bool bVerbose, const bool bTiming )
{
    puts( "Semiprimes Interactive Mode - Enter a number, or q to quit." );

    // SE - TODO: endless buffer, obvs.
    static char szBuffer[ 4096 ];
    while( true )
    {
        putchar( ':' );
        gets_s( szBuffer );
        // allow to quit
        if( ( szBuffer[ 0 ] == 'q' )
            || ( szBuffer[ 0 ] == 'Q' ) )
        {
            return;
        }

        Number xNumber( szBuffer );
        printf( "Testing number %s...\n", xNumber.ToString().c_str() );
        
        Factorisation xTest = PowersOf2( xNumber );
        xTest.Report();
    }

    puts( "Interactive session terminated." );
}
