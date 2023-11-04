#include "largenum.h"
#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

// Your code goes here

// Outputs the large number with a comma after every 3 digits
ostream &operator<<(ostream &out, const LargeNum &num) {
  // for a negative number
  if (!num.isPositive) {
    out << "-";
  }

  for (int i = static_cast<int>(num.largeNum.length() - 1); i >= 0; i--) {
    if (i % 3 == 0 && i != 0) {
      out << num.largeNum[i] << ",";
    } else {
      out << num.largeNum[i];
    }
  }
  return out;
}

// Private helper method to internally store the large number string in reverse
// order.
void LargeNum::reverseString() {
  for (int i = 0; i < largeNum.length() / 2; i++) {
    char temp = largeNum[i];
    largeNum[i] = largeNum[largeNum.length() - i - 1];
    largeNum[largeNum.length() - i - 1] = temp;
  }
}

// Constructor for a string parameter or a default constructor that will set the
// internal string to the number 0
LargeNum::LargeNum(const string &str) : largeNum(str) {
  // makes sure to only have digits in the string, no negative sign
  if (largeNum[0] == '-') {
    largeNum.erase(largeNum.begin());
    isPositive = false;
  }
  reverseString();
}

// Constructor for a int parameter
LargeNum::LargeNum(int anInteger) {
  // makes sure to only have digits in the string, no negative sign
  largeNum = anInteger == 0 ? "0" : to_string(anInteger);
  if (largeNum[0] == '-' || anInteger < 0) {
    largeNum.erase(largeNum.begin());
    isPositive = false;
  }
  reverseString();
}

// Returns true if the number is zero
bool LargeNum::isZero() const { return largeNum == "0"; }

// Negates the number, so positive becomes negative and negative becomes
// positive. But zero will always remain positive.
LargeNum &LargeNum::negate() {
  isPositive = !(isPositive);
  if (isZero()) {
    isPositive = true;
  }
  return *this;
}

// Plus operator overload to add two LargeNum objects
LargeNum LargeNum::operator+(const LargeNum &rhs) const {
  // a + (-b) = a - b
  if (isPositive && !rhs.isPositive) {
    LargeNum negatedNum = rhs;
    negatedNum.negate();
    return *this - negatedNum;
  }
  // -a + b = b - a
  if (!isPositive && rhs.isPositive) {
    LargeNum negatedNum(largeNum);
    negatedNum.reverseString();
    return rhs - negatedNum;
  }

  int carry = 0;
  string number;
  // loops to the bigger number
  int biggerNum = largeNum.length() > rhs.largeNum.length()
                      ? static_cast<int>(largeNum.length())
                      : static_cast<int>(rhs.largeNum.length());

  for (int i = 0; i < biggerNum; i++) {
    // makes sure for no invalid index accessing
    int num1 = i >= largeNum.length() ? 0 : (largeNum[i] - '0');
    int num2 = i >= rhs.largeNum.length() ? 0 : (rhs.largeNum[i] - '0');
    int sum = carry + num1 + num2;

    // to handle carry-overs
    if (sum > 9) {
      sum %= 10;
      number.push_back(static_cast<char>(sum + '0'));
      carry = 1;
    } else {
      number.push_back(static_cast<char>(sum + '0'));
      carry = 0;
    }
  }

  if (carry == 1) {
    number.push_back('1');
  }

  // gets rid of leading zeros
  while (number.length() > 1 && number.back() == '0') {
    number.pop_back();
  }

  LargeNum newNumber(number);
  newNumber.reverseString();

  // -a + -b = -(a+b)
  if (!isPositive && !rhs.isPositive) {
    newNumber.negate();
  }
  return newNumber;
}

// Subtraction operator overload to subtract two LargeNum objects
LargeNum LargeNum::operator-(const LargeNum &rhs) const {
  // a - (-b) = a + b
  if (isPositive && !rhs.isPositive) {
    LargeNum negatedNum = rhs;
    negatedNum.negate();
    return *this + negatedNum;
  }
  // -a - b = -(a + b)
  if (!isPositive && rhs.isPositive) {
    LargeNum negatedNum = *this;
    negatedNum.negate();
    LargeNum difference = negatedNum + rhs;
    difference.negate();
    return difference;
  }
  // -a - (-b) = -a + b
  if (!isPositive && !rhs.isPositive) {
    LargeNum negatedNum = rhs;
    negatedNum.negate();
    return *this + negatedNum;
  }

  int help = 0;
  string number;
  // loops to the bigger number
  int biggerLength = largeNum.length() > rhs.largeNum.length()
                         ? static_cast<int>(largeNum.length())
                         : static_cast<int>(rhs.largeNum.length());

  // stores biggest and smallest number for proper condition check in the loop
  string biggerNum = *this > rhs ? largeNum : rhs.largeNum;
  string smallerNum = *this < rhs ? largeNum : rhs.largeNum;

  for (int i = 0; i < biggerLength; i++) {
    int num1 = (i >= biggerNum.length() ? 0 : biggerNum[i] - '0') - help;
    int num2 = (i >= smallerNum.length() ? 0 : smallerNum[i] - '0');

    if (num1 < num2) {
      num1 += 10;
      // need to borrow from the next digit
      help = 1;
    } else {
      help = 0;
    }

    int difference = num1 - num2;
    number.push_back(static_cast<char>(difference + '0'));
  }

  // gets rid of leading zeros
  while (number.length() > 1 && number.back() == '0') {
    number.pop_back();
  }

  LargeNum newNumber(number);
  // if a < b, then a - b = -(b - a)
  if (*this < rhs) {
    newNumber.negate();
  }
  newNumber.reverseString();
  return newNumber;
}

// Multiplication operator overload to multiply two LargNum objects
LargeNum LargeNum::operator*(const LargeNum &rhs) const {
  // finds smaller number and loops to it from 1 to smaller number
  LargeNum smallerNum = *this < rhs ? *this : rhs;
  LargeNum biggerNum = *this > rhs ? *this : rhs;
  LargeNum product(0);

  // is smaller number is positive, then loop from 0 to smallerNum - 1
  if (smallerNum.isPositive) {
    LargeNum iterator(0);
    while (iterator < smallerNum) {
      product = product + biggerNum;
      ++iterator;
    }
  } else {
    // since the smaller number is negative, have to make bigger number positive
    biggerNum.negate();
    LargeNum iterator = smallerNum;
    // loops from the smaller number to 0
    while (LargeNum(0) > iterator) {
      product = product + biggerNum;
      ++iterator;
    }
  }

  return product;
}

// Divison operator overload to divide two LargeNum objects. Works like C++
// integer divison, ignores remainder.
LargeNum LargeNum::operator/(const LargeNum &rhs) const {
  // can just return 0 if its 0 / rhs
  if (largeNum == "0") {
    return LargeNum(0);
  }

  // can't divide by 0, so an error message is sent and 0 is returned.
  if (rhs.largeNum == "0") {
    cerr << "Error: Cannot divide by 0";
    return LargeNum(0);
  }

  LargeNum numerator = *this;
  LargeNum denominator = rhs;
  LargeNum quotient(0);

  // makes sure both numerator and denominator are positive before looping
  if (!numerator.isPositive) {
    numerator.negate();
  }
  if (!denominator.isPositive) {
    denominator.negate();
  }

  while (numerator >= denominator) {
    numerator = numerator - denominator;
    ++quotient;
  }

  // if one of the digits is negative, then the result will also be negative
  if (isPositive != rhs.isPositive) {
    quotient.negate();
  }
  return quotient;
}

// Returns true if the LargeNum objects are equal in terms of their number.
bool LargeNum::operator==(const LargeNum &rhs) const {
  // if the two numbers are both negative or both positive, then we can just
  // check if their internal strings are the same.
  if (isPositive == rhs.isPositive) {
    return largeNum == rhs.largeNum;
  }
  return false;
}

// Return true if the LargeNum objects are not equal in terms of their number.
bool LargeNum::operator!=(const LargeNum &rhs) const { return !(*this == rhs); }

// Private helper to determine which string is greater by comparing each digit
// Condition is that strings are of equal length, but this method is only called
// when the strings are equal. returns 1 if str1 is greater than str2 returns 0
// if the strings (which is a number) are the same returns -1 if str1 is less
// than str2
int LargeNum::compareStrings(const string &str1, const string &str2) {
  if (str1 == str2) {
    return 0;
  }
  for (int i = static_cast<int>(str1.length() - 1); i >= 0; i--) {
    if (str1[i] > str2[i]) {
      return 1;
    }
    if (str1[i] < str2[i]) {
      break;
    }
  }
  return -1;
}

// Return trues if the left-hand-side number (*this) is less than the
// right-hand-side number (rhs)
bool LargeNum::operator<(const LargeNum &rhs) const {
  // false since positive will always be greater than negative
  if (isPositive && !rhs.isPositive) {
    return false;
  }
  // truen since negative will always be less than positive
  if (!isPositive && rhs.isPositive) {
    return true;
  }

  // to handle two positives
  if (isPositive && rhs.isPositive) {
    // numbers are equal
    if (largeNum == rhs.largeNum) {
      return false;
    }
    if (largeNum.length() > rhs.largeNum.length()) {
      return false;
    }
    if (largeNum.length() < rhs.largeNum.length()) {
      return true;
    }
    // true if largeNum is less than rhs.largeNum
    return compareStrings(largeNum, rhs.largeNum) == -1;
  }
  // to handle two negatives
  if (largeNum.length() > rhs.largeNum.length()) {
    return true;
  }
  if (largeNum.length() < rhs.largeNum.length()) {
    return false;
  }
  return *this > rhs;
}

// Returns true if the left-hand-side number (*this) is greater than the
// right-hand-side number (rhs)
bool LargeNum::operator>(const LargeNum &rhs) const {
  // if both are negatives or both are positives, we can check the length of
  // their internal strings. if the length of largeNum is greater, then *this is
  // greater than rhs
  if (isPositive == rhs.isPositive &&
      largeNum.length() == rhs.largeNum.length()) {
    return compareStrings(largeNum, rhs.largeNum) == 1;
  }
  return !(*this < rhs);
}

// Returns true if the left-hand-side (*this) number is less than or equal to
// the right-hand-side number (rhs)
bool LargeNum::operator<=(const LargeNum &rhs) const {
  return *this < rhs || *this == rhs;
}

// Returns true if the left-hand-side number (*this) is greater than or equal to
// the right-hand-side number (rhs)
bool LargeNum::operator>=(const LargeNum &rhs) const {
  return *this > rhs || *this == rhs;
}

// Prefix increment
LargeNum &LargeNum::operator++() {
  LargeNum one("1");
  *this = *this + one;
  return *this;
}

// Postfix increment
LargeNum LargeNum::operator++(int) {
  LargeNum num = *this;
  LargeNum one("1");
  *this = *this + one;
  return num;
}

// Prefix decrement
LargeNum &LargeNum::operator--() {
  LargeNum one("-1");
  *this = *this + one;
  return *this;
}

// Postfix decrement
LargeNum LargeNum::operator--(int) {
  LargeNum num = *this;
  LargeNum one("-1");
  *this = *this + one;
  return num;
}