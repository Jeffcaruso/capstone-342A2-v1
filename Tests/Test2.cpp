//============================================================================
// Name        : Test2
// Test Desc.  : Test that add work properly for 1 item
//				 	(coverage for old test 2 method)
// Author      : Jeffrey Caruso
// Date    	   : Fall 2023
//============================================================================

#include <gtest/gtest.h>
#include "applib/largenum.h"

using namespace std;

//note / reminder:
// use EXPECT_EQ (or _NE) for std::string
// for c strings, use EXPECT_STREQ (or STRNE)
// http://google.github.io/googletest/reference/assertions.html

TEST(Test2, Add1Pokemon)
{
	//Make Pokedex class pdx
	Pokedex pdx;

	//string stream for output testing
	stringstream strs;

	pdx.insert("Pikachu");

	//check its size 1 as expected after 1 add
	//yield better error output to user with making it clear 1 is expected result
	int expectedResult1 = 1;
	EXPECT_EQ(pdx.size(), expectedResult1);

	//expecting pdx to not be empty after 1 add
	EXPECT_FALSE(pdx.empty());

	//expect Pikachu to be at index 0 after adding it
	//have comparison be against a std string
	string Pika = "Pikachu";
	EXPECT_EQ(pdx.at(0), Pika);

	//expect with only 1 item for front to equal back
	EXPECT_EQ(pdx.front(), pdx.back());

	//init str stream
	strs.str("");
	//test output operator
	strs << pdx;
	//have comparison be against a std string
	string PikaSet = "[Pikachu]";
	//check the output operator was correct
	EXPECT_EQ(strs.str(), PikaSet);
}

//this test has no reason to be split into multiple sections to feasibly provide 
	//more info to user by splitting this into multiple subtests
