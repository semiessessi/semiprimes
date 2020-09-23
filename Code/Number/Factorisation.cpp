#include "Factorisation.h"

Factorisation::Factorisation( const Number& xNumber )
: mxKnownFactors()
, mxNumber( xNumber )
, mbKnownPrime( false )
, mbKnownComposite( false )
{
}
