/**
 * Pokedex class
 * Pokemon are represented as string objects
 * Can add and remove pokemon, print pokedex
 * Internally pokedex is an array and all pokemon are kept sorted
 *
 * Calling a function with invalid parameters causes undefined behavior.
 * For our puporposes, if a function has been called with invalid parameters
 * and needs to return a value, the first element in the pokedex is returned.
 **/

#ifndef POKEDEX_H
#define POKEDEX_H

#include <iostream>
#include <string>

using namespace std;

class Pokedex {
public:
  // constructor - create empty Pokedex
  Pokedex();

  // Return size
  int size() const;

  // Return maximum size, capacity of Pokedex
  static int max_size();

  // return true if Pokedex is empty
  bool empty() const;

  // return pokemon at given index
  // undefined behaviour for n < 0 or n >= size
  const string &at(int n) const;

  // return pokemon at the front, alphabetically first one
  const string &front() const;

  // return pokemon at the front, alphabetically last one
  const string &back() const;

  // Add pokemon to Pokedex, keep the Pokedex list sorted
  // Can have multiple pokemon with the same name
  // Pokemon is not inserted if Pokedex is already full
  void insert(const string &pokemon);

  // Delete the last element
  void pop_back();

  // Erase element at location, move other elements as needed
  // undefined behaviour if given index is not valid
  void erase(int n);

private:
  // maximum capacity of Pokedex
  static const int MAX = 10;

  // sorted list of pokemon in Pokedex
  string pokemons[MAX];

  // current internal size
  int msize = 0;
};

// insertion operator, so we can use "cout << pdx"
ostream &operator<<(ostream &out, const Pokedex &pdx);

#endif // POKEDEX_H