#include "../Core/Parameters.h"
#include "../Core/ProcessNumber.h"
#include "../Number/Number.h"

#include <cstdio>

void InteractiveMode( const Parameters& xParameters )
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

        const Number xNumber( szBuffer );
        ProcessNumber( xNumber, xParameters );
    }

    puts( "Interactive session terminated." );
}
