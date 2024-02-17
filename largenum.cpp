/**
 * LargeNum Class
 * Represents large numbers with each digit stored in reverse order. Provides
 * utility functions for arithmetric, relational, and unary operations.
 * **/

#include "largenum.h"
#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

// Constructs LargeNum from a string, storing digits in reverse order
LargeNum::LargeNum(const string &str) {
  if (str[0] == '0' || (str[0] == '-' && str[1] == '0')) {
    digits.push_back(0);
    return;
  }

  isPositive = str[0] != '-';
  int firstIndex = isPositive ? 0 : 1;

  for (int i = str.size() - 1; i >= firstIndex; i--) {
    digits.push_back(str[i] - '0');
  }
}

// Constructs LargeNum from an integer, storing digits in reverse order
LargeNum::LargeNum(int anInteger) {
  if (anInteger < 0) {
    isPositive = false;
    anInteger = -anInteger;
  }

  do {
    digits.push_back(anInteger % 10);
    anInteger /= 10;
  } while (anInteger > 0);
}

// Returns true if LargeNum is zero, otherwise false
bool LargeNum::isZero() const { return (digits.size() == 1 && digits[0] == 0); }

// Negates LargeNum if not zero
// Positive becomes negative, negative becomes positive
LargeNum &LargeNum::negate() {
  if (!isZero()) {
    isPositive = !isPositive;
  }
  return *this;
}

// Adds two LargeNums
LargeNum LargeNum::operator+(const LargeNum &rhs) const {
  LargeNum result("");

  size_t maxSize = max(digits.size(), rhs.digits.size());
  int carry = 0;

  if ((isPositive && rhs.isPositive) || (!isPositive && !rhs.isPositive)) {
    for (int i = 0; i < maxSize; i++) {
      int num1 = (i < digits.size()) ? digits[i] : 0;
      int num2 = (i < rhs.digits.size()) ? rhs.digits[i] : 0;

      int sum = num1 + num2 + carry;
      carry = sum / 10;

      result.digits.push_back(sum % 10);
    }

    if (carry > 0) {
      result.digits.push_back(carry);
    }

    // Removes leading zeros
    while (result.digits.size() > 1 && result.digits.back() == 0) {
      result.digits.pop_back();
    }

    if (!isPositive && !rhs.isPositive) {
      result.negate();
    }

  } else if (isPositive && !rhs.isPositive) {
    LargeNum negRhs = rhs;
    negRhs.negate();
    result = *this - negRhs;
  } else if (!isPositive && rhs.isPositive) {
    LargeNum negLhs = *this;
    negLhs.negate();
    result = rhs - negLhs;
  }

  return result;
}

// Subtracts two LargeNums
LargeNum LargeNum::operator-(const LargeNum &rhs) const {
  LargeNum result("");

  int borrow = 0;

  if ((isPositive && rhs.isPositive) && *this >= rhs) {
    for (int i = 0; i < digits.size(); i++) {
      int num1 = (i < digits.size()) ? digits[i] : 0;
      int num2 = (i < rhs.digits.size()) ? rhs.digits[i] : 0;

      int diff = num1 - num2 - borrow;
      if (diff < 0) {
        diff += 10;
        borrow = 1;
      } else {
        borrow = 0;
      }

      result.digits.push_back(diff);
    }

    // Removes leading zeros
    while (result.digits.size() > 1 && result.digits.back() == 0) {
      result.digits.pop_back();
    }

  } else if ((!isPositive && !rhs.isPositive) && *this >= rhs) {
    LargeNum negLhs = *this;
    negLhs.negate();
    LargeNum negRhs = rhs;
    negRhs.negate();
    result = negRhs - negLhs;
  } else if (isPositive && !rhs.isPositive) {
    LargeNum negRhs = rhs;
    negRhs.negate();
    result = *this + negRhs;
  } else if (!isPositive && rhs.isPositive) {
    LargeNum negLhs = *this;
    negLhs.negate();
    result = (rhs + negLhs).negate();
  } else {
    result = (rhs - *this).negate();
  }

  return result;
}

// Multiplies two LargeNums
LargeNum LargeNum::operator*(const LargeNum &rhs) const {
  if (rhs > *this) {
    return rhs * *this;
  }

  LargeNum result(0);

  for (int i = 0; i < rhs.digits.size(); i++) {
    LargeNum product(0);

    for (int j = 0; j < rhs.digits[i]; j++) {
      product = product + *this;
    }

    if (i > 0) {
      for (int k = 0; k < i; k++) {
        product.digits.insert(product.digits.begin(), 0);
      }
    }

    result = result + product;
  }

  // Removes leading zeros
  while (result.digits.size() > 1 && result.digits.back() == 0) {
    result.digits.pop_back();
  }

  if (result.isZero()) {
    result.isPositive = true;
  } else {
    result.isPositive = (isPositive == rhs.isPositive);
  }

  return result;
}

// Divides two LargeNums
// Prints error message and return 0 if division is by zero
LargeNum LargeNum::operator/(const LargeNum &rhs) const {
  if (rhs.isZero()) {
    cerr << "ERROR: Division by zero" << endl;
    return LargeNum(0);
  }

  LargeNum result(0);

  LargeNum dividend(*this);
  if (!dividend.isPositive) {
    dividend.negate();
  }

  LargeNum divisor(rhs);
  if (!divisor.isPositive) {
    divisor.negate();
  }

  while (dividend >= divisor) {
    dividend = dividend - divisor;
    result = ++result;
  }

  if (result.isZero()) {
    result.isPositive = true;
  } else {
    result.isPositive = (isPositive == rhs.isPositive);
  }

  return result;
}

// Returns true if two LargeNums are equal, otherwise false
// LargeNum must have equal positive/negative signs, sizes, and digit sequence
bool LargeNum::operator==(const LargeNum &rhs) const {
  return ((isPositive == rhs.isPositive) && (digits == rhs.digits));
}

// Returns true is two LargeNums are not equal, otherwise false
bool LargeNum::operator!=(const LargeNum &rhs) const { return !(*this == rhs); }

// Returns true if left-hand-side LargeNum is less than right-hand-side
// LargeNum, otherwise false
bool LargeNum::operator<(const LargeNum &rhs) const {
  if (isPositive != rhs.isPositive) {
    return !isPositive;
  }

  if (digits.size() != rhs.digits.size()) {
    return (digits.size() < rhs.digits.size()) == isPositive;
  }

  for (int i = digits.size() - 1; i >= 0; i--) {
    if (digits[i] != rhs.digits[i]) {
      return (digits[i] < rhs.digits[i]) == isPositive;
    }
  }

  return false;
}

// Returns true if left-hand-side LargeNum is greater than right-hand-side
// LargeNum, otherwise false
bool LargeNum::operator>(const LargeNum &rhs) const { return rhs < *this; }

// Returns true if left-hand-side LargeNum is less than or equal to
// right-hand-side LargeNum, otherwise false
bool LargeNum::operator<=(const LargeNum &rhs) const {
  return (*this < rhs) || (*this == rhs);
}

// Returns true if left-hand-side LargeNum is greater than or equal to
// right-hand-side LargeNum, otherwise false
bool LargeNum::operator>=(const LargeNum &rhs) const {
  return (*this > rhs) || (*this == rhs);
}

// Prefix increment
LargeNum &LargeNum::operator++() {
  *this = *this + LargeNum(1);
  return *this;
}

// Postfix increment
LargeNum LargeNum::operator++(int) {
  LargeNum temp(*this);
  ++*this;
  return temp;
}

// Prefix decrement
LargeNum &LargeNum::operator--() {
  *this = *this - LargeNum(1);
  return *this;
}

// Postfix decrement
LargeNum LargeNum::operator--(int) {
  LargeNum temp(*this);
  --*this;
  return temp;
}

// Prints LargeNum with commas as thousands separators
ostream &operator<<(ostream &out, const LargeNum &num) {
  if (!num.isPositive) {
    out << "-";
  }

  for (int i = num.digits.size() - 1; i >= 0; i--) {
    out << num.digits[i];
    if (i % 3 == 0 && i > 0) {
      out << ",";
    }
  }
  return out;
}
