/*
Name: Trevor Kling
ID: 002270716
Email: kling109@mail.chapman.edu
Course: CPSC 406 Algorithm Analysis
Last Date Modified: 16 February 2019
Project: NFA to DFA Converter
*/

#include <vector>
#include <string>
#include "fileIO.h"
#include "epsilon.h"
#include "deltaFunc.h"
#include "powerSetGen.h"

#ifndef DFAGEN_H
#define DFAGEN_H

class DFAGenerator
{
  /*
  Provides the workflow for producing a new DFA given
  a NFA as input.  Takes a formatted file as input, and
  returns a formatted file as output.
  */
  private:
    std::string inputFileName;
    std::string outputFileName;
  public:
    DFAGenerator();
    DFAGenerator(std::string inputFile);
    DFAGenerator(std::string inputFile, std::string outputFile);
    ~DFAGenerator();
    void setInputFile(std::string inputFile);
    void setOutputFile(std::string outputFile);
    void generateDFA();
    void generateDFA(std::string inputFile);
    void generateDFA(std::string inputFile, std::string outputFile);
};

#endif /* DFAGEN_H */
