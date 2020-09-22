#ifndef NUMBER_H
#define NUMBER_H

#include <cstdint>
#include <string>
#include <vector>

class Number
{

public:

    Number();
    Number( const std::string& xString );
    Number( const Number& xNumber );
    Number( Number&& xNumber ) noexcept;

    Number& operator=( const Number& xNumber );
    Number& operator=( Number&& xNumber ) noexcept;
    
    std::string ToString() const;

private:

    std::vector<int64_t> mxLimbs;
    bool mbNegative;
};

#pragma warning( disable : 4455 )
Number operator ""z( const char* const szToken );
#pragma warning( default : 4455 )

#endif
