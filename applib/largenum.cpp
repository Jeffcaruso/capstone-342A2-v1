// Ian Frigillana
// Project 2
// CSS 342
// Professor Pisan

#include "largenum.h"
#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

// << operator for large number
ostream &operator<<(ostream &out, const LargeNum &num) {
  if (num.isZero()) {
    out << "0";
    return out;
  }
  if (num.isNegative) {
    out << "-";
  }
  for (int i = num.fig.size() - 1; i >= 0; i--) {
    out << num.fig[i];
    if (i > 0 && i % 3 == 0) {
      out << ",";
    }
  }
  return out;
}

// Construct large number from a string
LargeNum::LargeNum(const string &str) {
  for (int i = str.size() - 1; i >= 0; i--) {
    if (str[i] == '-') {
      isNegative = true;
    } else {
      fig.push_back(str[i] - '0');
    }
  }
  if (isZero() && isNegative) {
    negate();
  }
}

// Construct large number from an integer
LargeNum::LargeNum(int anInteger) {
  int temp;
  if (anInteger == 0) {
    fig.push_back(anInteger);
  }
  isNegative = anInteger < 0;
  if (isNegative) {
    anInteger *= -1;
  }
  while (anInteger > 0) {
    temp = anInteger % 10;
    fig.push_back(temp);
    anInteger = anInteger / 10;
  }
}

// Check if number is just zero
bool LargeNum::isZero() const {
  for (int nums : fig) {
    if (nums != 0 && nums != 45) {
      return false;
    }
  }
  return true;
}

// Negate
LargeNum &LargeNum::negate() {
  if (this->isZero()) {
    this->isNegative = false;
  }
  this->isNegative = !this->isNegative;
  return *this;
}

// Addition operator
LargeNum LargeNum::operator+(const LargeNum &rhs) const {
  LargeNum result = LargeNum();
  result.fig.pop_back();
  int sum;
  vector<int> num1;
  vector<int> num2;
  // -a + b = b - a
  if (this->isNegative && !rhs.isNegative) {
    LargeNum newA = *this;
    newA.negate();
    return rhs - newA;
  }
  // a + -b = a - b
  if (!this->isNegative && rhs.isNegative) {
    LargeNum newA = rhs;
    newA.negate();
    return *this - newA;
  }
  // Set longer number to num1, shorter to num2
  if (this->fig.size() >= rhs.fig.size()) {
    num1 = this->fig;
    num2 = rhs.fig;
  } else {
    num1 = rhs.fig;
    num2 = this->fig;
  }
  // Add trailing zeroes to shorter number (num2)
  if (num1.size() != num2.size()) {
    for (int i = num2.size(); i < num1.size(); i++) {
      num2.push_back(0);
    }
  }
  int maxSize = max(num1.size(), num2.size());
  int carry = 0;
  for (int i = 0; i < maxSize; i++) {
    sum = carry + num1[i] + num2[i];
    if (sum > 9) {
      carry = 1;
      sum -= 10;
    } else {
      carry = 0;
    }
    result.fig.push_back(sum);
  }
  if (carry == 1) {
    result.fig.push_back(1);
  }
  // -a + -b = -(a+b)
  if (this->isNegative && rhs.isNegative) {
    result.negate();
  }
  return result;
}

// Multiplication operator
LargeNum LargeNum::operator*(const LargeNum &rhs) const {
  // -a * -b = a * b
  if (this->isNegative && rhs.isNegative) {
    LargeNum newA = *this;
    newA.negate();
    LargeNum newB = rhs;
    newB.negate();
    return newA * newB;
  }
  // -a * b = -c
  if (this->isNegative || rhs.isNegative) {
    LargeNum newA;
    LargeNum newB;
    if (this->isNegative) {
      newA = *this;
      newB = rhs;
    } else {
      newA = rhs;
      newB = *this;
    }
    newA.negate();
    LargeNum newC = newA * newB;
    newC.negate();
    return newC;
  }
  // if a * b, and b > a, b * a
  if (rhs > *this) {
    return rhs * *this;
  }
  LargeNum result = LargeNum(0);
  for (LargeNum i = LargeNum(1); i <= rhs; i++) {
    result = result + *this;
  }
  return result;
}

// Division operator
LargeNum LargeNum::operator/(const LargeNum &rhs) const {
  // -a / -b = a / b
  if (this->isNegative && rhs.isNegative) {
    LargeNum newA = *this;
    newA.negate();
    LargeNum newB = rhs;
    newB.negate();
    return newA / newB;
  }
  // -a / b = -c
  if (this->isNegative || rhs.isNegative) {
    LargeNum newA;
    LargeNum newB;
    newA = *this;
    newB = rhs;
    if (newA.isNegative) {
      newA.negate();
    } else {
      newB.negate();
    }
    LargeNum newC = newA / newB;
    newC.negate();
    return newC;
  }
  LargeNum temp = *this;
  int count = 0;
  while (temp >= LargeNum(0)) {
    temp = temp - rhs;
    if (temp >= LargeNum(0)) {
      count++;
    }
  }
  return LargeNum(count);
}

// Subtraction operator
LargeNum LargeNum::operator-(const LargeNum &rhs) const {
  LargeNum result = LargeNum();
  result.fig.pop_back();
  int diff;
  vector<int> num1;
  vector<int> num2;
  if (*this < rhs) {
    LargeNum newA = rhs - *this;
    newA.negate();
    return newA;
  }
  // -a - -b = b - a
  if (this->isNegative && rhs.isNegative) {
    LargeNum newA = *this;
    LargeNum newB = rhs;
    newA.negate();
    newB.negate();
    return newB - newA;
  }
  // -a - b = -(a+b)
  if (this->isNegative && !rhs.isNegative) {
    LargeNum newA = *this;
    newA.negate();
    LargeNum newB = newA + rhs;
    newB.negate();
    return newB;
  }
  // a - -b = a + b
  if (!this->isNegative && rhs.isNegative) {
    LargeNum newA = rhs;
    newA.negate();
    return *this + newA;
  }
  // Set longer number to num1, shorter to num2
  if (this->fig.size() >= rhs.fig.size()) {
    num1 = this->fig;
    num2 = rhs.fig;
  } else {
    num1 = rhs.fig;
    num2 = this->fig;
  }
  // Add trailing zeroes to shorter number (num2)
  if (num1.size() != num2.size()) {
    for (int i = num2.size(); i < num1.size(); i++) {
      num2.push_back(0);
    }
  }
  int maxSize = max(num1.size(), num2.size());
  int borrow = 0;
  for (int i = 0; i < maxSize; i++) {
    diff = (borrow + num1[i]) - num2[i];
    if (diff < 0) {
      borrow = -1;
      diff += 10;
    } else {
      borrow = 0;
    }
    result.fig.push_back(diff);
  }
  if (diff == 0) {
    result.fig.pop_back();
  }
  return result;
}

// Equals operator
bool LargeNum::operator==(const LargeNum &rhs) const {
  // If both are Zero
  if (this->isZero() && rhs.isZero()) {
    return true;
  }
  // If both are positive/negative
  if ((this->isNegative && rhs.isNegative) ||
      (!this->isNegative && !rhs.isNegative)) {
    // And numbers are same length
    if (this->fig.size() == rhs.fig.size()) {
      for (int i = 0; i < this->fig.size(); i++) {
        // If any integers are not the same, numbers are NOT equal
        if (this->fig[i] != rhs.fig[i]) {
          return false;
        }
      }
      return true;
    }
  }
  return false;
}

// Not equals operator
bool LargeNum::operator!=(const LargeNum &rhs) const { return !(*this == rhs); }

// Less than operator
bool LargeNum::operator<(const LargeNum &rhs) const {
  if (*this == rhs) {
    return false;
  }
  // 0 < non-negative
  if (this->isZero() && !rhs.isNegative) {
    return true;
  }
  // A negative is less than
  if (this->isNegative) {
    // A positive
    if (!rhs.isNegative) {
      return true;
    }
    // A negative of same size with a smaller left-most figure
    if (this->fig.size() == rhs.fig.size()) {
      for (int i = rhs.fig.size() - 1; i >= 0; i--) {
        if (this->fig[i] > rhs.fig[i]) {
          return true;
        }
      }
      return false;
    }
    // A negative that is shorter
    return rhs.fig.size() < this->fig.size();
  }
  // If both are positive
  if (!rhs.isNegative) {
    // The number with smallest left-most figure is smaller
    if (this->fig.size() == rhs.fig.size()) {
      for (int i = rhs.fig.size() - 1; i >= 0; i--) {
        if (this->fig[i] < rhs.fig[i]) {
          return true;
        }
      }
      return false;
    }
    // The shorter number is smaller
    return this->fig.size() < rhs.fig.size();
  }
  return false;
}

// Greater than operator
bool LargeNum::operator>(const LargeNum &rhs) const {
  return *this != rhs && !(*this < rhs);
}

// Less than or equal to operator
bool LargeNum::operator<=(const LargeNum &rhs) const {
  return *this < rhs || *this == rhs;
}

// Greater than or equal to operator
bool LargeNum::operator>=(const LargeNum &rhs) const {
  return *this > rhs || *this == rhs;
}

// prefix increment operator
LargeNum &LargeNum::operator++() {
  *this = *this + LargeNum(1);
  return *this;
}

// postfix decrement opterator
LargeNum LargeNum::operator++(int) {
  LargeNum copy(*this);
  ++(*this);
  return copy;
}

// prefix decrement operator
LargeNum &LargeNum::operator--() {
  *this = *this - LargeNum(1);
  return *this;
}

// postfix decrement operator
LargeNum LargeNum::operator--(int) {
  LargeNum copy(*this);
  --(*this);
  return copy;
};