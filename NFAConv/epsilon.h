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

#ifndef EPSILON_H
#define EPSILON_H

class EpsilonClosureGenerator
{
  /*
  Provides the methods required to find the epsilon closure of a set, given a
  particular mapping.
  */
  private:
    std::vector<std::vector<std::string>* >* deltaMap;
    void insertUniqueElement(std::vector<std::string>* set, std::string element);
  public:
    EpsilonClosureGenerator();
    EpsilonClosureGenerator(std::vector<std::vector<std::string>* >* transitionMap);
    ~EpsilonClosureGenerator();
    void setMapping(std::vector<std::vector<std::string>* >* transitionMap);
    std::vector<std::string>* closureOf(std::string state);
    std::vector<std::string>* closureOf(std::vector<std::string>* powerState);
};

#endif /* EPSILON_H */
