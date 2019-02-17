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
  this->powerSet = NULL;
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
  this->powerSet = NULL;
  this->alphabet = NULL;
}

/*
Overloaded constructor for a Delta Generator.  Establishes values for both transitions
and the input set.
*/
DeltaGenerator::DeltaGenerator(vector<vector<string>* >* transitionMap, vector<vector<string>* >* set)
{
  this->epsilonClosure = new EpsilonClosureGenerator(transitionMap);
  this->deltaMap = transitionMap;
  this->powerSet = set;
  this->alphabet = NULL;
}

/*
Overloaded constructor for a Delta Generator.  Establishes values for all objects.
*/
DeltaGenerator::DeltaGenerator(vector<vector<string>* >* transitionMap, vector<vector<string>* >* set, vector<string>* alph)
{
  this->epsilonClosure = new EpsilonClosureGenerator(transitionMap);
  this->deltaMap = transitionMap;
  this->powerSet = set;
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
Setter method for the given alphabet.
*/
void DeltaGenerator::setAlphabet(vector<string>* alph)
{
  this->alphabet = alph;
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
Setter method for the given power set.
*/
void DeltaGenerator::setPowerSet(vector<vector<string>* >* set)
{
  this->powerSet = set;
}

/*
Produces a new delta function based on the set of inputs.  The function begins by
establishing the existence of a mapping, a powerset, and an alphabet as they are
essential to the program.  If all three are initialized, then the function produces a new
vector object to contain the new mapping.  The inputs to this map will be vectors of vectors, as
each power set object itself is a vector.  The format of the new mapping is now a nested
vector, where the initial vector contains vectors corresponding to the delta mappings, with
the first vector in the double nested vector being the input states, the second being the
alphabet character, and the third being the end state.  This vector is produced by iterating
over all combinations of power set elements and alphabet characters, then finding what power set
element all their mappings constitute.
*/
vector<vector<vector<string>* >* >* DeltaGenerator::powerSetDeltaMapGen()
{
  if (this->deltaMap == 0 || this->powerSet == 0 || this->alphabet == 0)
  {
    cout << "A mapping or a set was not provided." << endl;
  }
  else
  {
    vector<vector<vector<string>* >* >* newMap = new vector<vector<vector<string>* >* >();
    for (int i = 0; i < this->powerSet->size(); ++i)
    {
      vector<string>* element = this->powerSet->at(i);
      for (int j = 0; j < this->alphabet->size(); ++j)
      {
        string character = this->alphabet->at(j);
        vector<vector<string>* >* newMapEntry = new vector<vector<string>* >();
        vector<string>* charContainer = new vector<string>();
        charContainer->push_back(character);
        vector<string>* endState = new vector<string>();
        for (int k = 0; k < element->size(); ++k)
        {
          for (int l = 0; l < deltaMap->size(); ++l)
          {
            vector<string>* mapping = deltaMap->at(l);
            if (mapping->at(0) == element->at(k) && mapping->at(1) == character)
            {
              endState = mergeUniquely(endState, epsilonClosure->closureOf(mapping->at(2)));
            }
          }
        }
        newMapEntry->push_back(element);
        newMapEntry->push_back(charContainer);
        newMapEntry->push_back(endState);
        newMap->push_back(newMapEntry);
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
Overloaded method for the power set delta generator.  Allows the power set to
be changed before the new delta function is produced.
*/
vector<vector<vector<string>* >* >* DeltaGenerator::powerSetDeltaMapGen(vector<vector<string>* >* set)
{
  this->setPowerSet(set);
  return this->powerSetDeltaMapGen();
}

/*
Overloaded method for the power set delta generator.  Allows both the power set and
the initial mapping to be changed before the new delta function is produced.
*/
vector<vector<vector<string>* >* >* DeltaGenerator::powerSetDeltaMapGen(vector<vector<string>* >* transitionMap, vector<vector<string>* >* set)
{
  this->setMapping(transitionMap);
  this->setPowerSet(set);
  return this->powerSetDeltaMapGen();
}
