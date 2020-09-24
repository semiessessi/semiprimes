#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "../Number/Number.h"

#include <string>
#include <unordered_map>

class Parameters
{

public:

    Parameters(
        const int iParameterCount,
        const char* const* const pszParameters );

    bool Help() const { return mxFlags.at( "help" ); }
    bool Timing() const { return mxFlags.at( "timing" ); }
    bool Verbose() const { return mxFlags.at( "verbose" ); }
    bool Interactive() const { return mxFlags.at( "interactive" ); }

    int NumberCount() const { return static_cast< int >( mxNumbers.size() ); }
    const Number& GetNumber( const int iNumber ) const { return mxNumbers[ iNumber ]; }

private:

    std::unordered_map<std::string, Number> mxNumberParameters;
    std::unordered_map<std::string, bool> mxFlags;
    std::vector< Number > mxNumbers;

};

#endif
