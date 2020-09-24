#include "Parameters.h"
#include "ProcessNumber.h"

void Help();
void InteractiveMode( const Parameters& xParameters );

int main(
	const int iArgumentCount,
	const char* const* const pszArguments )
{
	const Parameters xParameters( iArgumentCount - 1, pszArguments + 1 );
	if( xParameters.Help() )
	{
		Help();
		return 0;
	}

	for( int i = 0; i < xParameters.NumberCount(); ++i )
	{
		ProcessNumber( xParameters.GetNumber( i ), xParameters );
	}

	if( xParameters.Interactive() )
	{
		InteractiveMode( xParameters );
		return 0;
	}
}
