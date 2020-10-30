#include "../Number/Factorisation.h"
#include "../Number/Number.h"
#include "../Algorithms/Factorisation/PollardRho.h"

bool TestRho()
{
    const Number xTest1 =
        10403z;

    Factorisation xResult = PollardRho( xTest1 );

    return true;
}
