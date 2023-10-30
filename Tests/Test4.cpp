//============================================================================
// Name        : Test2
// Test Desc.  : Test that add + remove work properly for 3 items
//				 	(coverage for old test 4 method)
// Author      : Jeffrey Caruso
// Date    	   : Fall 2023
//============================================================================

#include <gtest/gtest.h>
#include "applib/pokedex.h"

using namespace std;

TEST(Test4, LifecycleFor3PokemonEntries)
{
	//Make Pokedex class pdx
	Pokedex pdx;

	//string stream for output testing
	stringstream strs;

	//insert 3 Pokemon out of alpha order, class should alpha sort.
	pdx.insert("Charmander");
	pdx.insert("Pikachu");
	pdx.insert("Bulbasaur");

	//init strs
	strs.str("");
	//test output
	strs << pdx;

	//test things were added correctly and output correctly (largely testing alpha sort)
	string expectedResult1 = "[Bulbasaur, Charmander, Pikachu]";
	EXPECT_EQ(strs.str(), expectedResult1);

	//erase center
	pdx.erase(1);

	//reset strs
	strs.str("");

	//test output
	strs << pdx;

	string expectedResult2 = "[Bulbasaur, Pikachu]";
	EXPECT_EQ(strs.str(), expectedResult2);
}

