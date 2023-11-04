/*
 *  largenum.cpp
 *
 *  Created by Amy Vier
 *
 *  Updated on Oct. 22, 2023
 */

#include "largenum.h"
#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

/**
 * Creates printable number
 *
 * @param out ostream
 * @param num LargeNum
 *
 * @return ostream printable number
 */
ostream &operator<<(ostream &out, const LargeNum &num) {
  int threes = 0; // counts number of digits until comma
  int numberLength =
      static_cast<int>((num.number).length()); // length of string number
  string printNumber;                          // number with commas

  // add commas to number
  for (int i = numberLength - 1; i >= 0; i--) {
    if (threes == 3) {
      printNumber = "," + printNumber;
      threes = 0;
    }

    printNumber = num.number[i] + printNumber;
    threes++;
  }

  // add negative sign
  if (num.negative) {
    out << "-";
  }

  // add number
  out << printNumber;

  return out;
}

/**
 *  LargeNum constructor: create LargeNum of default value 0 or the
 *  value inputted, assuming that the string inputted is valid
 *  (no 00012 or --23 or ab32)
 *
 * @param str string value of LargeNum
 */
LargeNum::LargeNum(const string &str) {
  // assuming that there is a number after a negative sign
  if (str[0] == '-' && str[1] != '0') {
    number = str.substr(1, str.length() - 1);
    negative = true;
  }
  // not a negative
  else {
    number = str;
    negative = false;
  }
}

/**
 *  LargeNum constructor: create LargeNum of value inputted
 *
 * @param anInteger int value of LargeNum
 */
LargeNum::LargeNum(int anInteger) {
  // check for negatives
  if (anInteger < 0) {
    number = to_string(anInteger * -1);
    negative = true;
  }
  // not a negative
  else {
    number = to_string(anInteger);
    negative = false;
  }
}

/**
 * Shows whether then number is negative or not
 *
 * @return bool whether then number is negative or not
 */
bool LargeNum::isZero() const { return number == "0"; }

/**
 * Makes positives negatives and negatives positives
 */
LargeNum &LargeNum::negate() {
  // zeros are always positive
  if (isZero()) {
    return *this;
  }

  // any other number
  negative = !negative;

  return *this;
}

/**
 * Adds numbers
 *
 * @param rhs LargeNum right hand side number
 *
 * @return LargeNum added number
 */
LargeNum LargeNum::operator+(const LargeNum &rhs) const {
  LargeNum newNum; // new large number

  // if both numbers have same positive/negative signs they add
  if (negative == rhs.negative) {
    newNum.number = add(number, rhs.number);
    newNum.negative = negative;
  }
  // if both numbers don't have same positive/negative signs and are the same,
  // they subtract to zero
  else if (number == rhs.number) {
    newNum.number = "0";
    newNum.negative = false;
  }
  // if both numbers don't have same positive/negative signs, they subtract
  else {
    newNum.number = subtract(number, rhs.number);

    // smaller positive + bigger negative = negative number
    // bigger negative + smaller positive = positive number
    newNum.negative = (less(number, rhs.number) && negative) ||
                              (less(rhs.number, number) && rhs.negative)
                          ? false
                          : true;
  }

  return newNum;
}

/**
 * Adds numbers, ignoring negatives
 *
 * @param lhs left hand side number
 * @param rhs right hand side number
 *
 * @return string added number
 */
string LargeNum::add(string lhs, string rhs) {
  string smallerString = less(lhs, rhs) ? lhs : rhs;    // smaller number
  string greaterString = !(less(lhs, rhs)) ? lhs : rhs; // greater number
  int smallerStringLength = static_cast<int>(smallerString.length());
  int greaterStringLength = static_cast<int>(greaterString.length());

  int carry = 0;    // if a one is carried over to the next digit
  string newNumber; // new added number

  // add up both digits in both of the numbers starting at the oneth place
  for (int i = 1; i <= smallerStringLength; i++) {
    int digit = (smallerString[smallerStringLength - i] - '0') + carry +
                (greaterString[greaterStringLength - i] - '0');

    // if digit is more than nine, carry the one over
    carry = digit > 9 ? 1 : 0;
    digit = digit > 9 ? digit - 10 : digit;

    // add added digit to number
    newNumber = to_string(digit) + newNumber;
  }

  // now add what is carried over from the previous loop of addition to the
  // remaining digits of the greater number
  for (int i = smallerStringLength + 1; i <= greaterStringLength; i++) {
    int digit = (greaterString[greaterStringLength - i] - '0') + carry;

    // if digit is more than nine, carry the one over
    carry = digit > 9 ? 1 : 0;
    digit = digit > 9 ? digit - 10 : digit;

    // add added digit to number
    newNumber = to_string(digit) + newNumber;
  }

  // if there still is a carried one, add one to the end of the number
  if (carry > 0) {
    newNumber = "1" + newNumber;
  }

  return newNumber;
}

/**
 * Subtracts numbers
 *
 * @param rhs Largenum right hand side number
 *
 * @return Largenum subtracted number
 */
LargeNum LargeNum::operator-(const LargeNum &rhs) const {
  LargeNum newNum; // new large number

  // if both numbers don't have same positive/negative signs, they add
  if (negative != rhs.negative) {
    newNum.number = add(number, rhs.number);
    newNum.negative = negative;
  }
  // if both numbers have same positive/negative signs and are the same,
  // they subtract to zero
  else if (number == rhs.number) {
    newNum.number = "0";
    newNum.negative = false;
  } else {
    newNum.number = subtract(number, rhs.number);

    // bigger negative - smaller negative = negative number
    // bigger positive - smaller positive = positive number
    newNum.negative = (less(number, rhs.number) && negative) ||
                              (less(rhs.number, number) && !(negative))
                          ? false
                          : true;
  }

  return newNum;
}

/**
 * Subtracts numbers, ignoring negatives
 *
 * @param lhs string left hand side number
 * @param rhs string right hand side number
 *
 * @return string subtracted number
 */
string LargeNum::subtract(string lhs, string rhs) {
  string greaterString = !(less(lhs, rhs)) ? lhs : rhs; // the greater number
  string smallerString = less(lhs, rhs) ? lhs : rhs;    // the smaller number

  string newNumber; // new subtracted number

  // if equal, subtracts to zero
  if (lhs == rhs) {
    return "0";
  }

  // subtract bigger number by smaller number
  for (int i = 1; i <= smallerString.length(); i++) {
    int digit; // current subtracted digit

    // if smaller - bigger creates a negative number, borrow a one from the
    // next digit in the big number
    if ((greaterString[greaterString.length() - i] - '0') <
        (smallerString[smallerString.length() - i] - '0')) {

      // digit to borrow one from
      int borrow = static_cast<int>(greaterString.length()) - i - 1;

      // if the digit cannot be borrowed from, find next digit
      while ((greaterString[borrow] - '0') == 0) {
        borrow = borrow - 1;
      }

      // create a string containing digits changed by borrowing
      string changedPart = to_string((greaterString[borrow] - '0') - 1);
      int borrowChange = borrow; // index of digits changed from this borrow

      // for each number borrowed from, subtract one. For each borrowing number,
      // add by ten
      while (borrowChange + 1 != greaterString.length() - i) {
        changedPart =
            changedPart +
            (to_string((greaterString[++borrowChange] - '0') + 10 - 1));
      }

      // add borrowing number by 10 and subtract with digit from smaller number
      digit = 10 + (greaterString[greaterString.length() - i] - '0') -
              (smallerString[smallerString.length() - i] - '0');

      // add subtracted digit to new number
      newNumber = to_string(digit) + newNumber;

      // update greater number from the borrow
      greaterString = greaterString.substr(0, borrow) + changedPart + newNumber;
    }
    // if borrowing not necessary
    else {
      digit = (greaterString[greaterString.length() - i] - '0') -
              (smallerString[smallerString.length() - i] - '0');

      // add subtracted digit to new number
      newNumber = to_string(digit) + newNumber;
    }
  }

  // add rest of digits that the bigger number still has to new subtracted
  // number
  newNumber =
      greaterString.substr(0, greaterString.length() - smallerString.length()) +
      newNumber;

  // get rid of unecessary digits/zeros
  while (newNumber[0] == '0') {
    newNumber = newNumber.substr(1, newNumber.length() - 1);
  }

  return newNumber;
}

/**
 * Multiplies numbers
 *
 * @param rhs LargeNum right hand side number
 *
 * @return LargeNum multiplied number
 */
LargeNum LargeNum::operator*(const LargeNum &rhs) const {
  LargeNum newNum; // new multiplied number
  string multiplier =
      rhs.number; // number of times the number will be added to itself

  // zeros multiply to zero
  if (isZero() || rhs.isZero()) {
    newNum.number = "0";
    newNum.negative = false;

    return newNum;
  }

  // add number to itself
  while (multiplier != "0") {
    newNum = newNum + *this;

    multiplier = subtract(multiplier, "1");
  }

  // negative * positive = negative
  if (rhs.negative != negative) {
    newNum.negative = true;
  }
  // positive/negative * positive/negative = positive
  else {
    newNum.negative = false;
  }

  return newNum;
}

/**
 * Divides numbers
 *
 * @param rhs LargeNum right hand side number
 *
 * @return LargeNum divided number
 */
LargeNum LargeNum::operator/(const LargeNum &rhs) const {
  LargeNum newNum;           // new divided number
  string numChange = number; // number that will be constantly subtracted from
  string amount = "0"; // The amount of times the divided number is subtracted
  // from the divider shows the answer to dividing the divided number from the
  // divider

  // dividing zeros yields zeros
  if (isZero() || rhs.isZero()) {
    newNum.number = "0";
    newNum.negative = false;

    return newNum;
  }

  // subtract until the the divided number is less than the divider
  while (less(rhs.number, numChange) || numChange == rhs.number) {
    numChange = subtract(numChange, rhs.number);
    amount = add(amount, "1");
  }

  // LargeNum does not use decimal place, it rounds down just like an int
  newNum.number = amount;

  // negative / positive = negative
  if (rhs.negative != negative) {
    newNum.negative = true;
  }
  // positive/negative / positive/negative = positive
  else {
    newNum.negative = false;
  }

  return newNum;
}

/**
 * Sees if numbers are equal
 *
 * @param rhs LargeNum right hand side number
 *
 * @return bool whether the numbers are equal
 */
bool LargeNum::operator==(const LargeNum &rhs) const {

  // negatives are not equal to positives
  if (negative != rhs.negative) {
    return false;
  }

  // compare numbers themselves
  if (number != rhs.number) {
    return false;
  }

  return true;
}

/**
 * Sees if numbers are not equal
 *
 * @param rhs LargeNum right hand side number
 *
 * @return bool whether the numbers are not equal
 */
bool LargeNum::operator!=(const LargeNum &rhs) const { return !(rhs == *this); }

/**
 * Sees if the right hand side number is less
 * than the left hand side number
 *
 * @param rhs LargeNum right hand side number
 *
 * @return bool whether the right hand side number is less
 * than the left hand side number
 */
bool LargeNum::operator<(const LargeNum &rhs) const {
  bool isLess; // whether this number is less or not

  // negative is less than positives
  if (negative && !(rhs.negative)) {
    isLess = true;
  } else if (!(negative) && rhs.negative) {
    isLess = false;
  }
  // if the numbers are negative, the smaller numbers look bigger
  else if (negative && rhs.negative) {
    isLess = less(rhs.number, number);
  }
  // if the numbers are positive, the smaller numbers look smaller
  else {
    isLess = less(number, rhs.number);
  }

  return isLess;
}

/**
 * Sees if the right hand side number is less than or equal to
 * than the left hand side number
 *
 * @param rhs LargeNum right hand side number
 *
 * @return bool whether the right hand side number is less than or equal to
 * than the left hand side number
 */
bool LargeNum::operator<=(const LargeNum &rhs) const {
  return (*this == rhs) || (*this < rhs);
}

/**
 * Sees if the right hand side number is greater than or equal to
 * than the left hand side number
 *
 * @param rhs LargeNum right hand side number
 *
 * @return bool whether the right hand side number is greater than or equal to
 * than the left hand side number
 */
bool LargeNum::operator>=(const LargeNum &rhs) const {
  return (*this == rhs) || (*this > rhs);
}

/**
 * Sees if the potential smaller number is less than the potential
 * bigger number
 *
 * @param smaller string smaller number
 * @param bigger string bigger number
 *
 * @return bool whether the potential smaller number is less than the potential
 * bigger number
 */
bool LargeNum::less(string smaller, string bigger) {
  bool isLess; // whether the potential smaller number is smaller or not

  // if the bigger size is bigger, the bigger number is numerically greater
  if (smaller.length() < bigger.length()) {
    isLess = true;
  }
  // if equal or the bigger size is smaller, the smaller string is not
  // less than the bigger string
  else if (smaller.length() > bigger.length() || smaller == bigger) {
    isLess = false;
  }
  // go through all digits and compare starting from the biggest nth place
  else {
    isLess = true; // if all the digits of the bigger number are greater

    for (int i = 0; i < smaller.length(); i++) {
      if ((smaller[i] + '0') > (bigger[i] + '0')) {
        isLess = false;
      }
    }
  }

  return isLess;
}

/**
 * Sees if the right hand side number is greater
 * than the left hand side number
 *
 * @param rhs LargeNum right hand side number
 *
 * @return bool whether the right hand side number is greater
 * than the left hand side number
 */
bool LargeNum::operator>(const LargeNum &rhs) const {
  bool isGreater; // whether this number is greater or not

  // negative is less than positives
  if (negative && !(rhs.negative)) {
    isGreater = false;
  } else if (!(negative) && rhs.negative) {
    isGreater = true;
  }
  // if the numbers are negative, the smaller numbers look bigger
  else if (negative && rhs.negative) {
    isGreater = less(number, rhs.number);
  }
  // if the numbers are positive, the smaller numbers look smaller
  else {
    isGreater = less(rhs.number, number);
  }

  return isGreater;
}

/**
 * pre increments number
 */
LargeNum &LargeNum::operator++() {
  // increments
  *this = *this + LargeNum(1);

  return *this;
}

/**
 * post increments number
 */
LargeNum LargeNum::operator++(int dummy) {
  LargeNum copy = *this; // before increment

  // increments
  *this = *this + LargeNum(1);

  return copy;
}

/**
 * pre decrements number
 */
LargeNum &LargeNum::operator--() {
  // decrements
  *this = *this - LargeNum(1);

  return *this;
}

/**
 * post decrements number
 */
LargeNum LargeNum::operator--(int dummy) {
  LargeNum copy = *this; // before decrement

  // decrements
  *this = *this - LargeNum(1);

  return copy;
}