//============================================================================
// Name        : Test4
// Test Desc.  : Test multiplication
//				 	(coverage for old test 4 method)
// Author      : Jeffrey Caruso
// Date    	   : Fall 2023
//============================================================================

#include <gtest/gtest.h>
#include "applib/largenum.h"

#include <iostream>
#include <sstream>

using namespace std;

TEST(Test4, MultiplicationTesting)
{
	// is true that 25 * 0 = 0
	EXPECT_TRUE(LargeNum(25) * LargeNum(0) == LargeNum(0));

	// is true that 25 * 5 = 125
	EXPECT_TRUE(LargeNum(25) * LargeNum(5) == LargeNum(125));

	//is true that (-25) * (-5) = 125
	EXPECT_TRUE(LargeNum(-25) * LargeNum(-5) == LargeNum(125));

	// is true that (-25) * (5) = -125
	EXPECT_TRUE(LargeNum(-25) * LargeNum(5) == LargeNum(-125));

	// is true that 25 * (-5) = -125
	EXPECT_TRUE(LargeNum(25) * LargeNum(-5) == LargeNum(-125));
}
