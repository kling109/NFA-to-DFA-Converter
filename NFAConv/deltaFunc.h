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
  given an alphabet, an inital delta map, and a power set.
  */
  private:
    EpsilonClosureGenerator* epsilonClosure;
    std::vector<std::string>* alphabet;
    std::vector<std::vector<std::string>* >* deltaMap;
    std::vector<std::vector<std::string>* >* powerSet;
    std::vector<std::string>* mergeUniquely(std::vector<std::string>* endSet, std::vector<std::string>* candidate);
  public:
    DeltaGenerator();
    DeltaGenerator(std::vector<std::vector<std::string>* >* transitionMap);
    DeltaGenerator(std::vector<std::vector<std::string>* >* transitionMap, std::vector<std::vector<std::string>* >* set);
    DeltaGenerator(std::vector<std::vector<std::string>* >* transitionMap, std::vector<std::vector<std::string>* >* set, std::vector<std::string>* alph);
    ~DeltaGenerator();
    void setAlphabet(std::vector<std::string>* alph);
    void setMapping(std::vector<std::vector<std::string>* >* transitionMap);
    void setPowerSet(std::vector<std::vector<std::string>* >* set);
    std::vector<std::vector<std::vector<std::string>* >* >* powerSetDeltaMapGen();
    std::vector<std::vector<std::vector<std::string>* >* >* powerSetDeltaMapGen(std::vector<std::vector<std::string>* >* set);
    std::vector<std::vector<std::vector<std::string>* >* >* powerSetDeltaMapGen(std::vector<std::vector<std::string>* >* transitionMap, std::vector<std::vector<std::string>* >* set);
};

#endif /* DELTAFUNC_H */
