//============================================================================
// Name        : Test3
// Test Desc.  : Test to check negative #'s
//				 	(coverage for old test 3 method)
// Author      : Jeffrey Caruso
// Date    	   : Fall 2023
//============================================================================

#include <gtest/gtest.h>
#include "applib/largenum.h"

#include <iostream>
#include <sstream>

using namespace std;

TEST(Test3, checkNegativeNumbers)
{
	//misc testing x3
	stringstream strs;
	LargeNum num0("-1234567890123456789");
	strs << num0;
	string ans0Str = "-1,234,567,890,123,456,789";
	EXPECT_EQ(strs.str(), ans0Str);

	strs.str("");
	LargeNum num1(-12345);
	strs << num1;
	string ans1Str = "-12,345";
	EXPECT_EQ(strs.str(), ans1Str);

	strs.str("");
	LargeNum numZero(-0000);
	strs << numZero;
	string ans2Str = "0";
	EXPECT_EQ(strs.str(), ans2Str);

	//check isZero
	EXPECT_TRUE(LargeNum(0).isZero());
	EXPECT_TRUE(LargeNum(-0).isZero());

	//check == operator on 0, -0.
	EXPECT_TRUE(LargeNum(0) == LargeNum(-0));

	//check negation operator
	EXPECT_TRUE(LargeNum(0).negate() == LargeNum(-0));

	//combination add, sub, then equality operator usage...
	// 100 - 100 = 0
	EXPECT_TRUE(LargeNum(100) - LargeNum(100) == LargeNum(0));
	// 100 + -100 = 0
	EXPECT_TRUE(LargeNum(100) + LargeNum(-100) == LargeNum(0));
	// 100 - (-100) = 200
	EXPECT_TRUE(LargeNum(100) - LargeNum(-100) == LargeNum(200));
	// -100 - (-100) = 0
	EXPECT_TRUE(LargeNum(-100) - LargeNum(-100) == LargeNum(0));
	// -100 + 100 = 0
	EXPECT_TRUE(LargeNum(-100) + LargeNum(100) == LargeNum(0));
	// 100 - 7 = 93
	EXPECT_TRUE(LargeNum(100) - LargeNum(7) == LargeNum(93));
	// 7 - 100 = -93
	EXPECT_TRUE(LargeNum(7) - LargeNum(100) == LargeNum(-93));
	// -7 + (-100) = -107
	EXPECT_TRUE(LargeNum(-7) + LargeNum(-100) == LargeNum(-107));
}

// There is no meaningful split here that is not already covered by Test 1 or Test 2.
// Thus, this is best left as 1 comprehensive test of negative numbers and their proper use in student BigNum class
