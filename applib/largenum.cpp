#include "largenum.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

// constructor for LargeNum, constructs from string
LargeNum::LargeNum(const string &str) {

  for (int i = str.size() - 1; i >= 0; i--) {
    largeNum.push_back(str[i]);
  }
  if (largeNum[largeNum.size() - 1] == '-') {
    isPositive = false;
    largeNum.pop_back();
  }
}

// constructor from int
LargeNum::LargeNum(int anInteger) : LargeNum(to_string(anInteger)) {}

// returns true if the number is zero
bool LargeNum::isZero() const { return largeNum[0] == '0'; }

// negate the number, positive becomes negative, negative becomes positive
// Zero is always positive
LargeNum &LargeNum::negate() {
  isPositive = !isPositive;
  if (isZero()) {
    isPositive = true;
  }
  return *this;
}

// add two numbers
LargeNum LargeNum::operator+(const LargeNum &rhs) const {
  string temp;
  int carry = 0;

  if (*this < rhs) {
    LargeNum copy = rhs + *this;
    return copy;
  }
  if (!isPositive && rhs.isPositive) {
    LargeNum copy = *this;
    copy.negate();
    return rhs - copy;
  }
  if (isPositive && !rhs.isPositive) {
    LargeNum copy = rhs;
    copy.negate(); // now is positive
    return *this - copy;
  }
  if (!isPositive && !rhs.isPositive) {
    LargeNum thisCopy;
    return (LargeNum(*this).negate() + LargeNum(rhs).negate()).negate();
  }

  for (int i = 0; i < largeNum.size(); i++) {
    int first = i < largeNum.size() ? (largeNum[i] - '0') : 0;
    int second = i < rhs.largeNum.size() ? (rhs.largeNum[i] - '0') : 0;
    int sum = carry + first + second;
    if (sum < 10) {
      carry = 0;
    } else {
      carry = 1;
      sum = sum - 10;
    }

    temp.push_back(sum + '0');
  }

  if (carry == 1) {
    temp.push_back(1 + '0');
  }
  LargeNum largenumsum;
  largenumsum.largeNum = temp;
  return largenumsum;
}

// subtract two numbers by finding the smaller num and subtract
LargeNum LargeNum::operator-(const LargeNum &rhs) const {
  string temp;
  int carry = 0;
  int sub;

  if (*this < rhs) {
    LargeNum copy = rhs - *this;
    copy.negate();
    return copy;
  }

  if (isPositive && !rhs.isPositive) {
    LargeNum copy = rhs;
    copy.negate();
    return *this + copy;
  }

  for (int i = 0; i < largeNum.size(); i++) {
    int first = i < largeNum.size() ? (largeNum[i] - '0') : 0;
    int second = i < rhs.largeNum.size() ? (rhs.largeNum[i] - '0') : 0;
    sub = first - second - carry;

    if (sub < 0) {
      sub = sub + 10;
      carry = 1;
    } else {
      carry = 0;
    }

    temp.push_back(sub + '0');
  }
  temp = removeLeadingZeros(temp);
  LargeNum largenumsub;
  largenumsub.largeNum = temp;

  return largenumsub;
}

// multiply two numbers
LargeNum LargeNum::operator*(const LargeNum &rhs) const {
  if (*this == LargeNum(0) || rhs == LargeNum(0)) {
    return LargeNum(0);
  }
  if ((isPositive && !rhs.isPositive) || (!isPositive && rhs.isPositive)) {
    if (!rhs.isPositive) {
      return (*this * LargeNum(rhs).negate()).negate();
    }
    if (!isPositive) {
      return (rhs * LargeNum(*this).negate()).negate();
    }
  }
  if (!isPositive && !rhs.isPositive) {
    LargeNum thisCopy;
    return (LargeNum(*this).negate() * LargeNum(rhs).negate());
  }

  LargeNum count(0);
  LargeNum smallest = getSmallestNum(rhs);
  LargeNum largest = getLargestNum(rhs);
  LargeNum total;

  while (count < smallest) {
    total = total + largest;
    count++;
  }
  return total;
}

// divide two numbers. rhs is the divisor
// similar to integer division, ignore remainder
LargeNum LargeNum::operator/(const LargeNum &rhs) const {
  if (*this == LargeNum(0) || rhs == LargeNum(0)) {
    return LargeNum(0);
  }
  if ((isPositive && !rhs.isPositive) || (!isPositive && rhs.isPositive)) {
    if (!rhs.isPositive) {
      return (*this / LargeNum(rhs).negate()).negate();
    }
    if (!isPositive) {
      return (LargeNum(*this).negate() / rhs).negate();
    }
  }
  if (!isPositive && !rhs.isPositive) {
    LargeNum thisCopy;
    return (LargeNum(*this).negate() / LargeNum(rhs).negate());
  }

  LargeNum largest = *this;
  LargeNum smallest = rhs;
  LargeNum count(0);

  if (largest < smallest) {
    return LargeNum(0);
  }

  LargeNum total = largest;

  while (total >= smallest) {
    total = total - smallest;
    count++;
  }

  return count;
}

// compare size, +/-, values, dont have to convert, start at index n - 1
// return true if the numbers are equal
bool LargeNum::operator==(const LargeNum &rhs) const {
  if (isPositive != rhs.isPositive) {
    return false;
  }
  if (largeNum.size() == rhs.largeNum.size()) {
    for (int i = largeNum.size() - 1; i >= 0; i--) {
      if ((largeNum[i] - '0') != (rhs.largeNum[i] - '0')) {
        return false;
      }
    }
    return true;
  }
  return false;
}

// return true if the numbers are not equal
bool LargeNum::operator!=(const LargeNum &rhs) const { return !(*this == rhs); }

// return true if the left-hand-side number is less than the
// right-hand-side number
bool LargeNum::operator<(const LargeNum &rhs) const {
  if ((*this == rhs) || (isPositive && !rhs.isPositive)) {
    return false;
  }

  if ((!isPositive) && (rhs.isPositive)) {
    return true;
  }

  if ((!isPositive) && (!rhs.isPositive)) {
    if (largeNum.size() > rhs.largeNum.size()) {
      return true;
    }
    if (largeNum.size() == rhs.largeNum.size()) {
      for (int i = largeNum.size() - 1; i >= 0; i--) {
        if ((largeNum[i] - '0') < (rhs.largeNum[i] - '0')) {
          return false;
        }
      }
      return true;
    }
    return false;
  }

  if (largeNum.size() == rhs.largeNum.size()) {
    for (int i = largeNum.size() - 1; i >= 0; i--) {
      if ((largeNum[i] - '0') > (rhs.largeNum[i] - '0')) {
        return false;
      }
    }
    return true;
  }

  if (largeNum.size() < rhs.largeNum.size()) {
    return true;
  }

  return false;
}

// return true if the left-hand-side number is greater than the
// right-hand-side number
bool LargeNum::operator>(const LargeNum &rhs) const {
  if (*this == rhs) {
    return false;
  }
  return !(*this < rhs);
}

// return true if the left-hand-side number is less than or equal to the
// right-hand-side number
bool LargeNum::operator<=(const LargeNum &rhs) const {
  return (*this < rhs || *this == rhs);
}

// return true if the left-hand-side number is greater than or equal to the
// right-hand-side number
bool LargeNum::operator>=(const LargeNum &rhs) const {
  return (*this > rhs || *this == rhs);
}

// prefix increment
LargeNum &LargeNum::operator++() {
  *this = *this + LargeNum("1");
  return *this;
}

// postfix increment
// creates copy of object
LargeNum LargeNum::operator++(int) {
  LargeNum copy(*this);
  ++(*this);
  return copy;
}

// prefix decrement
LargeNum &LargeNum::operator--() {
  *this = *this - LargeNum("1");
  return *this;
}

// postfix decrement
LargeNum LargeNum::operator--(int) {
  LargeNum copy(*this);
  --(*this);
  return copy;
}

// output number with a comma after ever 3 digits,
// e.g. 1234567890 -> 1,234,567,890
std::ostream &operator<<(ostream &out, const LargeNum &num) {
  if (!num.isPositive) {
    out << "-";
  }
  for (int i = num.largeNum.size() - 1; i >= 0; i--) {
    out << num.largeNum[i];
    if (i > 0 && i % 3 == 0) {
      out << ",";
    }
  }
  return out;
}