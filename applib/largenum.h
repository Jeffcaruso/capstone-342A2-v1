#include <iostream>

using namespace std;

class LargeNum {
  // output number with a comma after ever 3 digits,
  // e.g. 1234567890 -> 1,234,567,890
  friend ostream &operator<<(ostream &out, const LargeNum &num);

private:
  // stores the large num
  string largeNum;

  // represents if the largenum is pos/neg
  bool isPositive = true;

  // returns the larger LargeNum
  LargeNum getLargestNum(const LargeNum &rhs) const {
    if (*this > rhs) {
      return *this;
    }
    return rhs;
  }

  // returns the smaller LargeNum
  LargeNum getSmallestNum(const LargeNum &rhs) const {
    if (*this < rhs) {
      return *this;
    }
    return rhs;
  }

  static string removeLeadingZeros(string temp) {
    // remove leading zeros
    int index = temp.size() - 1;
    if (temp[index] == '0' && temp.size() > 1) {

      for (int j = temp.size() - 1; j > 0; j--) {
        if (temp[j] == '0') {
          temp.pop_back();
        }
      }
    }
    return temp;
  }

public:
  // default constructor from string
  // try to store it in reverse?
  explicit LargeNum(const string &str = "0");

  // constructor from int
  explicit LargeNum(int anInteger);

  // use the default copy constructor
  LargeNum(const LargeNum &other) = default;

  // use the default copy assignment operator
  LargeNum &operator=(const LargeNum &other) = default;

  // use the default destructor
  ~LargeNum() = default;

  // returns true if the number is zero
  bool isZero() const;

  // negate the number, positive becomes negative, negative becomes positive
  // Zero is always positive
  LargeNum &negate();

  // add two numbers
  LargeNum operator+(const LargeNum &rhs) const;

  // subtract two numbers
  LargeNum operator-(const LargeNum &rhs) const;

  // multiply two numbers
  LargeNum operator*(const LargeNum &rhs) const;

  // divide two numbers. rhs is the divisor
  // similar to integer division, ignore remainder
  LargeNum operator/(const LargeNum &rhs) const;

  // return true if the numbers are equal
  bool operator==(const LargeNum &rhs) const;

  // return true if the numbers are not equal
  bool operator!=(const LargeNum &rhs) const;

  // return true if the left-hand-side number is less than the
  // right-hand-side number
  bool operator<(const LargeNum &rhs) const;

  // return true if the left-hand-side number is greater than the
  // right-hand-side number
  bool operator>(const LargeNum &rhs) const;

  // return true if the left-hand-side number is less than or equal to the
  // right-hand-side number
  bool operator<=(const LargeNum &rhs) const;

  // return true if the left-hand-side number is greater than or equal to the
  // right-hand-side number
  bool operator>=(const LargeNum &rhs) const;

  // prefix increment
  LargeNum &operator++();

  // postfix increment
  LargeNum operator++(int);

  // prefix decrement
  LargeNum &operator--();

  // postfix decrement
  LargeNum operator--(int);
};