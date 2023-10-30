//============================================================================
// Name        : Test2
// Test Desc.  : Testing student access input Sanitization
//				 	(coverage for old test 5 method)
// Author      : Jeffrey Caruso
// Date    	   : Fall 2023
//============================================================================

#include <gtest/gtest.h>
#include "applib/largenum.h"

using namespace std;

TEST(Test6, CheckAccessInputSanitizationInPokedex)
{
	//Make Pokedex class pdx
	Pokedex pdx;

	// expect error message from Pokedex class
	pdx.front();
	pdx.back();
	pdx.at(3);
	pdx.at(-9);
	pdx.erase(5);
	pdx.erase(-10);
	pdx.pop_back();

	//yield better error output to user with making it clear 0 is expected result
	int expectedSize = 0;
	//verify expected result of 0
	EXPECT_EQ(pdx.size(), expectedSize);

	//should actually work
	pdx.insert("Charmander");
	// expect error message from Pokedex class
	pdx.at(6);
	pdx.erase(2);

	//yield better error output to user with making it clear 1 is expected result
	int expectedSize1 = 1;
	//verify expected result of 1
	EXPECT_EQ(pdx.size(), expectedSize1);

	//actually erase the start of the list (Charmander)
	pdx.erase(0);

	//yield better error output to user with making it clear 0 is expected result
	int expectedSize2 = 0;
	//verify expected result of 0
	EXPECT_EQ(pdx.size(), expectedSize2);
}


