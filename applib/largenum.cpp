#include "largenum.h"
#include <algorithm>
#include <cassert>
#include <exception>
#include <iostream>
#include <math.h>
#include <string>

#include <vector>

using namespace std;

// Your code goes here
LargeNum::LargeNum(const string &str) { this->init(str); }
// constructor from int
LargeNum::LargeNum(int anInteger) { init(to_string(anInteger)); }

void LargeNum::init(const string &str) {
  if (str.length() == 0) {
    number = vector<int>(1, 0);
  } else {
    int count = 0;
    if (str[0] == '-' || str[0] == '+') {
      isNeg = str[0] == '-';
      count++;
    }
    if (count == str.length()) {
      throw invalid_argument("no numbers in string");
    }

    number = vector<int>(str.length() - count, 0);
    int index = 0;
    for (; count < str.length(); count++) {
      if (isdigit(str[count]) == 1) {
        this->number[index] = str[count] - '0';
      } else {
        throw invalid_argument(string("Invalid character at index ") +
                               to_string(count));
      }

      index++;
    }
  }
}

// returns true if the number is zero
bool LargeNum::isZero() const { return number.size() == 1 && number[0] == 0; }

// negate the number, positive becomes negative, negative becomes positive
// Zero is always positive
LargeNum &LargeNum::negate() {
  if (number.size() > 1 || number[0] > 0) {
    isNeg = !isNeg;
  }

  return *this;
}

// add two numbers
LargeNum LargeNum::operator+(const LargeNum &rhs) const {
  if (number == rhs.number && isNeg != rhs.isNeg) {
    return LargeNum(0);
  }
  if (!isNeg && rhs.isNeg) {
    LargeNum other = rhs;
    other.negate();
    return *this - other;
  }
  if (isNeg && !rhs.isNeg) {
    LargeNum other = *this;
    other.negate();
    return rhs - other;
  }

  int rightIndex = 0;
  int otherIndex = 0;
  int rem = 0;
  bool leftShorter = rhs.number.size() > this->number.size();
  LargeNum rightNum = leftShorter ? rhs : *this;
  LargeNum otherNum = leftShorter ? *this : rhs;

  rightIndex = static_cast<int>(rightNum.number.size() - 1);
  otherIndex = static_cast<int>(otherNum.number.size() - 1);
  while (rightIndex >= 0) {
    int sum = rem + rightNum.number[rightIndex];
    if (otherIndex >= 0) {
      sum += otherNum.number[otherIndex];
      otherIndex--;
    }
    rightNum.number[rightIndex] = sum % 10;
    rem = sum / 10;
    rightIndex--;
  }
  if (rem > 0) {
    rightNum.number.insert(rightNum.number.begin(), rem);
  } else if (rightNum.number[0] == 0) {
    rightNum.number.erase(rightNum.number.begin());
  }

  rightNum.isNeg = isNeg;

  return rightNum;
}

// subtract two numbers
LargeNum LargeNum::operator-(const LargeNum &rhs) const {
  if (this->number == rhs.number && this->isNeg == rhs.isNeg) {
    return LargeNum(0);
  }
  if (isNeg && !rhs.isNeg) {
    LargeNum other = rhs;
    other.negate();
    return *this + other;
  }
  if (!isNeg && rhs.isNeg) {
    LargeNum other = rhs;
    other.negate();
    return *this + other;
  }

  int rightIndex = 0;
  int otherIndex = 0;
  int borrow = 0;
  bool leftShorter = rhs.number.size() > this->number.size();
  LargeNum rightNum = leftShorter ? rhs : *this;
  LargeNum other = leftShorter ? *this : rhs;

  if (leftShorter) {
    rightNum.negate();
    other.negate();
  }

  rightIndex = static_cast<int>(rightNum.number.size() - 1);
  otherIndex = static_cast<int>(other.number.size() - 1);
  while (rightIndex >= 0) {
    int sum = borrow + rightNum.number[rightIndex];
    if (otherIndex >= 0) {
      sum = sum - other.number[otherIndex];
      otherIndex--;
    }
    if (sum < 0) {
      if (rightIndex > 0) {
        rightNum.number[rightIndex] = sum + 10;
      } else {
        rightNum.number[rightIndex] = abs(sum);
      }

      borrow = -1;
    } else {
      rightNum.number[rightIndex] = abs(sum);
      borrow = 0;
    }

    rightIndex--;
  }
  if (borrow < 0) {
    rightNum.isNeg = true;
  } else {
    rightNum.isNeg = isNeg;
  }
  if (rightNum.number[0] == 0) {
    rightNum.number.erase(rightNum.number.begin());
  }

  if (leftShorter) {
    rightNum.isNeg = !rightNum.isNeg;
  }

  return rightNum;
}

// multiply two numbers
LargeNum LargeNum::operator*(const LargeNum &rhs) const {
  if (this->isZero() || rhs.isZero()) {
    return LargeNum(0);
  }

  int rem = 0;

  bool leftShorter = rhs.number.size() > this->number.size();
  LargeNum bottom = leftShorter ? *this : rhs;
  LargeNum top = leftShorter ? rhs : *this;
  vector<LargeNum> rows(bottom.number.size());

  for (int j = static_cast<int>(bottom.number.size() - 1); j >= 0; j--) {
    rows[j] = LargeNum(0);
    rows[j].number.resize(top.number.size() + 1);

    int index = static_cast<int>(rows[j].number.size() - 1);
    for (int k = static_cast<int>(top.number.size() - 1); k >= 0; k--) {
      int prod = rem + top.number[k] * bottom.number[j];
      rows[j].number[index] = prod % 10;
      rem = prod / 10;
      index--;
    }
    if (rem > 0) {
      rows[j].number[0] = rem;
    } else if (rows[j].number[0] == 0) {
      rows[j].number.erase(rows[j].number.begin());
    }

    if (j < bottom.number.size() - 1) {
      rows[j].number.push_back(0);
    }
  }
  LargeNum result = rows[0];
  for (int k = 1; k < rows.size(); k++) {
    result = result + rows[k];
  }
  result.isNeg = this->isNeg != rhs.isNeg;
  return result;
}

// divide two numbers. rhs is the divisor
// similar to integer division, ignore remainder
LargeNum LargeNum::operator/(const LargeNum &rhs) const {
  if (rhs.isZero()) {
    throw overflow_error("Divide by zero.");
  }
  LargeNum tally = *this;
  LargeNum other = rhs;
  tally.isNeg = false;
  other.isNeg = false;
  int count = 0;
  while (tally >= other) {
    tally = tally - other;
    count++;
  }
  LargeNum result(count);
  result.isNeg = isNeg != rhs.isNeg;
  return result;
}

// return true if the numbers are equal
bool LargeNum::operator==(const LargeNum &rhs) const {
  return this->isNeg == rhs.isNeg && this->number == rhs.number;
}

// return true if the numbers are not equal
bool LargeNum::operator!=(const LargeNum &rhs) const { return !(*this == rhs); }

// return true if the left-hand-side number is less than the
// right-hand-side number
bool LargeNum::operator<(const LargeNum &rhs) const {
  bool result;
  if (isNeg && !rhs.isNeg) {
    return true;
  }
  if (!this->isNeg && rhs.isNeg) {
    return false;
  }
  if (this->number.size() == rhs.number.size()) {
    int index = 0;
    while (index < this->number.size() &&
           this->number[index] == rhs.number[index]) {
      index++;
    }
    if (index < this->number.size()) {
      result = this->number[index] < rhs.number[index];
    } else {
      result = false;
    }
  } else {
    result = this->number.size() < rhs.number.size();
  }

  if (this->isNeg) {
    return !result;
  }
  return result;
}

// return true if the left-hand-side number is greater than the
// right-hand-side number
bool LargeNum::operator>(const LargeNum &rhs) const { return rhs < *this; }

// return true if the left-hand-side number is less than or equal to the
// right-hand-side number
bool LargeNum::operator<=(const LargeNum &rhs) const {
  return *this == rhs || *this < rhs;
}

// return true if the left-hand-side number is greater than or equal to the
// right-hand-side number
bool LargeNum::operator>=(const LargeNum &rhs) const {
  return *this == rhs || *this > rhs;
}

// prefix increment
LargeNum &LargeNum::operator++() {
  LargeNum temp(1);
  *this = *this + temp;
  return *this;
}

// postfix increment
LargeNum LargeNum::operator++(int) {
  LargeNum temp = *this;
  ++*this;
  return temp;
}

// prefix decrement
LargeNum &LargeNum::operator--() {
  LargeNum temp(-1);
  *this = *this + temp;
  return *this;
}

// postfix decrement
LargeNum LargeNum::operator--(int) {
  LargeNum temp = *this;
  --*this;
  return temp;
}

ostream &operator<<(ostream &out, const LargeNum &num) {
  // 1,234,567,890,123,456,789
  int index = 0;
  if (num.isNeg) {
    out << '-';
  }
  while (index < num.number.size()) {
    if (index > 0 && (num.number.size() - index) % 3 == 0) {
      out << ',';
    }
    out << num.number[index];

    index++;
  }
  return out;
}
