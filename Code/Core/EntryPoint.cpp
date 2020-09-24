#include "Parameters.h"

void Help();
void InteractiveMode( const bool bVerbose, const bool bTiming );

int main(
	const int iArgumentCount,
	const char* const* const pszArguments )
{
	const Parameters xParameters( iArgumentCount, pszArguments );
	if( xParameters.Help() )
	{
		Help();
		return 0;
	}

	if( xParameters.Interactive() )
	{
		InteractiveMode( xParameters.Verbose(), xParameters.Timing() );
		return 0;
	}

	// SE - TODO: do prime number thing to spare parameters
	return 0;
}
