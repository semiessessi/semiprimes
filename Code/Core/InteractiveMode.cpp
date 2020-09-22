
#include <cstdio>

void InteractiveMode( const bool bVerbose, const bool bTiming )
{
    // SE - TODO: endless buffer, obvs.
    static char szBuffer[ 4096 ];
    while( true )
    {
        putchar( ':' );
        gets_s( szBuffer );
        // allow to quit
        if( szBuffer[ 0 ] == 'q' )
        {
            return;
        }
    }
}
