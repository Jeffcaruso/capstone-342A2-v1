#include "largenum.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

// Overloaded << operator to print LargeNum
ostream &operator<<(ostream &out, const LargeNum &num) {
  std::string str = num.number;
  int size = static_cast<int>(num.number.size());
  for (int i = size - 3; i > 0; i -= 3) {
    str.insert(static_cast<std::string::size_type>(i), 1, ',');
  }
  if (!num.isPositive) {
    str = '-' + str;
  }
  out << str;
  return out;
}

// Constructor that initializes a LargeNum from a string
LargeNum::LargeNum(const string &str) {
  if (str[0] == '-') {
    number = str;
    isPositive = false;
    number.erase(0, 1);
  } else {
    number = str;
  }
}

// Constructor that initializes a LargeNum from an integer
LargeNum::LargeNum(int anInteger) {
  if (anInteger < 0) {
    isPositive = false;
    anInteger *= -1;
  }
  number = to_string(anInteger);
}

// Check if the LargeNum is zero
bool LargeNum::isZero() const {
  bool isZero = false;
  if (number == "0") {
    isZero = true;
  }
  return isZero;
}

// Negate the sign of the LargeNum (positive to negative and vice versa)
LargeNum &LargeNum::negate() {
  if (number == "0") {
    isPositive = true;
    return *this;
  }
  if (isPositive) {
    isPositive = false;
    return *this;
  }
  isPositive = true;
  return *this;
}

// Overloaded + operator for adding LargeNum objects
LargeNum LargeNum::operator+(const LargeNum &rhs) const {
  if ((isPositive && rhs.isPositive) || (!isPositive && !rhs.isPositive)) {
    string number1 = number;
    string number2 = rhs.number;
    int num = 0;
    string sum;
    while (number1.size() > number2.size()) {
      number2 = '0' + number2;
    }
    while (number1.size() < number2.size()) {
      number1 = '0' + number1;
    }
    for (std::string::size_type i = number1.size() - 1;
         i != static_cast<std::string::size_type>(-1); i--) {
      num = (number1[i] - '0') + (number2[i] - '0') + num;
      sum = static_cast<char>((num % 10) + '0') + sum;
      num /= 10;
    }
    if (num == 1) {
      sum = '1' + sum;
    }
    if (!(isPositive && rhs.isPositive)) {
      return LargeNum(sum).negate();
    }
    return LargeNum(sum);
  }
  if (isPositive && !rhs.isPositive) {
    LargeNum negatedRhs = rhs;
    negatedRhs.negate();
    return *this - negatedRhs;
  }
  LargeNum negatedCur = *this;
  negatedCur.negate();
  return rhs - negatedCur;
}

// Overloaded - operator for subtracting LargeNum objects
LargeNum LargeNum::operator-(const LargeNum &rhs) const {
  if (isPositive && rhs.isPositive) {
    std::string number1 = number;
    std::string number2 = rhs.number;
    bool flipped = false;
    if (*this < rhs) {
      number1 = rhs.number;
      number2 = number;
      flipped = true;
    }
    std::string difference;
    int num = 0;
    while (number1.size() > number2.size()) {
      number2 = '0' + number2;
    }
    while (number1.size() < number2.size()) {
      number1 = '0' + number1;
    }
    for (std::string::size_type i = number1.size() - 1;
         i != static_cast<std::string::size_type>(-1); i--) {
      int digit1 = number1[i] - '0';
      int digit2 = number2[i] - '0';
      int tempDiff = digit1 - digit2 - num;

      if (tempDiff < 0) {
        tempDiff += 10;
        num = 1;
      } else {
        num = 0;
      }
      difference = static_cast<char>(tempDiff + '0') + difference;
    }
    difference.erase(
        0, std::min(difference.find_first_not_of('0'), difference.size() - 1));
    if (difference.empty()) {
      difference = "0";
    }
    if (flipped) {
      return LargeNum(difference).negate();
    }
    return LargeNum(difference);
  }
  if (isPositive && !rhs.isPositive) {
    LargeNum negatedRhs = rhs;
    negatedRhs.negate();
    return *this + negatedRhs;
  }
  if (!isPositive && rhs.isPositive) {
    LargeNum negatedThis = rhs;
    negatedThis.negate();
    return *this + negatedThis;
  }
  LargeNum negatedRhs = rhs;
  negatedRhs.negate();
  LargeNum result = *this + negatedRhs;
  return result;
}

// Overloaded * operator for multiplying LargeNum objects
LargeNum LargeNum::operator*(const LargeNum &rhs) const {
  LargeNum result("0");
  if (isPositive && rhs.isPositive) {
    LargeNum number1(*this);
    LargeNum number2(rhs);
    while (number2.number != "0") {
      result = result + number1;
      number2 = number2 - LargeNum("1");
    }
    return result;
  }
  if (!isPositive && !rhs.isPositive) {
    LargeNum negatedRhs = rhs;
    negatedRhs.negate();
    LargeNum negated = *this;
    negated.negate();
    return negatedRhs * negated;
  }
  LargeNum negated;
  LargeNum negatedRhs;
  if (!isPositive) {
    negated = *this;
    negated.negate();
    negatedRhs = rhs;
  } else {
    negatedRhs = rhs;
    negatedRhs.negate();
    negated = *this;
  }
  return (negatedRhs * negated).negate();
}

// Overloaded / operator for dividing LargeNum objects
LargeNum LargeNum::operator/(const LargeNum &rhs) const {
  if (isPositive && rhs.isPositive) {
    LargeNum result("0");
    LargeNum number1(*this);
    LargeNum number2(rhs);
    if (number1 == result || number1 < number2) {
      return result;
    }
    while (number1 != LargeNum("0")) {
      number1 = number1 - number2;
      result = result + LargeNum("1");
      if (number1 < number2) {
        return result;
      }
    }
    return result;
  }
  if (!isPositive && !rhs.isPositive) {
    LargeNum negatedRhs = rhs;
    negatedRhs.negate();
    LargeNum negated = *this;
    negated.negate();
    return negated / negatedRhs;
  }
  LargeNum negated;
  LargeNum negatedRhs;
  if (!isPositive) {
    negated = *this;
    negated.negate();
    negatedRhs = rhs;
  } else {
    negatedRhs = rhs;
    negatedRhs.negate();
    negated = *this;
  }
  return (negated / negatedRhs).negate();
}

// Overloaded == operator to check equality between LargeNum objects
bool LargeNum::operator==(const LargeNum &rhs) const {
  bool same = false;
  if (number == rhs.number && isPositive == rhs.isPositive) {
    same = true;
  }
  return same;
}

// Overloaded != operator to check inequality between LargeNum objects
bool LargeNum::operator!=(const LargeNum &rhs) const {
  bool different = false;
  if (number != rhs.number || isPositive != rhs.isPositive) {
    different = true;
  }
  return different;
}

// Overloaded < operator to check if this LargeNum is less than another
bool LargeNum::operator<(const LargeNum &rhs) const {
  if (!isPositive && !rhs.isPositive) {
    LargeNum negated = *this;
    negated.negate();
    LargeNum negatedRhs = rhs;
    negatedRhs.negate();
    return negated > negatedRhs;
  }
  bool lessThan = false;
  if (!isPositive && rhs.isPositive) {
    return true;
  }
  if (isPositive && !rhs.isPositive) {
    return false;
  }
  if (number.size() < rhs.number.size()) {
    lessThan = true;
  } else if (number.size() == rhs.number.size()) {
    for (int i = 0; i < number.size(); i++) {
      int first = number[i] - '0';
      int second = rhs.number[i] - '0';
      if (first < second) {
        return true;
      }
      if (first > second) {
        return false;
      }
    }
  }
  return lessThan;
}

// Overloaded > operator to check if this LargeNum is greater than another
bool LargeNum::operator>(const LargeNum &rhs) const {
  if (!isPositive && !rhs.isPositive) {
    LargeNum negated = *this;
    negated.negate();
    LargeNum negatedRhs = rhs;
    negatedRhs.negate();
    return negated < negatedRhs;
  }
  bool greaterThan = false;
  if (isPositive && !rhs.isPositive) {
    return true;
  }
  if (!isPositive && rhs.isPositive) {
    return false;
  }
  if (number.size() > rhs.number.size()) {
    greaterThan = true;
  } else if (number.size() == rhs.number.size()) {
    for (int i = 0; i < number.size(); i++) {
      int first = number[i] - '0';
      int second = rhs.number[i] - '0';
      if (first > second) {
        return true;
      }
      if (first > second) {
        return false;
      }
    }
  }
  return greaterThan;
}

// Overloaded <= operator to check if this LargeNum is less than or equal to
// another
bool LargeNum::operator<=(const LargeNum &rhs) const {
  bool lte = false;
  if (*this < rhs || *this == rhs) {
    lte = true;
  }
  return lte;
}

// Overloaded >= operator to check if this LargeNum is greater than or equal to
// another
bool LargeNum::operator>=(const LargeNum &rhs) const {
  bool gte;
  if (*this > rhs || *this == rhs) {
    gte = true;
  }
  return gte;
}

// Prefix increment operator
LargeNum &LargeNum::operator++() {
  *this = *this + LargeNum("1");
  return *this;
}

// Postfix increment operator
LargeNum LargeNum::operator++(int) {
  LargeNum postInc = *this;
  *this = *this + LargeNum("1");
  return LargeNum(postInc);
}

// Prefix decrement operator
LargeNum &LargeNum::operator--() {
  *this = *this - LargeNum("1");
  return *this;
}

// Postfix decrement operator
LargeNum LargeNum::operator--(int) {
  LargeNum postDec = *this;
  *this = *this - LargeNum("1");
  return LargeNum(postDec);
}
