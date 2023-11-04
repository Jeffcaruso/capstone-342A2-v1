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
    //intentionally wrong def
    Num = "1";
}

LargeNum::LargeNum(int anInteger)
{
    //intentionally wrong def
    Num = "1";
}

// Large Num Functions

bool LargeNum::isZero() const
{
    return false;
}

LargeNum &LargeNum::negate()
{
    //intentionally wrong def
    LargeNum ln = LargeNum(1);
    return ln;
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
    //intentionally wrong def
    LargeNum ln = LargeNum(1);
    return ln;
}

// postfix increment
LargeNum LargeNum::operator++(int)
{
    //intentionally wrong def
    LargeNum ln = LargeNum(1);
    return ln;
}

// prefix decrement
LargeNum &LargeNum::operator--()
{
    //intentionally wrong def
    LargeNum ln = LargeNum(1);
    return ln;
}

// postfix decrement
LargeNum LargeNum::operator--(int)
{
    //intentionally wrong def
    LargeNum ln = LargeNum(1);
    return ln;
}
