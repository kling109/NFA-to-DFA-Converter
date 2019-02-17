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

#ifndef DFAGEN_H
#define DFAGEN_H

class DFAGenerator
{
  private:
    std::string inputFileName;
    std::string outputFileName;
  public:
    DFAGenerator();
    DFAGenerator(std::string inputFile);
    DFAGenerator(std::string inputFile, std::string outputFile);
    void setInputFile(std::string inputFile);
    void setOutputFile(std::string outputFile);
    void generateDFA();
    void generateDFA(std::string inputFile);
    void printDFA();
    void printDFA(std::string outputFile);
}

#endif /* DFAGEN_H */
