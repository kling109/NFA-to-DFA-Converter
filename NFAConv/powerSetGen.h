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

#ifndef POWERSETGEN_H
#define POWERSETGEN_H

class PowerSetGenerator
{
  /*
  Produces a power set for a given input of an initial map.  Uses string vectors
  for the input, and outputs a new string vector.
  */
  private:
    std::vector<std::vector<std::vector<std::string>* >* >* sourceMap;
    std::vector<std::vector<std::string>* >* powerSet;
    void insertUniqueElement(std::vector<std::vector<std::string>* >* results, std::vector<std::string>* input);
  public:
    PowerSetGenerator();
    PowerSetGenerator(std::vector<std::vector<std::vector<std::string>* >* >* map);
    ~PowerSetGenerator();
    void buildPowerSet();
    void buildPowerSet(std::vector<std::vector<std::vector<std::string>* >* >* map);
    std::vector<std::vector<std::string>* >* getPowerSet();
    std::vector<std::vector<std::string>* >* getPowerSet(std::vector<std::vector<std::string>* >* map);
    std::vector<std::vector<std::string>* >* getPowerSet(std::vector<std::vector<std::vector<std::string>* >* >* map);
};

#endif /* POWERSETGEN_H */
