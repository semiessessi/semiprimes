#ifndef NUMBER_H
#define NUMBER_H

#include <cstdint>
#include <vector>

class Number
{

public:

    Number();
    Number( const Number& xNumber );
    Number( Number&& xNumber ) noexcept;

    Number& operator=( const Number& xNumber );
    Number& operator=( Number&& xNumber );

private:

    std::vector<int64_t> mxLimbs;
    bool mbNegative;
};

#endif
