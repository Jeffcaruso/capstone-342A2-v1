//============================================================================
// Name        : Test2
// Test Desc.  : Test EQ, NE, GT, GTE, LT, LTE comparisons
//				 	(coverage for old test 2 method)
// Author      : Jeffrey Caruso
// Date    	   : Fall 2023
//============================================================================

#include <gtest/gtest.h>
#include "applib/largenum.h"

#include <iostream>
#include <sstream>

using namespace std;

//note / reminder:
// use EXPECT_EQ (or _NE) for std::string
// for c strings, use EXPECT_STREQ (or STRNE)
// http://google.github.io/googletest/reference/assertions.html

TEST(Test2one, CheckEqualAndNE)
{
	//Testing Equal and Not Equal with operator overloads
	//is true that 99 == 99
	EXPECT_TRUE(LargeNum(99) == LargeNum(99));
	//is true that 99 != 100
	EXPECT_TRUE(LargeNum(99) != LargeNum(100));  	
}

TEST(TEST2two, CheckGTEandLTE)
{
	//Testing Greater Than or Equal and Less Than or Equal with operator overloads	
	//is true that 105 >= 100
	EXPECT_TRUE(LargeNum(105) >= LargeNum(100));
	//is true that 100 <= 105
	EXPECT_TRUE(LargeNum(100) <= LargeNum(105));
}

TEST(Test2three, CheckGTandLT)
{
	//Testing Greater Than and Less Than with operator overloads	

	//is true that 99 > 7
	EXPECT_TRUE(LargeNum(99) > LargeNum(7));
	//is true that 7 < 99
	EXPECT_TRUE(LargeNum(7) < LargeNum(99));

	//is true that 99 > -7
	EXPECT_TRUE(LargeNum(99) > LargeNum(-7));
	//is true that -7 < 99
	EXPECT_TRUE(LargeNum(-7) < LargeNum(99));

	//is true that -5 > -10
	EXPECT_TRUE(LargeNum(-5) > LargeNum(-10));
	//is true that -10 < -5
	EXPECT_TRUE(LargeNum(-10) < LargeNum(-5));

	//is true that (5 > 5 is incorrect)
	EXPECT_TRUE( ! (LargeNum(5) > LargeNum(5)));
}

// These tests were feasibly split by category, so students can know and test their inequality operators by type.
