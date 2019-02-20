/*
Name: Trevor Kling
ID: 002270716
Email: kling109@mail.chapman.edu
Course: CPSC 406 Algorithm Analysis
Last Date Modified: 15 February 2019
Project: NFA to DFA Converter
*/

#include <string>
#include <vector>
#include <iostream>
#include "powerSetGen.h"

using namespace std;


/*
Default construct for the power set generator.  Initializes the powerSet
vector, which will be filled with values.
*/
PowerSetGenerator::PowerSetGenerator()
{
  this->powerSet = new vector<vector<string>* >();
  this->sourceMap = NULL;
}

/*
Overloaded Constructor for the case in which a mapping is supplied to the
program.  Initializes both the power set and source map vectors.
*/
PowerSetGenerator::PowerSetGenerator(vector<vector<vector<string>* >* >* mapping)
{
  this->powerSet = new vector<vector<string>* >();
  this->sourceMap = mapping;
}

/*
Standard deconstructor for a power set generator.
*/
PowerSetGenerator::~PowerSetGenerator()
{
  if (powerSet != 0)
  {
    delete this->powerSet;
  }
}

/*
Adds elements to the end set based on which elements of the power set are being used
by the new delta map.  The sourece map is iterated over, checking if each element has
been added to the set of vectors.  If it has not been, it is added.
*/
void PowerSetGenerator::buildPowerSet()
{
  if (this->sourceMap == 0)
  {
    cout << "A mapping has not been provided.  Please retry with a valid mapping." << endl;
  }
  else
  {
    for (int i = 0; i < this->sourceMap->size(); ++i)
    {
      insertUniqueElement(powerSet, sourceMap->at(i)->at(0));
      insertUniqueElement(powerSet, sourceMap->at(i)->at(2));
    }
  }
}

/*
Iterates through the set of existing elements in the power set, and adds the new element only
if there is no existing copy of that set in the power set.
*/
void PowerSetGenerator::insertUniqueElement(vector<vector<string>* >* results, vector<string>* entry)
{
  bool unique = true;
  for (int i = 0; i < results->size(); ++i)
  {
    if (*results->at(i) == *entry)
    {
      unique = false;
      break;
    }
  }
  if (unique)
  {
    results->push_back(entry);
  }
}

/*
Builds the power set of a given map.  The given mapping will
override a map that was applied when the constructor was called.
The function is simply a macro for reassigning the soureMap and then calling
the build function.
*/
void PowerSetGenerator::buildPowerSet(vector<vector<vector<string>* >* >* mapping)
{
  this->sourceMap = mapping;
  buildPowerSet();
}

/*
Returns the power set if and only if it has been built.  If a mapping has been
provided but the build has not occured, then the power set is built before being returned.
The function displays an error message if the program has not been provided any input map.
*/
vector<vector<string>* >* PowerSetGenerator::getPowerSet()
{
  if (this->powerSet->size() == 0)
  {
    if (this->sourceMap == 0)
    {
      cout << "A starting set has not been provided.  Please retry with a valid set." << endl;
    }
    else
    {
      buildPowerSet();
      return this->powerSet;
    }
  }
  else
  {
    return this->powerSet;
  }
}

/*
A macro for assigning the mapping, building and returning the power set.
*/
vector<vector<string>* >* PowerSetGenerator::getPowerSet(vector<vector<vector<string>* >* >* mapping)
{
  this->sourceMap = mapping;
  buildPowerSet();
  return this->powerSet;
}
