#include <cstdio>
#include <cstring>

void InteractiveMode( const bool bVerbose, const bool bTiming );

bool CheckFlag(
	const char* const szFlag,
	const int iArgumentCount,
	const char* const* const pszArguments )
{
	for( int i = 0; i < iArgumentCount; ++i )
	{
		if( _stricmp( pszArguments[ 1 ], szFlag ) == 0 )
		{
			return true;
		}
	}

	return false;
}

int main(
	const int iArgumentCount,
	const char* const* const pszArguments )
{
	bool bVerbose = false;
	bool bTiming = false;
	if( CheckFlag( "-v", iArgumentCount, pszArguments )
		|| CheckFlag( "-verbose", iArgumentCount, pszArguments ) )
	{
		bVerbose = true;
	}

	if( CheckFlag( "-t", iArgumentCount, pszArguments )
		|| CheckFlag( "-timing", iArgumentCount, pszArguments ) )
	{
		bTiming = true;
	}

	if( CheckFlag( "-i", iArgumentCount, pszArguments )
		|| CheckFlag( "-interactive", iArgumentCount, pszArguments ) )
	{
		InteractiveMode( bVerbose, bTiming );
		return 0;
	}

	// SE - TODO: do prime number thing to spare parameters
	return 0;
}
