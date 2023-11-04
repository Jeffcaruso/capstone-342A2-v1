#include "largenum.h"
#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

// output number with a comma after ever 3 digits,
// e.g. 1234567890 -> 1,234,567,890
ostream &operator<<(ostream &out, const LargeNum &num) {
  if (num.isZero()) {
    out << "0";
    return out;
  }
  if (!num.isPositive) {
    out << "-";
  }
  for (int i = num.size() - 1; i >= 0; i--) {
    out << num.num[i];
    if (i > 0 && i % 3 == 0) {
      out << ",";
    }
  }
  return out;
}

// default constructor from string
LargeNum::LargeNum(const string &str) {

  vector<char> vec(str.rbegin(), str.rend());
  for (char input : vec) {
    if (input == '-') {
      isPositive = false;
      break;
    }
    num.push_back(input);
  }
}

// constructor from int
LargeNum::LargeNum(int anInteger) {
  if (anInteger < 0) {
    isPositive = false;
    anInteger *= -1;
  }
  while (anInteger > 0) {
    num.push_back((anInteger % 10) + '0');
    anInteger /= 10;
  }
}

// returns size
int LargeNum::size() const { return num.size(); }

// returns true if the number is zero
bool LargeNum::isZero() const {
  for (int i = 0; i < num.size(); i++) {
    if (num[i] != '0') {
      return false;
    }
  }
  return true;
}

// negate the number, positive becomes negative, negative becomes positive
// Zero is always positive
LargeNum &LargeNum::negate() {
  isPositive = !isPositive;
  return *this;
}

// add two numbers
LargeNum LargeNum::operator+(const LargeNum &rhs) const {
  LargeNum result;
  LargeNum tempLhs(*this);
  LargeNum tempRhs(rhs);
  if (!isPositive && !rhs.isPositive) {
    tempRhs.negate();
    tempLhs.negate();
    result = tempLhs + tempRhs;
    result.negate();
    return result;
  }
  if (!isPositive || !rhs.isPositive) {
    if (rhs.isPositive) {
      tempLhs.negate();
    } else {
      tempRhs.negate();
    }
    result = tempLhs - tempRhs;
    result.negate();
    return result;
  }
  result = *this;
  int largeSize;
  int smallSize;
  int carry = 0;
  int tot;
  int index;
  smallSize = (rhs.size() > size()) ? size() : rhs.size();
  largeSize = (rhs.size() < size()) ? size() : rhs.size();
  for (index = 0; index < smallSize; index++) {
    if (carry == 1) {
      tot = (num[index] - '0') + (rhs.num[index] - '0') + 1;
      carry = 0;
    } else {
      tot = (num[index] - '0') + (rhs.num[index] - '0');
    }
    if (tot > 9) {
      tot -= 10;
      carry = 1;
    }
    result.num[index] = tot + '0';
  }
  if (smallSize == num.size()) {
    while (smallSize < largeSize) {
      int tot = (carry == 1) ? (rhs.num[smallSize++] - '0') + 1
                             : (rhs.num[smallSize++] - '0');
      result.num.push_back(tot + '0');
      carry = 0;
    }
  }
  if (carry == 1) {
    if (index == largeSize) {
      result.num.push_back(1 + '0');
    } else {
      tot = (num[index] - '0') + 1;
      result.num[index] = tot + '0';
    }
    carry = 0;
  }
  return result;
}

// subtract two numbers
LargeNum LargeNum::operator-(const LargeNum &rhs) const {
  LargeNum result;
  LargeNum tempLhs(*this);
  LargeNum tempRhs(rhs);
  if (!isPositive && !rhs.isPositive) {
    tempLhs.negate();
    tempRhs.negate();
    result = tempRhs - tempLhs;
    return result;
  }
  if (!isPositive || !rhs.isPositive) {
    if (rhs.isPositive) {
      tempLhs.negate();
    } else {
      tempRhs.negate();
    }
    result = tempRhs + tempLhs;
    result.negate();
    return result;
  }
  if (*this == rhs) {
    return LargeNum(0);
  }
  if (rhs > *this) {
    result = rhs - *this;
    result.negate();
    return result;
  }
  result = *this;
  int largeSize;
  int smallSize;
  int borrowed = 0;
  int tot;
  int index;
  smallSize = (rhs.size() > size()) ? size() : rhs.size();
  largeSize = (rhs.size() < size()) ? size() : rhs.size();
  for (index = 0; index < largeSize; index++) {
    if (borrowed == 1) {
      if (smallSize <= index && smallSize == rhs.size()) {
        tot = (num[index] - '0') - 1;
      } else if (smallSize <= index && smallSize == size()) {
        tot = (rhs.num[index] - '0') - 1;
      } else {
        tot = (num[index] - '0') - (rhs.num[index] - '0') - 1;
      }
      borrowed = 0;
    } else {
      if (smallSize <= index && smallSize == rhs.size()) {
        tot = (num[index] - '0');
      } else if (smallSize <= index && smallSize == size()) {
        tot = (rhs.num[index] - '0');
      } else {
        tot = (num[index] - '0') - (rhs.num[index] - '0');
      }
    }
    if (tot < 0) {
      tot += 10;
      borrowed = 1;
    }
    if ((index == largeSize - 1) && tot == 0) {
      result.num.pop_back();
    } else {
      result.num[index] = tot + '0';
    }
  }
  while (borrowed >= 1) {
    tot = (num[index] - '0') - 1;
    if ((index == largeSize - 1) && tot == 0) {
      result.num.pop_back();
    } else {
      tot = (num[index] - '0') - 1;
      result.num[index] = tot + '0';
    }
    borrowed--;
  }
  return result;
}

// multiply two numbers
LargeNum LargeNum::operator*(const LargeNum &rhs) const {
  LargeNum result;
  LargeNum rhsTemp = rhs;
  LargeNum lhsTemp = *this;
  LargeNum zero(0);
  if (!rhs.isPositive && !isPositive) {
    rhsTemp.negate();
    lhsTemp.negate();
    result = lhsTemp * rhsTemp;
    return result;
  }
  if (!rhs.isPositive || !isPositive) {
    if (rhs.isPositive) {
      lhsTemp.negate();
    } else {
      rhsTemp.negate();
    }
    result = lhsTemp * rhsTemp;
    result.negate();
    return result;
  }
  if (rhs.isZero()) {
    return zero;
  }
  while (rhsTemp > zero) {
    result = result + lhsTemp;
    rhsTemp--;
  }
  return result;
}

// divide two numbers. rhs is the divisor
// similar to integer division, ignore remainder
LargeNum LargeNum::operator/(const LargeNum &rhs) const {
  LargeNum result;
  LargeNum rhsTemp = rhs;
  LargeNum lhsTemp = *this;
  LargeNum zero(0);
  if (!rhs.isPositive && !result.isPositive) {
    rhsTemp.negate();
    lhsTemp.negate();
    result = lhsTemp / rhsTemp;
    return result;
  }
  if (!rhs.isPositive || !isPositive) {
    if (rhs.isPositive) {
      lhsTemp.negate();
    } else {
      rhsTemp.negate();
    }
    result = lhsTemp / rhsTemp;
    result.negate();
    return result;
  }
  if (lhsTemp < rhsTemp) {
    return zero;
  }
  while (lhsTemp > zero) {
    lhsTemp = lhsTemp - rhsTemp;
    result++;
    if (lhsTemp < rhsTemp) {
      break;
    }
  }
  return result;
}

// return true if the numbers are equal
bool LargeNum::operator==(const LargeNum &rhs) const {
  if (isZero() && rhs.isZero()) {
    return true;
  }
  if (num.size() != rhs.num.size()) {
    return false;
  }
  for (int i = 0; i < num.size(); i++) {
    if (num[i] != rhs.num[i]) {
      return false;
    }
  }
  return true;
}

// return true if the numbers are not equal
bool LargeNum::operator!=(const LargeNum &rhs) const {
  return (!(num == rhs.num));
  return false;
}

// return true if the left-hand-side number is less than the
// right-hand-side number
bool LargeNum::operator<(const LargeNum &rhs) const {
  if (!isPositive && !rhs.isPositive) {
    LargeNum tempLhs;
    LargeNum tempRhs;
    tempLhs = LargeNum(*this);
    tempRhs = LargeNum(rhs);
    tempLhs.negate();
    tempRhs.negate();
    return (tempLhs > tempRhs);
    // create new largenum and negate
  }
  if (num.size() < rhs.num.size()) {
    return true;
  }
  if (num.size() > rhs.num.size()) {
    return false;
  }
  for (int i = size() - 1; i >= 0; i--) {
    if (num[i] < rhs.num[i]) {
      return true;
    }
  }
  return false;
}

// return true if the left-hand-side number is greater than the
// right-hand-side number
bool LargeNum::operator>(const LargeNum &rhs) const {
  if (!isPositive && !rhs.isPositive) {
    LargeNum tempLhs;
    LargeNum tempRhs;
    tempLhs = LargeNum(*this);
    tempRhs = LargeNum(rhs);
    tempLhs.negate();
    tempRhs.negate();
    return (tempLhs < tempRhs);
  }
  if (num.size() > rhs.num.size()) {
    return true;
  }
  if (num.size() < rhs.num.size()) {
    return false;
  }
  for (int i = size() - 1; i >= 0; i--) {
    if (num[i] > rhs.num[i]) {
      return true;
    }
  }
  return false;
}

// return true if the left-hand-side number is less than or equal to the
// right-hand-side number
bool LargeNum::operator<=(const LargeNum &rhs) const {
  if (num < rhs.num) {
    return true;
  }
  if (num == rhs.num) {
    return true;
  }
  return false;
}

// return true if the left-hand-side number is greater than or equal to the
// right-hand-side number
bool LargeNum::operator>=(const LargeNum &rhs) const {
  if (num > rhs.num) {
    return true;
  }
  if (num == rhs.num) {
    return true;
  }
  return false;
}

// prefix increment
LargeNum &LargeNum::operator++() {
  LargeNum one(1);
  *this = *this + one;
  return *this;
}

// postfix increment
LargeNum LargeNum::operator++(int) {
  LargeNum temp(*this);
  LargeNum one(1);
  *this = *this + one;
  return temp;
}

// prefix decrement
LargeNum &LargeNum::operator--() {
  LargeNum one(1);
  *this = *this - one;
  return *this;
}

// postfix decrement
LargeNum LargeNum::operator--(int) {
  LargeNum temp(*this);
  LargeNum one(1);
  *this = *this - one;
  return temp;
}
