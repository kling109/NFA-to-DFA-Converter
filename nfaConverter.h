/*
Name: Trevor Kling
ID: 002270716
Email: kling109@mail.chapman.edu
Course: CPSC 406 Algorithm Analysis
Last Date Modified: 11 February 2019
Project: NFA to DFA Converter
*/

#include <map>
#include <set>
#include <iostream>
#include <fstream>

#ifndef NFACONVERTER_H
#define NFACONVERTER_H

class nfaConverter
{
    /*
    Contains the tools needed to convert a non-deterministic finite
    state automata to an equivalent deterministic finite-state automata.
    */
    private:
      std::string *alphabet;

      std::string *nfaStates;
      std::map<std::set<std::string*>,std::set<std::string*>> nfaDeltaFunc;
      std::string **nfaAcceptStates;
      std::string **nfaStartStates;

      std::string *dfaStates;
      std::map<std::set<std::string*>,std::set<std::string*>> dfaDeltaFunc;
      std::string **dfaAcceptStates;
      std::string **dfaStartStates;

      void fileReader(std::string inputFileName);
      void fileWriter(std::string outputFileName);
      std::string* powerSetGenerator(std::string* stateSet);
      std::string** epsilonClosureGenerator(std::string* state, std::map<std::set<std::string*>,std::set<std::string*>>* delta);
      std::string** acceptStateGenerator(std::string** initalAcceptStates);
      std::string** startStateGenerator(std::string** initialStartStates);

    public:
      void DFAGenerator(std::string inputFileName, std::string outputFileName);

};

#endif /* NFACONVERTER_H */
