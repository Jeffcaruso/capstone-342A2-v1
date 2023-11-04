#include "largenum.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Your code goes here

// output number with a comma after every 3 digits,
ostream &operator<<(ostream &out, const LargeNum &num) {
  string result;
  string temp = num.num;
  int high = static_cast<int>(temp.length()) - 1;
  for (int i = high; i >= 0; i--) {
    if ((high - i) % 3 == 0 && i != high) {
      result.push_back(',');
    }
    result.push_back(temp[i]);
  }
  result = LargeNum::reverse(result);
  if (!num.isPositive) {
    out << "-";
  }
  out << result;
  return out;
}

// default constructor from string
LargeNum::LargeNum(const string &str) {
  if (str == "-0") {
    num = "0";
    return;
  }

  if (str[0] == '-') {
    isPositive = false;
    num = str.substr(1);
  } else {
    num = str;
  }
}

// constructor from int
LargeNum::LargeNum(int anInteger) {
  if (anInteger < 0) {
    isPositive = false;
    anInteger *= -1;
  }
  num = to_string(anInteger);
}

// reverses the string
string LargeNum::reverse(string num) {
  string temp;
  int length = static_cast<int>(num.length()) - 1;
  for (int i = length; i >= 0; i--) {
    temp.push_back(num[i]);
  }
  return temp;
}

// returns true if the number is zero
bool LargeNum::isZero() const { return num == "0"; }

// negate the number, positive becomes negative, negative becomes positive
// zero is positive
LargeNum &LargeNum::negate() {
  if (isZero()) {
  } else if (isPositive) {
    isPositive = false;
  } else {
    isPositive = true;
  }
  return *this;
}

// add two nums
LargeNum LargeNum::operator+(const LargeNum &rhs) const {
  string result;
  if (isPositive && !rhs.isPositive) {
    return LargeNum(num) - LargeNum(rhs.num);
  }
  if (!isPositive && rhs.isPositive) {
    return LargeNum(rhs.num) - LargeNum(num);
  }
  string num1 = reverse(num);
  string num2 = reverse(rhs.num);
  int carry = 0;
  for (int i = 0; i < max(num1.length(), num2.length()); i++) {
    int temp1 = i < num1.length() ? num1[i] - '0' : 0;
    int temp2 = i < num2.length() ? num2[i] - '0' : 0;
    int sum = temp1 + temp2 + carry;
    carry = sum / 10;
    result += to_string(sum % 10);
  }
  if (carry != 0) {
    result += to_string(carry);
  }
  result = reverse(result);
  LargeNum realResult = LargeNum(result);
  if (!isPositive && !rhs.isPositive) {
    realResult.isPositive = false;
  }
  return realResult;
}

// subtract two numbers
LargeNum LargeNum::operator-(const LargeNum &rhs) const {
  string result;
  if (num == rhs.num && isPositive && rhs.isPositive) {
    return LargeNum("0");
  }
  if (!isPositive && !rhs.isPositive) {
    return LargeNum(rhs.num) - LargeNum(num);
  }
  if (isPositive && !rhs.isPositive) {
    return LargeNum(num) + LargeNum(rhs.num);
  }

  LargeNum realResult = LargeNum(result);
  string num1 = reverse(num);
  string num2 = reverse(rhs.num);
  if (num2.length() > num1.length()) {
    string tempS = num1;
    num1 = num2;
    num2 = tempS;
    realResult.isPositive = false;
  }
  int carry = 0;
  int difference = 0;
  for (int i = 0; i < max(num1.length(), num2.length()); i++) {
    int temp1 = i < num1.length() ? num1[i] - '0' : 0;
    int temp2 = i < num2.length() ? num2[i] - '0' : 0;
    difference = temp1 - temp2 - carry;
    carry = 0;
    if (difference < 0 && i + 1 < num1.length()) {
      difference += 10;
      carry = 1;
    }
    result += to_string(difference);
  }
  while (result.length() > 1 && result.back() == '0') {
    result.pop_back();
  }

  realResult.num = reverse(result);
  return realResult;
}

// multiply two numbers
LargeNum LargeNum::operator*(const LargeNum &rhs) const {
  if (isZero() || rhs.isZero()) {
    return LargeNum("0");
  }
  LargeNum realResult = LargeNum(0);
  LargeNum num2 = rhs;
  if (!rhs.isPositive) {
    num2.negate();
  }
  for (LargeNum i = LargeNum(0); i < num2; i++) {
    realResult = realResult + *this;
  }
  if (!isPositive && !rhs.isPositive) {
    realResult.isPositive = true;
  } else if (!isPositive || !rhs.isPositive) {
    realResult.isPositive = false;
  }
  return realResult;
}

// divide two numbers. rhs is the divisor
// similar to integer division, ignore remainder
LargeNum LargeNum::operator/(const LargeNum &rhs) const {
  if (*this == rhs) {
    return LargeNum(1);
  }
  if (isZero() || rhs.isZero() || num.length() < rhs.num.length()) {
    return LargeNum(0);
  }
  LargeNum num1 = LargeNum(num);
  LargeNum num2 = rhs;
  if (!rhs.isPositive) {
    num2.negate();
  }
  LargeNum counter = LargeNum(1);
  while (num1 > num2) {
    num1 = num1 - num2;
    counter++;
  }
  if (num1 < num2) {
    counter--;
  }
  if (!isPositive && !rhs.isPositive) {
    counter.isPositive = true;
  } else if (!isPositive || !rhs.isPositive) {
    counter.isPositive = false;
  }
  return counter;
}

// return true if the numbers are equal
bool LargeNum::operator==(const LargeNum &rhs) const {
  return isPositive == rhs.isPositive && num == rhs.num;
}

// return true if the nubmers are not equal
bool LargeNum::operator!=(const LargeNum &rhs) const { return !(*this == rhs); }

// return true if the left-hand-side number is less than the
// right-hand-side
bool LargeNum::operator<(const LargeNum &rhs) const {
  if (!isPositive && !rhs.isPositive) {
    return LargeNum(num) > LargeNum(rhs);
  }
  if (isPositive != rhs.isPositive) {
    return !isPositive;
  }
  if (num.length() != rhs.num.length()) {
    return (num.length() < rhs.num.length());
  }
  for (int i = 0; i < num.length(); i++) {
    if (num[i] < rhs.num[i]) {
      return true;
    }
    if (num[i] > rhs.num[i]) {
      return false;
    }
  }
  return false;
}

// return true if the left-hand-side number is greater than the
// right-hand-side number
bool LargeNum::operator>(const LargeNum &rhs) const {
  if (!isPositive && !rhs.isPositive) {
    return LargeNum(num) < LargeNum(rhs.num);
  }
  if (isPositive != rhs.isPositive) {
    return isPositive;
  }
  if (num.length() != rhs.num.length()) {
    return (num.length() > rhs.num.length());
  }
  for (int i = 0; i < num.length(); i++) {
    if (num[i] > rhs.num[i]) {
      return true;
    }
    if (num[i] < rhs.num[i]) {
      return false;
    }
  }
  return false;
}

// return true if the left-hand-side number is less than or equal to the
// right-hand-side number
bool LargeNum::operator<=(const LargeNum &rhs) const {
  return (*this == rhs) || (*this < rhs);
}

// return true if the left-hand-side number is greater than or equal to the
// right-hand-side number
bool LargeNum::operator>=(const LargeNum &rhs) const {
  return (*this == rhs) || (*this > rhs);
}

// prefix increment
LargeNum &LargeNum::operator++() {
  if (!isPositive) {
    this->num = (*this - LargeNum(1)).num;
    if (isZero()) {
      isPositive = true;
    }
    return *this;
  }
  *this = *this + LargeNum(1);
  return *this;
}

// postfix increment
LargeNum LargeNum::operator++(int) {
  LargeNum copy(*this);
  *this = *this + LargeNum(1);
  return copy;
}

// prefix decrement
LargeNum &LargeNum::operator--() {

  if (isZero()) {
    *this = LargeNum(-1);
    return *this;
  }
  if (!isPositive) {
    this->num = (*this + LargeNum(-1)).num;
    return *this;
  }
  *this = *this - LargeNum(1);
  return *this;
}

// postfix decrement
LargeNum LargeNum::operator--(int) {
  LargeNum copy(*this);
  *this = *this - LargeNum(1);
  return copy;
}