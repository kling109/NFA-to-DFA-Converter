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
#include <algorithm>
#include "deltaFunc.h"
#include "epsilon.h"

using namespace std;

/*
Default constructor for a Delta Generator, intiializes all pointers to null
so they can be checked later
*/
DeltaGenerator::DeltaGenerator()
{
  this->epsilonClosure = NULL;
  this->deltaMap = NULL;
}

/*
Overloaded constructor for a Delta Generator.  Produces the EpsilonClosureGenerator
object for use later, when given a transition map.
*/
DeltaGenerator::DeltaGenerator(vector<vector<string>* >* transitionMap)
{
  this->epsilonClosure = new EpsilonClosureGenerator(transitionMap);
  this->deltaMap = transitionMap;
}

/*
Standard deconstructor.  Deletes objects if they have not been set
to null.
*/
DeltaGenerator::~DeltaGenerator()
{
  if (this->epsilonClosure != 0)
  {
    delete this->epsilonClosure;
  }
}

/*
Setter method for the given mapping.  Also re-initializes the epsilonClosure
object for the new mapping.
*/
void DeltaGenerator::setMapping(vector<vector<string>* >* transitionMap)
{
  this->deltaMap = transitionMap;
  if (this->epsilonClosure != 0)
  {
    epsilonClosure->setMapping(transitionMap);
  }
  else
  {
    this->epsilonClosure = new EpsilonClosureGenerator(transitionMap);
  }
}

/*
A generator method for the new delta map.  The program iterates over all existing mappings in the
NFA, taking the epsilon closure of each start state.  The new element of the powerset is then checked
against all elements in the mapping, to find any possible mappings as a result of the given alphabet
character.  These end results are then compoinded into another elment of the power set, and once the
new mapping has checked every one of the original delta function transitions, the new mapping is pushed
into a new vector for the overall map.
*/
vector<vector<vector<string>* >* >* DeltaGenerator::powerSetDeltaMapGen()
{
  if (this->deltaMap == 0)
  {
    cout << "A mapping was not provided." << endl;
  }
  else
  {
    vector<vector<vector<string>* >* >* newMap = new vector<vector<vector<string>* >* >();
    for (int i = 0; i < this->deltaMap->size(); ++i)
    {
      // One iteration for each mapping
      vector<string>* currentObj = this->deltaMap->at(i);
      if (currentObj->at(1) != "EPS")
      {
        vector<string>* newStartState = epsilonClosure->closureOf(currentObj->at(0));
        vector<string>* newEndState = epsilonClosure->closureOf(currentObj->at(2));
        vector<vector<string>* >* newMapEntry = new vector<vector<string>* >();
        for (int j = 0; j < newStartState->size(); ++j)
        {
          for (int k = 0; k < this->deltaMap->size(); ++k)
          {
            vector<string>* iteration = this->deltaMap->at(k);
            if (newStartState->at(j) == iteration->at(0) && currentObj->at(1) == iteration->at(1))
            {
              newEndState = mergeUniquely(newEndState, epsilonClosure->closureOf(iteration->at(2)));
              sort(newEndState->begin(), newEndState->end());
            }
          }
        }
        vector<string>* alphabetChar = new vector<string>();
        alphabetChar->push_back(currentObj->at(1));
        newMapEntry->push_back(newStartState);
        newMapEntry->push_back(alphabetChar);
        newMapEntry->push_back(newEndState);
        bool uniqueEntry = true;
        for (int j = 0; j < newMap->size(); ++j)
        {
          if (*newMapEntry->at(0) == *newMap->at(j)->at(0) && *newMapEntry->at(1) == *newMap->at(j)->at(1) && *newMapEntry->at(2) == *newMap->at(j)->at(2))
          {
            uniqueEntry = false;
          }
        }
        if (uniqueEntry)
        {
          newMap->push_back(newMapEntry);
        }
        else
        {
          delete newMapEntry;
        }
      }
    }
    return newMap;
  }
}

/*
Helper method for the power set delta generator.  Merges two vectors, removing any
duplicates.  The function iterates through the input vector, checking it against all
elements of the output vector.  If none of the elements match, the input is merged into the
output vector.  If the element matches, the element is discarded.
*/
vector<string>* DeltaGenerator::mergeUniquely(vector<string>* endSet, vector<string>* candidate)
{
  for (int i = 0; i < candidate->size(); ++i)
  {
    bool unique = true;
    for (int j = 0; j < endSet->size(); ++j)
    {
      if (endSet->at(j) == candidate->at(i))
      {
        unique = false;
        break;
      }
    }
    if (unique)
    {
      endSet->push_back(candidate->at(i));
    }
  }
  return endSet;
}

/*
Overloaded method for the power set delta generator.  Allows both the power set and
the initial mapping to be changed before the new delta function is produced.
*/
vector<vector<vector<string>* >* >* DeltaGenerator::powerSetDeltaMapGen(vector<vector<string>* >* transitionMap)
{
  this->setMapping(transitionMap);
  return this->powerSetDeltaMapGen();
}
