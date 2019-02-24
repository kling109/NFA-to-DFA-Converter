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
  this->alphabet = NULL;
}

/*
Overloaded constructor for a Delta Generator.  Produces the EpsilonClosureGenerator
object for use later, when given a transition map.
*/
DeltaGenerator::DeltaGenerator(vector<vector<string>* >* transitionMap)
{
  this->epsilonClosure = new EpsilonClosureGenerator(transitionMap);
  this->deltaMap = transitionMap;
  this->alphabet = NULL;
}

/*
Overloaded constructor for a Delta Generator.  Produces the EpsilonClosureGenerator
object for use later, when given a transition map.
*/
DeltaGenerator::DeltaGenerator(vector<vector<string>* >* transitionMap, vector<string>* alph)
{
  this->epsilonClosure = new EpsilonClosureGenerator(transitionMap);
  this->deltaMap = transitionMap;
  this->alphabet = alph;
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
Setter method for the alphabet being used.
*/
void DeltaGenerator::setAlphabet(vector<string>* alph)
{
  this->alphabet = alph;
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
  if (this->deltaMap == 0 || this->alphabet == 0)
  {
    cout << "A mapping or alphabet was not provided." << endl;
  }
  else
  {
    vector<vector<vector<string>* >* >* newMap = new vector<vector<vector<string>* >* >();
    vector<vector<string>* >* newMapStateSet = new vector<vector<string>* >();
    for (int i = 0; i < this->deltaMap->size(); ++i)
    {
      insertUniqueElement(newMapStateSet, epsilonClosure->closureOf(this->deltaMap->at(i)->at(0)));
      insertUniqueElement(newMapStateSet, epsilonClosure->closureOf(this->deltaMap->at(i)->at(2)));
    }
    for (int i = 0; i < newMapStateSet->size(); ++i)
    {
      for (int j = 0; j < this->alphabet->size(); ++j)
      {
        vector<vector<string>* >* newMapElement = new vector<vector<string>* >();
        vector<string>* newStartState = newMapStateSet->at(i);
        vector<string>* alphabetChar = new vector<string>();
        vector<string>* newEndState = new vector<string>();
        alphabetChar->push_back(this->alphabet->at(j));
        for (int k = 0; k < this->deltaMap->size(); ++k)
        {
          for (int l = 0; l < newStartState->size(); ++l)
          {
            if (this->deltaMap->at(k)->at(0) == newStartState->at(l) && this->deltaMap->at(k)->at(1) == alphabetChar->at(0))
            {
              mergeUniquely(newEndState, epsilonClosure->closureOf(this->deltaMap->at(k)->at(2)));
            }
          }
        }
        if (newEndState->size() != 0)
        {
          newMapElement->push_back(newStartState);
          newMapElement->push_back(alphabetChar);
          newMapElement->push_back(newEndState);
          newMap->push_back(newMapElement);
        }
        else
        {
          delete newMapElement;
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
void DeltaGenerator::mergeUniquely(vector<string>* endSet, vector<string>* candidate)
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
}

/*
Iterates through the set of existing elements in the power set, and adds the new element only
if there is no existing copy of that set in the power set.
*/
void DeltaGenerator::insertUniqueElement(vector<vector<string>* >* results, vector<string>* entry)
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
Overloaded method for the power set delta generator.  Allows both the power set and
the initial mapping to be changed before the new delta function is produced.
*/
vector<vector<vector<string>* >* >* DeltaGenerator::powerSetDeltaMapGen(vector<vector<string>* >* transitionMap)
{
  this->setMapping(transitionMap);
  return this->powerSetDeltaMapGen();
}
