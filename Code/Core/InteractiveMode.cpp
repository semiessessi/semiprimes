
#include <cstdio>

#include "../Number/Number.h"

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
        puts( "TODO: some testing!" );
    }
}
