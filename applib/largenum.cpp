#include "largenum.h"
#include <algorithm>
#include <iostream>

using namespace std;

// Overloaded ostream operator to print LargeNum objects.
ostream &operator<<(ostream &out, const LargeNum &num) {
  if (num.bigNum.empty()) {
    out << 0;
    return out;
  }

  if (num.isNegative) {
    out << "-";
  }

  size_t digitsLeftToPrint = num.bigNum.size();
  for (size_t i = num.bigNum.size(); i > 0; --i) {
    out << num.bigNum[i - 1];
    digitsLeftToPrint--;

    if (digitsLeftToPrint > 0 && digitsLeftToPrint % 3 == 0) {
      out << ",";
    }
  }

  return out;
}

// Constructor that initializes LargeNum from a string.
LargeNum::LargeNum(const string &str) {
  for (int i = static_cast<int>(str.size()) - 1; i >= 0; i--) {
    if (i == static_cast<int>(str.size()) - 1 && str[i] == '0') {
      continue;
    }
    if (str[i] == '-') {
      isNegative = true;
      continue;
    }
    bigNum.push_back(str[i] - '0');
  }
}

// Constructor that initializes LargeNum from an integer.
LargeNum::LargeNum(int anInteger) {

  if (anInteger < 0) {
    isNegative = true;
    anInteger = -anInteger;
  }

  while (anInteger != 0) {
    bigNum.push_back(anInteger % 10);
    anInteger = anInteger / 10;
  }
}

// Check if the LargeNum object is zero.
bool LargeNum::isZero() const {
  return bigNum.empty() || (bigNum.size() == 1 && bigNum[0] == 0);
}

// Negate the sign of the LargeNum object.
LargeNum &LargeNum::negate() {
  isNegative = !isNegative;
  return *this;
}

// Addition operator for LargeNum objects.
LargeNum LargeNum::operator+(const LargeNum &rhs) const {
  LargeNum result;

  LargeNum num1 = *this;
  LargeNum num2 = rhs;

  if (isNegative && rhs.isNegative) {
    num1.negate();
    num2.negate();
    result = num1 + num2;
    result.negate();
    return result;
  }

  if (!isNegative && rhs.isNegative) {
    num2.negate();
    return num1 - num2;
  }

  if (isNegative && !rhs.isNegative) {
    num1.negate();
    return num2 - num1;
  }

  int carry = 0;
  size_t maxSize = max(bigNum.size(), rhs.bigNum.size());

  for (size_t i = 0; i < maxSize || carry != 0; i++) {
    int sum = carry;
    if (i < bigNum.size()) {
      sum += bigNum[i];
    }
    if (i < rhs.bigNum.size()) {
      sum += rhs.bigNum[i];
    }

    carry = sum / 10;
    sum %= 10;

    result.bigNum.push_back(sum);
  }

  return result;
}

// Subtraction operator for LargeNum objects.
LargeNum LargeNum::operator-(const LargeNum &rhs) const {
  LargeNum result;

  LargeNum num1 = *this;
  LargeNum num2 = rhs;

  if (num1.isZero()) {
    return num2.negate();
  }

  if (!num1.isNegative && num2.isNegative) {
    return num1 + num2.negate();
  }

  if (num2 > num1) {
    result = num2 - num1;
    result.negate();
    return result;
  }

  int borrow = 0;
  size_t maxSize = max(num1.bigNum.size(), num2.bigNum.size());

  for (size_t i = 0; i < maxSize; i++) {
    int digit1 = (i < num1.bigNum.size()) ? num1.bigNum[i] : 0;
    int digit2 = (i < num2.bigNum.size()) ? num2.bigNum[i] : 0;

    int diff = borrow + digit1 - digit2;

    if (diff < 0) {
      borrow = -1;
      diff += 10;
    } else {
      borrow = 0;
    }

    result.bigNum.push_back(diff);
  }

  if (borrow != 0) {

    result.bigNum.clear();
  }

  while (!result.bigNum.empty() && result.bigNum.back() == 0) {
    result.bigNum.pop_back();
  }

  return result;
}

// Multiplication operator for LargeNum objects.
LargeNum LargeNum::operator*(const LargeNum &rhs) const {
  LargeNum result;
  LargeNum num1 = *this;
  LargeNum num2 = rhs;

  if (isNegative && rhs.isNegative) {
    num1.negate();
    num2.negate();
    result = num1 * num2;
    return result;
  }

  if (isNegative || rhs.isNegative) {
    if (isNegative) {
      num1.negate();
    } else {
      num2.negate();
    }
    result = num1 * num2;
    result.negate();
    return result;
  }

  if (this->isZero() || rhs.isZero()) {
    result.bigNum.push_back(0);
  }

  for (LargeNum i(0); i < rhs; ++i) {
    result = result + *this;
  }

  while (!result.bigNum.empty() && result.bigNum.back() == 0) {
    result.bigNum.pop_back();
  }

  return result;
}

// Division operator for LargeNum objects.
LargeNum LargeNum::operator/(const LargeNum &rhs) const {
  LargeNum result;
  LargeNum quotient;
  LargeNum num1 = *this;
  LargeNum num2 = rhs;

  if (isNegative && (rhs.isNegative)) {
    num1.negate();
    num2.negate();
    result = num1 / num2;
    result.negate();
    return result;
  }
  if (isNegative) {
    num1.negate();
    result = num1 / num2;
    result.negate();
    return result;
  }
  if (rhs.isNegative) {
    num2.negate();
    result = num1 / num2;
    result.negate();
    return result;
  }

  if (isZero() || num1 < num2) {
    result.bigNum.push_back(0);
  } else {
    while (num1 >= num2) {
      num1 = num1 - num2;
      ++quotient;
    }
    result = quotient;
  }

  while (!result.bigNum.empty() && result.bigNum.back() == 0) {
    result.bigNum.pop_back();
  }

  return result;
}

// Equality operator for LargeNum objects.
bool LargeNum::operator==(const LargeNum &rhs) const {
  if (bigNum.size() != rhs.bigNum.size()) {
    return false;
  }
  for (size_t i = 0; i < bigNum.size(); i++) {
    if (bigNum[i] != rhs.bigNum[i]) {
      return false;
    }
  }
  return true;
}

// Inequality operator for LargeNum objects.
bool LargeNum::operator!=(const LargeNum &rhs) const { return !(*this == rhs); }

// Less than operator for LargeNum objects.
bool LargeNum::operator<(const LargeNum &rhs) const {
  if (isNegative != rhs.isNegative) {
    return isNegative;
  }

  size_t maxSize = max(bigNum.size(), rhs.bigNum.size());
  for (size_t i = maxSize - 1; i != SIZE_MAX; --i) {
    int digit1 = (i < bigNum.size()) ? bigNum[i] : 0;
    int digit2 = (i < rhs.bigNum.size()) ? rhs.bigNum[i] : 0;

    if (digit1 < digit2) {
      return !isNegative;
    }
    if (digit1 > digit2) {
      return isNegative;
    }
  }

  return false;
}

// Greater than operator for LargeNum objects.
bool LargeNum::operator>(const LargeNum &rhs) const {
  if (isNegative != rhs.isNegative) {
    return rhs.isNegative;
  }

  size_t maxSize = max(bigNum.size(), rhs.bigNum.size());
  for (size_t i = maxSize - 1; i != SIZE_MAX; --i) {
    int digit1 = (i < bigNum.size()) ? bigNum[i] : 0;
    int digit2 = (i < rhs.bigNum.size()) ? rhs.bigNum[i] : 0;

    if (digit1 > digit2) {
      return !isNegative;
    }

    if (digit1 < digit2) {
      return isNegative;
    }
  }

  return false;
}

// Less than or equal to operator for LargeNum objects.
bool LargeNum::operator<=(const LargeNum &rhs) const { return !(*this > rhs); }

// Greater than or equal to operator for LargeNum objects.
bool LargeNum::operator>=(const LargeNum &rhs) const { return !(*this < rhs); }

// Prefix increment operator for LargeNum objects.
LargeNum &LargeNum::operator++() {
  LargeNum inc(1);

  *this = *this + inc;
  return *this;
}

// Postfix increment operator for LargeNum objects.
LargeNum LargeNum::operator++(int) {
  LargeNum originalValue = *this;
  LargeNum inc(1);

  *this = *this + inc;
  return originalValue;
}

// Prefix decrement operator for LargeNum objects.
LargeNum &LargeNum::operator--() {
  LargeNum inc(1);

  *this = *this - inc;
  return *this;
}

// Postfix decrement operator for LargeNum objects.
LargeNum LargeNum::operator--(int) {
  LargeNum originalValue = *this;
  LargeNum inc(1);

  *this = *this - inc;
  return originalValue;
}
