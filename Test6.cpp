//============================================================================
// Name        : Test6
// Test Desc.  : Testing Prefix + Postfix operations
//				 	(coverage for old test 5 method)
// Author      : Jeffrey Caruso
// Date    	   : Fall 2023
//============================================================================

#include <gtest/gtest.h>
#include "applib/largenum.h"

#include <iostream>
#include <sstream>

using namespace std;


TEST(Test6one, CheckPrefixAndPostfix)
{
	LargeNum num0(10);

	// is true that (10++) = 10
	EXPECT_TRUE(num0++ == LargeNum(10));
	
	// is true that 11 = 11
	EXPECT_TRUE(num0 == LargeNum(11));

	// is true that (--11) = 10
	EXPECT_TRUE(--num0 == LargeNum(10));

	// is true that (10--) = 10
	EXPECT_TRUE(num0-- == LargeNum(10));

	// is true that 9 = 9
	EXPECT_TRUE(num0 == LargeNum(9));

	// is true that (++9) = 10
	EXPECT_TRUE(++num0 == LargeNum(10));

	// is true that (10--) = 10
	EXPECT_TRUE(num0-- == LargeNum(10));

	// is true that 9 = 9
	EXPECT_TRUE(num0 == LargeNum(9));

	// testing with a negative (and staying negative)
	num0.negate();

	// is true that (++(-9)) = -8
	EXPECT_TRUE(++num0 == LargeNum(-8));

	// is true that (--(-8)) = -9
	EXPECT_TRUE(--num0 == LargeNum(-9));

}

TEST(Test6two, CheckPrefixIntoAndOutOfNegative)
{
	//specifically prefix making # negative
	LargeNum num1(1);

	// is true that (--1) = 0
	EXPECT_TRUE(--num1 == LargeNum(0));

	// is true that (--0) = 0
	EXPECT_TRUE(--num1 == LargeNum(-1));

	// is true that (++(-1)) = 0
	EXPECT_TRUE(++num1 == LargeNum(0));
}
