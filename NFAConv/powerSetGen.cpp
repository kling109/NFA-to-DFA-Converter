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
}

/*
Overloaded Constructor for the case in which a state set is supplied to the
constructor.  Initializes both the power set and source set vectors.
*/
PowerSetGenerator::PowerSetGenerator(vector<string>* stateSet)
{
  this->powerSet = new vector<vector<string>* >();
  this->sourceSet = stateSet;
}

/*
Method to build the power set from inputs.  The function first checks if  a
source set has actually been supplied, and prints an error otherwise.
The function then calls a recursive helper method to build the actual power set.
*/
void PowerSetGenerator::buildPowerSet()
{
  if (this->sourceSet == 0)
  {
    cout << "A starting set has not been provided.  Please retry with a valid set." << endl;
  }
  else
  {
    powerSetHelper(this->powerSet, this->sourceSet);
  }
}

/*
Recursive helper method for building a power set.  The function takes inputs for the set
to store the resutls in as a nested vector, and the input set as a vector of strings.
The program first checks if the input set is empty, and if so pushes "EM", the empty set,
onto the resutls vector.  All results are added via the "insertUniqueElement" method, which
first checks if a duplicate of the element is already in the vector before deciding whether
to add it or not.  If the input size is not 0, the function pushes the inputs onto the vector.
Then, the function loops through the input set and produces new sets of elements, each with
one of the previous input elements removed.  These sets are then recursively operated on by the
helper method.
*/
void PowerSetGenerator::powerSetHelper(vector<vector<string>* >* results, vector<string>* inputs)
{
  if (inputs->size() == 0)
  {
    vector<string>* nextInput = new vector<string>();
    nextInput->push_back("EM");
    insertUniqueElement(results, nextInput);
  }
  else
  {
    insertUniqueElement(results, inputs);
    for (int i = 0; i < inputs->size(); ++i)
    {
      vector<string>* nextInput = new vector<string>();
      for (int j = 0; j < i; ++j)
      {
        nextInput->push_back(inputs->at(j));
      }
      for (int k = i+1; k < inputs->size(); ++k)
      {
        nextInput->push_back(inputs->at(k));
      }
      powerSetHelper(results, nextInput);
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
Builds the power set of a given state set.  The given state set will
override a state that was applied when the constructor was called.
The function is simply a macro for reassigning the stateSet and then calling
the build function.
*/
void PowerSetGenerator::buildPowerSet(vector<string>* stateSet)
{
  this->sourceSet = stateSet;
  buildPowerSet();
}

/*
Returns the power set if and only if it has been built.  If a state has been
provided but the build has not occured, then the power set is built before being returned.
The function displays an error message if the program has not been provided any input set.
*/
vector<vector<string>* >* PowerSetGenerator::getPowerSet()
{
  if (this->powerSet == 0)
  {
    if (this->sourceSet == 0)
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
A macro for assigning the state set, building and returning the power set.
*/
vector<vector<string>* >* PowerSetGenerator::getPowerSet(vector<string>* stateSet)
{
  this->powerSet = stateSet;
  buildPowerSet();
  return this->powerSet;
}
