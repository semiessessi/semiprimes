#ifndef POWERS_OF_N_H
#define POWERS_OF_N_H

struct Factorisation;
class Number;

template< int N >
Factorisation PowersOf( const Number& xNumber );

#include "PowersOfN.inl"

#endif
