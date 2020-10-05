#include "Parameters.h"

bool CheckFlag(
	const char* const szFlag,
	const int iArgumentCount,
	const char* const pszArgument )
{
	return ( _stricmp( pszArgument, szFlag ) == 0 );
}

Parameters::Parameters(
    const int iParameterCount,
    const char* const* const pszParameters )
{
	mxFlags[ "help" ] = false;
	mxFlags[ "timing" ] = false;
	mxFlags[ "verbose" ] = false;
	mxFlags[ "interactive" ] = false;
	mxFlags[ "test" ] = false;
    for( int i = 0; i < iParameterCount; ++i )
    {
		if( CheckFlag( "-v", iParameterCount, pszParameters[ i ] )
			|| CheckFlag( "-verbose", iParameterCount, pszParameters[ i ] ) )
		{
			mxFlags[ "verbose" ] = true;
		}
		else if( CheckFlag( "-t", iParameterCount, pszParameters[ i ] )
			|| CheckFlag( "-timing", iParameterCount, pszParameters[ i ] ) )
		{
			mxFlags[ "timing" ] = true;
		}
		else if( CheckFlag( "-h", iParameterCount, pszParameters[ i ] )
			|| CheckFlag( "/?", iParameterCount, pszParameters[ i ] )
			|| CheckFlag( "-help", iParameterCount, pszParameters[ i ] ) )
		{
			mxFlags[ "help" ] = true;
		}
		else if( CheckFlag( "-i", iParameterCount, pszParameters[ i ] )
			|| CheckFlag( "-interactive", iParameterCount, pszParameters[ i ] ) )
		{
			mxFlags[ "interactive" ] = true;
		}
		else if( CheckFlag( "-test", iParameterCount, pszParameters[ i ] ) )
		{
			mxFlags[ "test" ] = true;
		}
		else
		{
			// SE - TODO: fancier parameters, e.g. trial division limit
			mxNumbers.push_back( Number( std::string( pszParameters[ i ] ) ) );
		}
    }
}
