#include "largenum.h"
#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

// Your code goes here

// Note need to have the fn defs here for building to work properly, even if its otherwise bad...

// friend output stream
ostream &operator<<(ostream &out, const LargeNum &num)
{
    // TODO: insert return statement here
    return out;
}

// constructors
LargeNum::LargeNum(const string &str)
{
}

LargeNum::LargeNum(int anInteger)
{
}

// Large Num Functions

bool LargeNum::isZero() const
{
    return false;
}

LargeNum &LargeNum::negate()
{
    // TODO: insert return statement here
    return;
}

// overloaded # manipulation operators
// Add
LargeNum LargeNum::operator+(const LargeNum &rhs) const
{
    return LargeNum();
}

// subtract
LargeNum LargeNum::operator-(const LargeNum &rhs) const
{
    return LargeNum();
}

// multiply
LargeNum LargeNum::operator*(const LargeNum &rhs) const
{
    return LargeNum();
}

// divide
LargeNum LargeNum::operator/(const LargeNum &rhs) const
{
    return LargeNum();
}

// Overloaded comparison operators

// equals
bool LargeNum::operator==(const LargeNum &rhs) const
{
    return false;
}

// not equals
bool LargeNum::operator!=(const LargeNum &rhs) const
{
    return false;
}

// return true if the left-hand-side number is less than the
// right-hand-side number
bool LargeNum::operator<(const LargeNum &rhs) const
{
    return false;
}

// return true if the left-hand-side number is greater than the
// right-hand-side number
bool LargeNum::operator>(const LargeNum &rhs) const
{
    return false;
}

// return true if the left-hand-side number is less than or equal to the
// right-hand-side number
bool LargeNum::operator<=(const LargeNum &rhs) const
{
    return false;
}

// return true if the left-hand-side number is greater than or equal to the
// right-hand-side number
bool LargeNum::operator>=(const LargeNum &rhs) const
{
    return false;
}

// Increment / Dectement overloads
//  prefix increment
LargeNum &LargeNum::operator++()
{
    // TODO: insert return statement here
    return;
}

// postfix increment
LargeNum LargeNum::operator++(int)
{
    return LargeNum();
}

// prefix decrement
LargeNum &LargeNum::operator--()
{
    // TODO: insert return statement here
    return;
}

// postfix decrement
LargeNum LargeNum::operator--(int)
{
    return LargeNum();
}
