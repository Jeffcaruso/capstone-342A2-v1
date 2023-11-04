#include "largenum.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <math.h>
#include <string>

using namespace std;

// String constructor for LargeNum
LargeNum::LargeNum(const string &str) {
  int index = 0;
  if (str[0] == '-') {
    isNegative = true;
    index = 1;
  }
  for (int i = index; i < str.size(); i++) {
    largeNum.push_back(str[i] - '0');
  }
  reverse(largeNum.begin(), largeNum.end());
};

// Integer constructor for LargeNum
LargeNum::LargeNum(int anInteger) {
  if (anInteger < 0) {
    isNegative = true;
    anInteger *= -1;
  }
  if (anInteger == 0) {
    largeNum.push_back(anInteger);
    isNegative = false;
  }
  while (anInteger > 0) {
    int remainder = anInteger % 10;
    largeNum.push_back(remainder);
    anInteger /= 10;
  }
}

// Makes LargeNum printable
ostream &operator<<(ostream &out, const LargeNum &num) {
  string hold;
  for (int i = 0; i < static_cast<int>(num.largeNum.size()); ++i) {
    if (i % 3 == 0 && i > 0) {
      hold += ",";
    }
    hold += static_cast<char>(num.largeNum[i] + 48);
  }
  if (num.isNegative) {
    hold += "-";
  }
  reverse(hold.begin(), hold.end());
  out << hold;
  return out;
}

// returns true if the number is zero
bool LargeNum::isZero() const {
  return (largeNum.size() == 1 && largeNum[0] == 0);
}

// negate the number, positive becomes negative, negative becomes positive
LargeNum &LargeNum::negate() {
  if (largeNum.size() == 1 && largeNum[0] == 0) {
    isNegative = false;
  } else {
    if (isNegative) {
      isNegative = false;
    } else if (!isNegative) {
      isNegative = true;
    }
  }
  return *this;
}

// Removes excess 0s from the front of the vector
LargeNum LargeNum::removeZeros(LargeNum other) {
  for (auto i = static_cast<int>(other.largeNum.size() - 1); i > 0; --i) {
    if (other.largeNum[i] == 0) {
      other.largeNum.pop_back();
    } else if (other.largeNum[i] != 0) {
      break;
    }
  }
  return other;
}

// Adds two LargeNums together
LargeNum LargeNum::operator+(const LargeNum &rhs) const {
  uint64_t size = max(rhs.largeNum.size(), largeNum.size());
  int remainder = 0;
  int current = 0;
  LargeNum hold;
  hold.largeNum.pop_back();
  bool adding = true;
  int index = 0;

  if (!isNegative && rhs.isNegative) {
    LargeNum temp = rhs;
    temp.negate();
    return (*this - temp);
  }
  if (isNegative && !(rhs.isNegative)) {
    LargeNum temp1 = *this;
    temp1.negate();
    LargeNum temp2 = rhs;
    temp1 = temp1 - temp2;
    temp1.negate();
    return temp1;
  }
  if (isNegative && rhs.isNegative) {
    LargeNum temp1 = *this;
    temp1.negate();
    LargeNum temp2 = rhs;
    temp2.negate();
    temp1 = temp1 + temp2;
    temp1.negate();
    return temp1;
  }

  while (adding) {
    current = 0;
    if (index < rhs.largeNum.size() && index < largeNum.size()) {
      current = largeNum[index] + rhs.largeNum[index] + remainder;
      remainder = 0;
    } else if (index < rhs.largeNum.size() && index >= largeNum.size()) {
      current = rhs.largeNum[index] + remainder;
      remainder = 0;
    } else if (index >= rhs.largeNum.size() && index < largeNum.size()) {
      current = largeNum[index] + remainder;
      remainder = 0;
    }
    if (current < 10) {
      hold.largeNum.push_back(current);
      ++index;
    } else if (current == 10) {
      hold.largeNum.push_back(0);
      remainder = 1;
      ++index;
    } else if (current > 10) {
      hold.largeNum.push_back(current - 10);
      remainder = 1;
      ++index;
    }
    if (remainder == 1 && index == size) {
      hold.largeNum.push_back(1);
      break;
    }
    if (remainder == 0 && index == size) {
      break;
    }
  }
  hold = removeZeros(hold);
  return hold;
}

// Subtraction operator for LargeNum objects
LargeNum LargeNum::operator-(const LargeNum &rhs) const {
  uint64_t size = max(rhs.largeNum.size(), largeNum.size());
  int borrow = 0;
  int current = 0;
  LargeNum hold;
  hold.largeNum.pop_back();
  int index = 0;

  if (!isNegative && rhs.isNegative) {
    LargeNum temp = rhs;
    temp.negate();
    return (*this + temp);
  }
  if (isNegative && !(rhs.isNegative)) {
    LargeNum temp1 = *this;
    temp1.negate();
    LargeNum temp2 = rhs;
    temp1 = temp1 + temp2;
    temp1.negate();
    return temp1;
  }
  if (isNegative && rhs.isNegative) {
    LargeNum temp1 = *this;
    temp1.negate();
    LargeNum temp2 = rhs;
    temp2.negate();
    temp1 = temp1 - temp2;
    temp1.negate();
    return temp1;
  }
  if (!(isNegative && rhs.isNegative) &&
      rhs.largeNum.size() > largeNum.size()) {
    LargeNum temp = rhs - *this;
    temp.negate();
    return temp;
  }

  while (!(index == size)) {
    current = 0;
    if (index < rhs.largeNum.size() && index < largeNum.size()) {
      current = largeNum[index] - rhs.largeNum[index] - borrow;
      borrow = 0;
    } else if (index < rhs.largeNum.size() && index >= largeNum.size()) {
      current = rhs.largeNum[index];
    } else if (index >= rhs.largeNum.size() && index < largeNum.size()) {
      current = largeNum[index] - borrow;
      borrow = 0;
    }
    if (current < 10 && current > 0) {
      hold.largeNum.push_back(current);
      ++index;
    } else if (current == 0) {
      hold.largeNum.push_back(0);
      ++index;
    } else if (current < 0 && index < (largeNum.size() - 1)) {
      current += 10;
      hold.largeNum.push_back(current);
      borrow = 1;
      ++index;
    } else if (current < 0 && index >= (largeNum.size() - 1)) {
      current *= -1;
      hold.negate();
      hold.largeNum.push_back(current);
      ++index;
    }
  }
  hold = removeZeros(hold);
  return hold;
}

// Multiplier helper function
LargeNum LargeNum::multiplyLargeNum(const LargeNum first,
                                    const LargeNum second) {
  LargeNum temp = first;
  LargeNum temp1 = temp;
  for (int ele = 0; ele < second.largeNum.size(); ++ele) {
    int control = 0;
    if (ele == 0) {
      control = 1;
    } else {
      control = 0;
    }
    for (int i = 0; i < (second.largeNum[ele] * (pow(10, ele)) - control);
         ++i) {
      temp1 = temp1 + temp;
    }
  }
  return temp1;
}

// Multiplication operator for LargeNum objects
LargeNum LargeNum::operator*(const LargeNum &rhs) const {
  if (rhs.isZero() || this->isZero()) {
    return LargeNum(0);
  }
  if (isNegative && !(rhs.isNegative)) {
    LargeNum temp = *this;
    temp.negate();
    LargeNum temp1 = temp;
    for (auto ele : rhs.largeNum) {
      for (int i = 0; i < ele - 1; ++i) {
        temp1 = temp1 + temp;
      }
    }
    temp1.negate();
    return temp1;
  }
  if (!isNegative && rhs.isNegative) {
    LargeNum temp = *this;
    LargeNum temp1 = temp;
    for (auto ele : rhs.largeNum) {
      for (int i = 0; i < ele - 1; ++i) {
        temp1 = temp1 + temp;
      }
    }
    temp1.negate();
    return temp1;
  }
  if (isNegative && rhs.isNegative) {
    LargeNum temp = *this;
    temp.negate();
    LargeNum temp1 = temp;
    for (auto ele : rhs.largeNum) {
      for (int i = 0; i < ele - 1; ++i) {
        temp1 = temp1 + temp;
      }
    }
    return temp1;
  }
  if (!isNegative && !(rhs.isNegative)) {
    return (multiplyLargeNum(*this, rhs));
  }
  return LargeNum();
}

// Division operator for LargeNum objects
LargeNum LargeNum::operator/(const LargeNum &rhs) const {
  if (this->isZero()) {
    return LargeNum(0);
  }
  if (rhs.largeNum.size() > largeNum.size()) {
    return LargeNum(0);
  }
  LargeNum temp = *this;

  if (isNegative && !(rhs.isNegative)) {
    temp.negate();
    temp = temp / rhs;
    temp.negate();
    return temp;
  }
  if (!isNegative && rhs.isNegative) {
    LargeNum temp2 = rhs;
    temp2.negate();
    temp = temp / temp2;
    temp.negate();
    return temp;
  }
  if (isNegative && rhs.isNegative) {
    temp.negate();
    LargeNum temp2 = rhs;
    temp2.negate();
    temp = temp / temp2;
    return temp;
  }

  bool divisible = false;
  if (temp >= rhs) {
    divisible = true;
  }
  int counter = 0;
  while (divisible) {
    temp = temp - rhs;
    counter += 1;
    divisible = false;
    if (temp >= rhs) {
      divisible = true;
    }
  }
  return LargeNum(counter);
}

// Compares if two LargeNum are equal
bool LargeNum::operator==(const LargeNum &rhs) const {
  if (largeNum.size() != rhs.largeNum.size() || isNegative != rhs.isNegative) {
    return false;
  }
  for (int i = 0; i < largeNum.size(); ++i) {
    if (largeNum[i] != rhs.largeNum[i]) {
      return false;
    }
  }
  return true;
}

// Compares if two LargeNum are not equal
bool LargeNum::operator!=(const LargeNum &rhs) const {
  if (largeNum.size() != rhs.largeNum.size() || isNegative != rhs.isNegative) {
    return true;
  }
  for (int i = 0; i < largeNum.size(); ++i) {
    if (largeNum[i] != rhs.largeNum[i]) {
      return true;
    }
  }
  return false;
}

// Compares if a LargeNum is less than another
bool LargeNum::operator<(const LargeNum &rhs) const {
  if (isNegative && !(rhs.isNegative)) {
    return true;
  }
  if (!isNegative && rhs.isNegative) {
    return false;
  }
  if ((isNegative && rhs.isNegative) &&
      (largeNum.size() > rhs.largeNum.size())) {
    return true;
  }
  if (!(isNegative && rhs.isNegative) &&
      (largeNum.size() < rhs.largeNum.size())) {
    return true;
  }

  for (auto i = static_cast<int>(largeNum.size() - 1); i >= 0; --i) {
    if (largeNum[i] < rhs.largeNum[i]) {
      return true;
    }
    if (largeNum[i] > rhs.largeNum[i]) {
      return false;
    }
  }
  return false;
}

// Compares if a LargeNum is greater than another
bool LargeNum::operator>(const LargeNum &rhs) const {
  if (!isNegative && (rhs.isNegative)) {
    return true;
  }
  if (isNegative && !(rhs.isNegative)) {
    return false;
  }
  if ((isNegative && rhs.isNegative) &&
      (largeNum.size() < rhs.largeNum.size())) {
    return true;
  }
  if (!(isNegative && rhs.isNegative) &&
      (largeNum.size() > rhs.largeNum.size())) {
    return true;
  }

  for (auto i = static_cast<int>(largeNum.size() - 1); i >= 0; --i) {
    if (largeNum[i] > rhs.largeNum[i]) {
      return true;
    }
    if (largeNum[i] < rhs.largeNum[i]) {
      return false;
    }
  }
  return false;
}

// Checks to see if the main object is less than or equal the second
bool LargeNum::operator<=(const LargeNum &rhs) const {
  return ((*this == rhs) || (*this < rhs));
}

// Checks to see if the main object is greater than or equal the second
bool LargeNum::operator>=(const LargeNum &rhs) const {
  return ((*this == rhs) || (*this > rhs));
}

// Prefix increment the LargeNum object by 1
LargeNum &LargeNum::operator++() {
  *this = *this + LargeNum(1);
  return *this;
}

// Postfix increment the LargeNum object by 1
LargeNum LargeNum::operator++(int) {
  LargeNum temp = *this;
  *this = *this + LargeNum(1);
  return temp;
}

// Prefix decrement the LargeNum object by 1
LargeNum &LargeNum::operator--() {
  *this = *this - LargeNum(1);
  return *this;
}

/// Postfix decrement the LargeNum object by 1
LargeNum LargeNum::operator--(int) {
  LargeNum temp = *this;
  *this = *this - LargeNum(1);
  return temp;
}
