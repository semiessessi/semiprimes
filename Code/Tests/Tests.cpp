#include "../Core/Parameters.h"
#include "../Core/Timing.h"

#include <cstdio>
#include <string>

bool SimpleAddCarryTest();
bool BigAddCarryTest();
bool BigSubBorrowTest();
bool SpecificSubTest();
bool ModTests();
bool MulTests();
bool LeftShiftTests();
bool RightShiftTests();
bool TestSquareRoot();
bool ModExpTests();
bool TestFermat();
bool TestRho();
bool SPRPTests();
bool AlgorithmDTests();

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
        { "converting string of ones and back again", StringTests },
        { "carry for base case addition", SimpleAddCarryTest },
        { "carry for mutliple limb addition", BigAddCarryTest },
        { "borrow for subtraction", BigSubBorrowTest },
        { "one highly specific subtraction", SpecificSubTest },
        { "multiple limb left shifts", LeftShiftTests },
        { "multiple limb right shifts", RightShiftTests },
        { "multiple limb multiplication", MulTests },
        { "(10^n - 1) / 9 mod 10 == 1 and similar", ModTests },
        { "Algorithm D tests", AlgorithmDTests },
        { "Square root tests", TestSquareRoot },
        { "Modular exponentiation tests", ModExpTests },
        { "Pollard rho algorithm tests", TestRho },
        { "Fermat's method tests", TestFermat },
        { "Strong Fermat psuedoprime tests", SPRPTests },
    };
    
    const size_t uTestCount = sizeof( lsaxTests ) / sizeof( lsaxTests[ 0 ] );
    bool bGood = true;
    for( size_t i = 0; i < uTestCount; ++i )
    {
        if( RunTest( lsaxTests[ i ].mxName, lsaxTests[ i ].mpfnTestFunction ) == false )
        {
            bGood = false;
        }
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
