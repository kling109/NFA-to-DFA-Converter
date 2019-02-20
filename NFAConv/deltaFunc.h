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
#include "epsilon.h"

#ifndef DELTAFUNC_H
#define DELTAFUNC_H

class DeltaGenerator
{
  /*
  Provides the tools to produce a new transition function,
  given an initial delta map.
  */
  private:
    EpsilonClosureGenerator* epsilonClosure;
    std::vector<std::vector<std::string>* >* deltaMap;
    std::vector<std::string>* mergeUniquely(std::vector<std::string>* endSet, std::vector<std::string>* candidate);
  public:
    DeltaGenerator();
    DeltaGenerator(std::vector<std::vector<std::string>* >* transitionMap);
    ~DeltaGenerator();
    void setMapping(std::vector<std::vector<std::string>* >* transitionMap);
    std::vector<std::vector<std::vector<std::string>* >* >* powerSetDeltaMapGen();
    std::vector<std::vector<std::vector<std::string>* >* >* powerSetDeltaMapGen(std::vector<std::vector<std::string>* >* transitionMap);
};

#endif /* DELTAFUNC_H */
