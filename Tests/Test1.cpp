//============================================================================
// Name        : Test1
// Test Desc.  : Test that Printing and addition operates as expected
//				 	(coverage for old test 1 method)
// Author      : Jeffrey Caruso
// Date    	   : Fall 2023
//============================================================================

#include <gtest/gtest.h>
#include "applib/largenum.h"

#include <iostream>
#include <sstream>

using namespace std;

TEST(Test1, CheckPrintingAndAddition)
{
	stringstream strs;

	//an actually large #
	LargeNum num0("1234567890123456789");
	strs << num0;
	string ans0Str = "1,234,567,890,123,456,789";
	EXPECT_EQ(strs.str(), ans0Str);
	
	//a smaller #
	strs.str("");
	LargeNum num1(12345);
	strs << num1;
	string ans1Str = "12,345";
	EXPECT_EQ(strs.str(), ans1Str);

	// addition w/ smaller #'s
	strs.str("");
	LargeNum num2(11115);
	LargeNum num3 = num1 + num2;
	strs << num3;
	string ans2Str = "23,460";
	EXPECT_EQ(strs.str(), ans2Str);

	// another addition w/ smaller #'s
	strs.str("");
	LargeNum num4(99);
	LargeNum num5 = num1 + num4;
	strs << num5;
	string ans3Str = "12,444";
	EXPECT_EQ(strs.str(), ans3Str);

	// addition w/ medium #
	strs.str("");
	LargeNum num6(99000);
	LargeNum num7 = num1 + num6;
	strs << num7;
	string ans4Str = "111,345";
	EXPECT_EQ(strs.str(), ans4Str);

	// addition w/ large #
	strs.str("");
	LargeNum num8 = num0 + num1;
	strs << num8;
	string ans5Str = "1,234,567,890,123,469,134";
	EXPECT_EQ(strs.str(), ans5Str);
}

//This cannot be easily split without changing the actual tests becuase they depend on each number...
