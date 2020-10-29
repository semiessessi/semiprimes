#include "../../Number/Number.h"

Number GCD_Euclidean( const Number& xA, const Number& xB )
{
	Number xP = xA;
	Number xQ = xB;
	Number xTemp;
	while( xQ > 0 )
	{
		xTemp = xQ;
		xQ = xP % xQ;
		xP = xQ;
	}

	return xP;
}
