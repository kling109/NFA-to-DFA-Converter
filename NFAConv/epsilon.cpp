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
#include "epsilon.h"

using namespace std;

EpsilonClosureGenerator::EpsilonClosureGenerator()
{
  this->deltaMap = NULL;
}

EpsilonClosureGenerator::EpsilonClosureGenerator(vector<vector<string>* >* transitionMap)
{
  this->deltaMap = transitionMap;
}

EpsilonClosureGenerator::~EpsilonClosureGenerator()
{
  if (this->deltaMap != 0)
  {
    delete this->deltaMap;
  }
}

void EpsilonClosureGenerator::setMapping(vector<vector<string>* >* transitionMap)
{
  this->deltaMap = transitionMap;
}

vector<string>* EpsilonClosureGenerator::closureOf(string state)
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

vector<string>* EpsilonClosureGenerator::closureOf(vector<string>* powerState)
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
