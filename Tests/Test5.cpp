//============================================================================
// Name        : Test5
// Test Desc.  : Testing division
//				 	(coverage for old test 5 method)
// Author      : Jeffrey Caruso
// Date    	   : Fall 2023
//============================================================================

#include <gtest/gtest.h>
#include "applib/largenum.h"

#include <iostream>
#include <sstream>

using namespace std;

TEST(Test5, Division)
{
	//using small #'s to avoid excessive computation

	// is true that 0 / 5 = 0
	EXPECT_TRUE(LargeNum(0) / LargeNum(5) == LargeNum(0));

	//is true that 25 / 5 = 5
	EXPECT_TRUE(LargeNum(25) / LargeNum(5) == LargeNum(5));

	//is true that (-25) / (-5) = 5
	EXPECT_TRUE(LargeNum(-25) / LargeNum(-5) == LargeNum(5));

	//is true that (-25) / 5 = -5
	EXPECT_TRUE(LargeNum(-25) / LargeNum(5) == LargeNum(-5));

	//is true that 25 / (-5) = -5
	EXPECT_TRUE(LargeNum(25) / LargeNum(-5) == LargeNum(-5));

	//is true that 25 / 7 = 3. (when using integer math)
	EXPECT_TRUE(LargeNum("25") / LargeNum("7") == LargeNum("3"));

	//is true that 7 / 25 = 0. (when using integer math)
	EXPECT_TRUE(LargeNum("7") / LargeNum("25") == LargeNum("0"));
}
