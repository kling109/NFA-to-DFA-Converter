/*
Name: Trevor Kling
ID: 002270716
Email: kling109@mail.chapman.edu
Course: CPSC 406 Algorithm Analysis
Last Date Modified: 11 February 2019
Project: NFA to DFA Converter
*/

#include <utility>
#include <ostream>
#include <list>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <math.h>

#ifndef NFACONVERTER_H
#define NFACONVERTER_H

class NFAConverter
{
    /*
    Contains the tools needed to convert a non-deterministic finite
    state automata to an equivalent deterministic finite-state automata.
    */
    private:
      std::string *alphabet;

      std::string *nfaStates;
      std::list<std::pair<std::string*, std::list<std::string>* > >* nfaDeltaFunc;
      std::string *nfaAcceptStates;
      std::string *nfaStartStates;

      std::string **dfaStates;
      std::list<std::pair<std::string*, std::list<std::string>* > >* dfaDeltaFunc;
      std::string **dfaAcceptStates;
      std::string **dfaStartStates;

      void fileReader(std::string inputFileName);
      void fileWriter(std::string outputFileName);
      std::string** powerSetGenerator(std::string* stateSet);

      std::list<std::string>* epsilonClosureGenerator(std::string state, std::list<std::pair<std::string*, std::list<std::string>* > >* delta);
      std::string** acceptStateGenerator(std::string* initalAcceptStates);
      std::string** startStateGenerator(std::string* initialStartStates);

    public:
      NFAConverter(void);
      void printList(std::list<std::string>* input);
      void uniqueList(std::list<std::list<std::string>* >* input);
      void powerSetHelper(std::list< std::list<std::string>* >* powerSet, std::list<std::string>* stateSet, int s);

      void arraySetGenerator(std::string** iterationSet, std::string* stateSet, int startpos, int maxsize, int currentIterationSize);
      int combination(int n, int r);
      int factorial(int n);
      void DFAGenerator(std::string inputFileName, std::string outputFileName);

};

#endif /* NFACONVERTER_H */
