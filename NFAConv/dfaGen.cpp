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
#include "dfaGen.h"

using namespace std;

DFAGenerator::DFAGenerator()
{
  this->inputFileName = "NULL";
  this->outputFileName = "NULL";
}

DFAGenerator::DFAGenerator(string inputFile)
{
  this->inputFileName = inputFile;
  this->outputFileName = "NULL";
}

DFAGenerator::DFAGenerator(string inputFile, string outputFile)
{
  this->inputFileName = inputFile;
  this->outputFileName = outputFile;
}

DFAGenerator::~DFAGenerator()
{

}

void DFAGenerator::setInputFile(string inputFile)
{
  this->inputFileName = inputFile;
}

void DFAGenerator::setOutputFile(string outputFile)
{
  this->outputFileName = outputFile;
}

void DFAGenerator::generateDFA()
{

}

void DFAGenerator::generateDFA(string inputFile)
{
  setInputFile(inputFile);
  generateDFA();
}

void DFAGenerator::printDFA()
{

}

void DFAGenerator::printDFA(string outputFile)
{
  setOutputFile(outputFile);
  printDFA();
}
