//#include "Inc/pokedex.h"
#include "pokedex.h"  //trying the alternate include approach to get things to maybe work better...

Pokedex::Pokedex()
{
    msize = 0;
}

int Pokedex::size() const
{
    return 0;
}

bool Pokedex::empty() const
{
    return false;
}

ostream &operator<<(ostream &out, const Pokedex &pdx)
{
    //Memory leak on or off...
    //char *lol = (char*) malloc(100);

    out << "[]";
    return out;
}

// Add pokemon to Pokedex, keep the Pokedex list sorted
// Can have multiple pokemon with the same name
// Pokemon is not inserted if Pokedex is already full
void Pokedex::insert(const string &pokemon)
{
    // do nothing...
    // student code to actually do the work here...
}

// return pokemon at given index
// undefined behaviour for n < 0 or n >= size
const string &Pokedex::at(int n) const
{
    // do nothing, return a string that shouldn't be a pokemon name...
    return "LOL1";
}

// return pokemon at the front, alphabetically first one
const string &Pokedex::front() const
{
    // do nothing, return a string that shouldn't be a pokemon name...
    return "LOL2";
}

// return pokemon at the front, alphabetically last one
const string &Pokedex::back() const
{
    // do nothing, return a string that shouldn't be a pokemon name...
    return "LOL3";
}

// Erase element at location, move other elements as needed
// undefined behaviour if given index is not valid
void Pokedex::erase(int n)
{
    // do nothing
}

// Delete the last element
void Pokedex::pop_back()
{
    // do nothing
}
