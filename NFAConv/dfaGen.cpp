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
  if (this->inputFileName != "NULL" && this->outputFileName != "NULL")
  {
    FileIO* fileManager = new FileIO(this->inputFileName, this->outputFileName);
    fileManager->readFile();
    EpsilonClosureGenerator* ecg = new EpsilonClosureGenerator(fileManager->getDelta());
    PowerSetGenerator* psg = new PowerSetGenerator(fileManager->getStates());
    psg->buildPowerSet();
    vector<vector<string>* >* newSet = psg->getPowerSet();
    DeltaGenerator* dg = new DeltaGenerator(fileManager->getDelta(), newSet, fileManager->getAlphabet());
    vector<vector<string>* >* newStartStates = new vector<vector<string>* >();
    for (int i = 0; i < fileManager->getStartStates()->size(); ++i)
    {
      newStartStates->push_back(ecg->closureOf(fileManager->getStartStates()->at(i)));
    }
    vector<vector<string>* >* newAcceptStates = new vector<vector<string>* >();
    for (int i = 0; i < fileManager->getAcceptStates()->size(); ++i)
    {
      newAcceptStates->push_back(ecg->closureOf(fileManager->getAcceptStates()->at(i)));
    }
    vector<vector<vector<string>* >* >* newDelta = dg->powerSetDeltaMapGen();
    fileManager->writeFile(newSet, fileManager->getAlphabet(), newDelta, newStartStates, newAcceptStates);
  }
  else
  {
    cout << "The files have not been set." << endl;
  }
}

void DFAGenerator::generateDFA(string inputFile)
{
  setInputFile(inputFile);
  generateDFA();
}

void DFAGenerator::generateDFA(string inputFile, string outputFile)
{
  setInputFile(inputFile);
  setOutputFile(outputFile)
  generateDFA();
}
