#ifndef REPEATED_MOD_H
#define REPEATED_MOD_H

class Number;

inline Number GeneralisedReciprocal( const Number& xNumber );
inline Number RepeatedMod( const Number& xNumber, const Number& xReciprocal, const Number& xModulus );

#include "RepeatedMod.inl"

#endif
