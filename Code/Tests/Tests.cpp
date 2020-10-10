#include "../Core/Parameters.h"
#include "../Core/Timing.h"

#include <cstdio>
#include <string>

bool RunTest( const std::string& xName, bool ( * const pfnTestFunction )() );

bool OnePlusOne()
{
    return ( 1z + 1z ) == 2;
}

bool OneMinusOne()
{
    return ( 1z - 1z ) == 0;
}

bool StringTests()
{
    const char* const szString =
        "111111111111111111111111111111111111111111111111111111111";
    const size_t uLength = strlen( szString );
    for( int i = 0; i < strlen( szString ); ++i )
    {
        if( Number( szString + i )
            != Number( Number( szString + i ).ToString() ) )
        {
            return false;
        }
    }

    return true;
}

bool ModTests();

void DoTests( const Parameters& xParameters )
{
    puts( "Running tests..." );
    static struct
    {
        std::string mxName;
        bool ( *mpfnTestFunction )();
    } lsaxTests[] =
    {
        // add tests here.
        { "1 + 1 == 2", OnePlusOne },
        { "1 - 1 == 0", OneMinusOne },
        { "Converting string of ones and back again", StringTests },
        { "(10^n - 1) / 9 mod 10 == 1 and similar", ModTests },
    };
    
    const size_t uTestCount = sizeof( lsaxTests ) / sizeof( lsaxTests[ 0 ] );
    bool bGood = true;
    for( size_t i = 0; i < uTestCount; ++i )
    {
        bGood = bGood && RunTest( lsaxTests[ i ].mxName, lsaxTests[ i ].mpfnTestFunction );
    }

    puts( bGood
        ? "All tests passed OK."
        : "Error: At least one test failed!" );
}

bool RunTest( const std::string& xName, bool ( * const pfnTestFunction )() )
{
    const bool bPass = pfnTestFunction();
    if( bPass == false )
    {
        printf( "Test failed: %s\n", xName.c_str() );
    }

    return bPass;
}
