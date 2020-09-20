#include <cstdio>
#include <cstring>

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
	if( CheckFlag( "-v", iArgumentCount, pszArguments )
		|| CheckFlag( "-verbose", iArgumentCount, pszArguments ) )
	{
		// SE - TODO: set verbosity enabled
	}

	if( CheckFlag( "-t", iArgumentCount, pszArguments )
		|| CheckFlag( "-timing", iArgumentCount, pszArguments ) )
	{
		// SE - TODO: set timing enabled
	}

	if( CheckFlag( "-1", iArgumentCount, pszArguments )
		|| CheckFlag( "-interactive", iArgumentCount, pszArguments ) )
	{
		// SE - TODO: run interactive mode
	}

	// SE - TODO: do prime number thing to spare parameters
	return 0;
}
