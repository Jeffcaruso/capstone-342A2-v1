#include "largenum.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#ifndef LARGENUM_H
#define LARGENUM_H
#endif // LARGENUM_H


using namespace std;

class LargeNum {
public:
    // Default constructor
    LargeNum() {
        num = "0";
        isPositive = true;
    }

    // Constructor with string input
    LargeNum(const std::string& str) {
        num = str;
        isPositive = true;
    }

    // Copy constructor
    LargeNum(const LargeNum& other) {
        num = other.num;
        isPositive = other.isPositive;
    }

    // Assignment operator
    LargeNum& operator=(const LargeNum& other) {
        if (this == &other) {
            return *this;
        }
        num = other.num;
        isPositive = other.isPositive;
        return *this;
    }

    // Addition operator
    LargeNum operator+(const LargeNum& other) const {
        LargeNum result;
        result.isPositive = isPositive;
        int carry = 0;
        int i = 0, j = 0;
        while (i < num.length() || j < other.num.length() || carry != 0) {
            int a = i < num.length() ? num[i++] - '0' : 0;
            int b = j < other.num.length() ? other.num[j++] - '0' : 0;
            int sum = a + b + carry;
            result.num.push_back(sum % 10 + '0');
            carry = sum / 10;
        }
        return result;
    }

    // Subtraction operator
    LargeNum operator-(const LargeNum& other) const {
        LargeNum result;
        result.isPositive = isPositive;
        int borrow = 0;
        int i = 0, j = 0;
        while (i < num.length() || j < other.num.length() || borrow != 0) {
            int a = i < num.length() ? num[i++] - '0' : 0;
            int b = j < other.num.length() ? other.num[j++] - '0' : 0;
            int diff = a - b - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.num.push_back(diff + '0');
        }
        return result;
    }

    // Negation operator
    LargeNum operator-() const {
        LargeNum result = *this;
        result.isPositive = !result.isPositive;
        return result;
    }

    // Equality operator
    bool operator==(const LargeNum& other) const {
        return num == other.num && isPositive == other.isPositive;
    }

    // Inequality operator
    bool operator!=(const LargeNum& other) const {
        return !(*this == other);
    }

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const LargeNum& ln) {
        if (!ln.isPositive) {
            os << "-";
        }
        for (int i = ln.num.length() - 1; i >= 0; --i) {
            os << ln.num[i];
        }
        return os;
    }

private:
    std::string num;
    bool isPositive;
};

