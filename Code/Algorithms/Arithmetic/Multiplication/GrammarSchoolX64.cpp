#include <vector>

#include "MultiplyLimbX64.h"
#include "../AdditionX64.h"

void MultiplyX64_GrammarSchool(
    std::vector< uint64_t >& xLimbs,
    const std::vector< uint64_t >& xOperandLimbs )
{
    const size_t uInitialLimbCount = xLimbs.size();
    const size_t uNewLimbCount = uInitialLimbCount + xOperandLimbs.size();
    static std::vector< uint64_t > xLimbsCopy;
    static std::vector< uint64_t > xOperandCopy;
    xLimbsCopy = xLimbs;

    xLimbs.resize( uNewLimbCount );
    for( size_t i = 0; i < uNewLimbCount; ++i )
    {
        xLimbs[ i ] = 0;
    }

    for( size_t i = 0; i < uInitialLimbCount; ++i )
    {
        // base case multiply, add the result after shifting based on our place
        xOperandCopy = xOperandLimbs;
        MultiplyX64_BaseCase( xOperandCopy, xLimbsCopy[ i ] );
        xOperandCopy.insert( xOperandCopy.begin(), i, 0 );
        AddX64_Generic( xLimbs, xOperandCopy );
    }

    while( xLimbs.back() == 0 )
    {
        xLimbs.pop_back();
    }
}
