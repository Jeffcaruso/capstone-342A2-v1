#include "largenum.h"
#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

// Your code goes here

// output number with a comma after ever 3 digits,
// e.g. 1234567890 -> 1,234,567,890
ostream &operator<<(ostream &out, const LargeNum &num) {
  if (num.backNum.empty()) {
    out << 0;
  }
  if (!num.isPositive) {
    out << "-";
  }
  for (int i = num.backNum.size() - 1; i > 0; i--) {
    out << num.backNum[i];
    if (i % 3 == 0) {
      out << ",";
    }
  }
  out << num.backNum[0];
  return out;
}

// default constructor from string
LargeNum::LargeNum(const string &str) {
  if (str[0] == '-') {
    isPositive = false;
  }
  for (int i = str.size() - 1; i >= 0; i--) {
    backNum.push_back(str[i]);
  }
  if (!isPositive) {
    backNum.pop_back();
  }
}

// constructor from int
LargeNum::LargeNum(int anInteger) {
  if (anInteger < 0) {
    isPositive = false;
  }
  string numStr = to_string(anInteger);

  for (int i = numStr.size() - 1; i >= 0; i--) {
    backNum.push_back(numStr[i]);
  }
  if (!isPositive) {
    backNum.pop_back();
  }
}

// returns true if the number is zero
bool LargeNum::isZero() const {
  LargeNum result = *this;
  for (int i = 0; i < result.backNum.size(); i++) {
    if (result.backNum[i] != '0') {
      return false;
    }
  }
  return true;
}

// negate the number, positive becomes negative, negative becomes positive
// Zero is always positive
LargeNum &LargeNum::negate() {
  LargeNum &result = *this;
  if (!isZero()) {
    result.isPositive = !result.isPositive;
  }
  return *this;
}

// add two numbers
LargeNum LargeNum::operator+(const LargeNum &rhs) const {
  // Initialize result with the left-hand operand
  LargeNum lhs = *this;
  int carry = 0;
  LargeNum biggerNum;
  LargeNum smallerNum;

  // checking each number's size
  if (rhs >= lhs) {
    biggerNum = LargeNum(rhs);
    smallerNum = LargeNum(lhs);
    biggerNum.isPositive = rhs.isPositive;
  } else {
    smallerNum = LargeNum(rhs);
    biggerNum = LargeNum(lhs);
    biggerNum.isPositive = lhs.isPositive;
  }
  if ((lhs.isPositive && !rhs.isPositive)) {
    LargeNum rrhs = LargeNum(rhs);
    rrhs = rrhs.negate();
    return (lhs - rrhs);
  }
  if ((!lhs.isPositive && rhs.isPositive)) {
    LargeNum llhs = LargeNum(lhs);
    llhs = llhs.negate();
    return (llhs - rhs).negate();
  }
  if (!lhs.isPositive && !rhs.isPositive) {
    LargeNum llhs = LargeNum(lhs);
    llhs = llhs.negate();
    LargeNum rrhs = LargeNum(rhs);
    rrhs = rrhs.negate();
    return (llhs + rrhs).negate();
  }

  for (int i = 0; i < biggerNum.backNum.size(); i++) {
    // Turns the char in i position into int digit1
    int digit1 = biggerNum.backNum[i] - '0';
    int sum;
    if (i >= smallerNum.backNum.size()) {
      sum = 0;
    } else {
      sum = smallerNum.backNum[i] - '0';
    }
    // adding the tens
    sum += carry;
    if (i < biggerNum.backNum.size()) {
      sum += digit1;
    }
    digit1 = sum % 10;
    carry = sum / 10;

    // Turning digit1 back to char and storing it in result
    biggerNum.backNum[i] = digit1 + '0';
  }
  if (carry != 0) {
    biggerNum.backNum.push_back(carry + '0');
    carry = 0;
  }
  if (biggerNum.isZero()) {
    biggerNum.backNum = "0";
  }
  return biggerNum;
}

// subtract two numbers
LargeNum LargeNum::operator-(const LargeNum &rhs) const {
  LargeNum lhs = *this;
  int takeOne = 0;
  LargeNum biggerNum;
  LargeNum smallerNum;

  // checking if rhs is negative
  if (lhs.isPositive && !rhs.isPositive) {
    LargeNum rrhs = LargeNum(rhs);
    rrhs = rrhs.negate();
    return (lhs + rrhs);
  }
  if (!lhs.isPositive && rhs.isPositive) {
    LargeNum llhs = LargeNum(lhs);
    llhs = llhs.negate();
    return (llhs + rhs).negate();
  }
  // checking each number's size
  if (lhs.isPositive && rhs.isPositive) {
    if (rhs >= lhs) {
      biggerNum = LargeNum(rhs);
      smallerNum = LargeNum(lhs);
      biggerNum.isPositive = false;
    } else {
      smallerNum = LargeNum(rhs);
      biggerNum = LargeNum(lhs);
      biggerNum.isPositive = lhs.isPositive;
    }
  }

  if (!lhs.isPositive && !rhs.isPositive) {
    if (rhs >= lhs) {
      biggerNum = LargeNum(lhs);
      smallerNum = LargeNum(rhs);
      biggerNum.isPositive = false;
    } else {
      smallerNum = LargeNum(lhs);
      biggerNum = LargeNum(rhs);
      biggerNum.isPositive = true;
    }
  }

  for (int i = 0; i < biggerNum.backNum.size(); i++) {
    // Turns the char in i position into int digit1
    int digit1 = biggerNum.backNum[i] - '0';
    int sub;
    if (i >= smallerNum.backNum.size()) {
      sub = 0;
    } else {
      sub = smallerNum.backNum[i] - '0';
    }

    // adding the tens
    digit1 += takeOne;
    takeOne = 0;
    // subtracting the 2 numbers
    if (digit1 < sub) {
      takeOne = -1;
      digit1 = digit1 + 10;
    }
    sub = digit1 - sub;

    // Turning digit1 back to char and storing it in result
    biggerNum.backNum[i] = sub + '0';
  }
  if (biggerNum.isZero()) {
    biggerNum.backNum = '0';
    biggerNum.isPositive = true;
  }
  for (int i = biggerNum.backNum.size() - 1; i >= 1; i--) {
    if (biggerNum.backNum[i] == '0') {
      biggerNum.backNum.pop_back();
    } else {
      break;
    }
  }
  return biggerNum;
}

// multiply two numbers
LargeNum LargeNum::operator*(const LargeNum &rhs) const {
  LargeNum lhs = *this;
  LargeNum result;
  LargeNum ltimes = LargeNum(lhs);
  ltimes.isPositive = true;
  LargeNum rrhs = LargeNum(rhs);
  LargeNum minusOne = LargeNum(1);
  if (lhs.isZero() || rhs.isZero()) {
    result.backNum = "0";
    return result;
  }
  while (!ltimes.isZero()) {
    result = result + rrhs;
    ltimes = ltimes - minusOne;
  }
  result.isPositive = !((lhs.isPositive && !rhs.isPositive) ||
                        (!lhs.isPositive && rhs.isPositive));
  return result;
}

// divide two numbers. rhs is the divisor
// similar to integer division, ignore remainder
LargeNum LargeNum::operator/(const LargeNum &rhs) const {
  LargeNum lhs = *this;
  LargeNum numbOne = LargeNum(1);
  LargeNum result = LargeNum(lhs);
  if (!result.isPositive) {
    result.negate();
  }
  LargeNum ltimes;
  LargeNum rrhs = LargeNum(rhs);
  if (!rrhs.isPositive) {
    rrhs.negate();
  }
  if (lhs.isZero() || (rhs.isZero()) ||
      ((lhs.isPositive && rhs.isPositive) && lhs < rhs)) {
    result.backNum = "0";
    return result;
  }
  while (result >= rrhs) {
    result = result - rrhs;
    ltimes = ltimes + numbOne;
  }
  ltimes.isPositive = !((lhs.isPositive && !rhs.isPositive) ||
                        (!lhs.isPositive && rhs.isPositive));

  return ltimes;
}

// return true if the numbers are equal
bool LargeNum::operator==(const LargeNum &rhs) const {
  LargeNum lhs = *this;
  if (lhs.backNum.size() != rhs.backNum.size() ||
      lhs.isPositive != rhs.isPositive) {
    return false;
  }
  for (int i = 0; i < rhs.backNum.size(); i++) {
    if (lhs.backNum[i] != rhs.backNum[i]) {
      return false;
    }
  }
  return true;
}

// return true if the numbers are not equal
// negating the result of operator==
bool LargeNum::operator!=(const LargeNum &rhs) const {
  LargeNum lhs = *this;
  return !(lhs == rhs);
}

// return true if the left-hand-side number is less than the
// right-hand-side number
bool LargeNum::operator<(const LargeNum &rhs) const {
  LargeNum lhs = *this;
  if ((lhs.backNum.size() < rhs.backNum.size()) ||
      (!lhs.isPositive && rhs.isPositive)) {
    return !(!lhs.isPositive && !rhs.isPositive);
  }
  if ((lhs.backNum.size() > rhs.backNum.size()) ||
      (lhs.isPositive && !rhs.isPositive)) {
    return !lhs.isPositive && !rhs.isPositive;
  }
  for (int i = rhs.backNum.size() - 1; i >= 0; i--) {
    if (lhs.backNum[i] < rhs.backNum[i]) {
      return !(!lhs.isPositive && !rhs.isPositive);
    }
    if (lhs.backNum[i] > rhs.backNum[i]) {
      return !lhs.isPositive && !rhs.isPositive;
    }
  }
  return false;
}

// return true if the left-hand-side number is greater than the
// right-hand-side number
bool LargeNum::operator>(const LargeNum &rhs) const {
  LargeNum lhs = *this;
  return !(lhs < rhs) && !(lhs == rhs);
}

// return true if the left-hand-side number is less than or equal to the
// right-hand-side number
bool LargeNum::operator<=(const LargeNum &rhs) const {
  LargeNum lhs = *this;
  return (lhs == rhs || lhs < rhs);
}

// return true if the left-hand-side number is greater than or equal to the
// right-hand-side number
bool LargeNum::operator>=(const LargeNum &rhs) const {
  LargeNum lhs = *this;
  return !(lhs < rhs);
}

// prefix increment
LargeNum &LargeNum::operator++() {
  LargeNum lhs = *this;
  LargeNum numbOne = LargeNum(1);
  lhs = lhs + numbOne;
  this->backNum = lhs.backNum;
  this->isPositive = lhs.isPositive;

  return *this;
}

// postfix increment
LargeNum LargeNum::operator++(int) {
  LargeNum copy(*this);
  ++(*this);

  return copy;
}

// prefix decrement
LargeNum &LargeNum::operator--() {
  LargeNum lhs = *this;
  LargeNum numbOne = LargeNum(1);
  lhs = lhs - numbOne;
  this->backNum = lhs.backNum;
  this->isPositive = lhs.isPositive;

  return *this;
}

// postfix decrement
LargeNum LargeNum::operator--(int) {
  LargeNum copy(*this);
  --(*this);

  return copy;
}