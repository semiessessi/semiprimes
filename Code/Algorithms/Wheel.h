#ifndef WHEEL_H
#define WHEEL_H

#include <cstdint>

struct Factorisation;
class Number;

Factorisation Wheel3( const Number& xNumber );
Factorisation Wheel5( const Number& xNumber );
template< class N >
Factorisation WheelUpTo( const Number& xNumber );

#include "Wheel.inl"

#endif
