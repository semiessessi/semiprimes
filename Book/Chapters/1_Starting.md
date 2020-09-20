[TOC](../TOC.md)

# 1 - Starting

## 1.1 First Steps

The first step is to create a 'do-nothing' program, with suitable project files to build and run it, from which we can grow the rest of the project.

### 1.1.1 The null entrypoint program

```
int main( const int iArgumentCount, const char* const* const pszArguments )
{
	return 0;
}
```

### 1.1.2 Fleshing it out

To do anything useful we need to process numbers of arbitrary length as input and display them as output.

It is also helpful to allow parameters from the command line.

Something like this...

```
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
```

