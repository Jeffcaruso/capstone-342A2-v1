//============================================================================
// Name        : Test1
// Test Desc.  : Test that the methods to determine empty are correct
//				 	(coverage for old test 1 method) the 'student' code
// Author      : Jeffrey Caruso
// Date    	   : Fall 2023
//============================================================================

#include <gtest/gtest.h>
#include "applib/largenum.h"

using namespace std;

TEST(Test1, CheckSize4Empty)
{
	cout << "trivial test for now..." << endl;

	// //Make Pokedex class pdx
	// Pokedex pdx;

	// //check it starts with size 0 as expected
	// EXPECT_EQ(pdx.size(), 0);
}

TEST(Test1, CheckEmpty4Empty)
{
	cout << "trivial test for now..." << endl;

	// //Make Pokedex class pdx
	// Pokedex pdx;

	// //Check empty method. expecting it to be empty
	// EXPECT_EQ(pdx.empty(), 0);
}

TEST(Test1, CheckOutStr4Empty)
{	
	cout << "trivial test for now..." << endl;
	// //Make Pokedex class pdx
	// Pokedex pdx;

	// //check output is an empty set "[]" as expected
	// ostringstream outStrStr;
	// outStrStr << pdx;
	// //for comparisons, make the c strings to a std::string, 
	// 	// since Pokedex is storing as std::string.
	// string emptySet = "[]";
	// EXPECT_EQ(outStrStr.str(), emptySet);
}
