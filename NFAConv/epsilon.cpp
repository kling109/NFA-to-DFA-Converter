/*
Name: Trevor Kling
ID: 002270716
Email: kling109@mail.chapman.edu
Course: CPSC 406 Algorithm Analysis
Last Date Modified: 16 February 2019
Project: NFA to DFA Converter
*/

#include <string>
#include <vector>
#include <iostream>
#include "epsilon.h"

using namespace std;


/*
Default constuctor for the Epsilon Closure Generator.  deltaMap is initialized to null to ensure the
pointer behaves correctly.
*/
EpsilonClosureGenerator::EpsilonClosureGenerator()
{
  this->deltaMap = NULL;
}

/*
Overloaded costructor for the case in which a particular mapping is provided.
*/
EpsilonClosureGenerator::EpsilonClosureGenerator(vector<vector<string>* >* transitionMap)
{
  this->deltaMap = transitionMap;
}

/*
Default deconstructor.  Checks to be sure that deltaMap is not null before deleting it.
*/
EpsilonClosureGenerator::~EpsilonClosureGenerator()
{
  
}

/*
Setter method for the transition map.
*/
void EpsilonClosureGenerator::setMapping(vector<vector<string>* >* transitionMap)
{
  this->deltaMap = transitionMap;
}

/*
Generates the closure of a given state.  The function first checks to be sure a mapping has
been provided; if not, the program prints an error.  If a map has been provided, the function
produces a new vector for the epsilon closure and subsequently pushes the initial state onto the
vector.  The program then iterates through all elements of the mapping, and finds the cases
where the starting state is the given state, and the alphabet element is "EPS," the symbol for
epsilon transitions.  These elements are then pushed onto the vector if they are unique.
*/
vector<string>* EpsilonClosureGenerator::closureOf(string state)
{
  if (this->deltaMap != 0)
  {
    vector<string>* closureSet = new vector<string>();
    closureSet->push_back(state);
    for (int i = 0; i < deltaMap->size(); ++i)
    {
      if (deltaMap->at(i)->at(0) == state && deltaMap->at(i)->at(1) == "EPS")
      {
        insertUniqueElement(closureSet, deltaMap->at(i)->at(2));
      }
    }
    return closureSet;
  }
  else
  {
    cout << "A mapping has not been provided." << endl;
  }
}

/*
Similarly to the above function, this program finds the epsilon closure of a state.
However, this epsilon closure is of an object in the power state, intended for use when
the new delta function is being produced.  The function first checks if a mapping has been
provided, and if so it produces two new vectors; a work vector to store temporary results in,
and a final vector to store the end state.  The function takes each element in the power set
and checks their closure set; the unique elements of this set are then added to the final vector.
This process is performed for all entries of the power set.
*/
vector<string>* EpsilonClosureGenerator::closureOf(vector<string>* powerState)
{
  if (this->deltaMap != 0)
  {
    vector<string>* finalState = new vector<string>();
    vector<string>* workSet = NULL;
    for (int i = 0; i < powerState->size(); ++i)
    {
      workSet = closureOf(powerState->at(i));
      for (int j = 0; j < workSet->size(); ++j)
      {
        insertUniqueElement(finalState, workSet->at(j));
      }
    }
    return finalState;
  }
  else
  {
    cout << "A mapping has not been provided." << endl;
  }
}

/*
Helper method which determines if a particular set contains an element or not.  If the element
is not contianed, it is added to the set.
*/
void EpsilonClosureGenerator::insertUniqueElement(vector<string>* set, string element)
{
  bool unique = true;
  for (int i = 0; i < set->size(); ++i)
  {
    if (set->at(i) == element)
    {
      unique = false;
      break;
    }
  }
  if (unique)
  {
    set->push_back(element);
  }
}
