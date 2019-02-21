/*
Name: Trevor Kling
ID: 002270716
Email: kling109@mail.chapman.edu
Course: CPSC 406 Algorithm Analysis
Last Date Modified: 21 February 2019
Project: NFA to DFA Converter
*/

#include <vector>
#include <string>
#include <iostream>
#include "fileIO.h"
#include "epsilon.h"
#include "deltaFunc.h"
#include "powerSetGen.h"
#include "dfaGen.h"

using namespace std;

/*
Standard Constructor method.  The names are initialized to "NULL" so it can be
checked if they have been given later.
*/
DFAGenerator::DFAGenerator()
{
  this->inputFileName = "NULL";
  this->outputFileName = "NULL";
}

/*
Overloaded Constructor method that sets the input file name.
*/
DFAGenerator::DFAGenerator(string inputFile)
{
  this->inputFileName = inputFile;
  this->outputFileName = "NULL";
}

/*
Overloaded Constructor method that sets the input file and output file name.
*/
DFAGenerator::DFAGenerator(string inputFile, string outputFile)
{
  this->inputFileName = inputFile;
  this->outputFileName = outputFile;
}

/*
Standard Deconstructor method.
*/
DFAGenerator::~DFAGenerator()
{

}

/*
Setter method for the input file.
*/
void DFAGenerator::setInputFile(string inputFile)
{
  this->inputFileName = inputFile;
}

/*
Setter method for the output file.
*/
void DFAGenerator::setOutputFile(string outputFile)
{
  this->outputFileName = outputFile;
}

/*
Main data handling method for the DFA generator.  The method takes a supplied file name and
supplied output name, and subsequently reads in the file.  The process then uses the
DeltaGenerator to make a new delta map.  This map is then used to find the new set of states.
Subsequently, the epsilon closure of the given accept states and start states is taken to find
new start/accept states.  Finally, all of this information is written to the given output file,
and all the data is deleted.
*/
void DFAGenerator::generateDFA()
{
  if (this->inputFileName != "NULL" && this->outputFileName != "NULL")
  {
    FileIO* fileManager = new FileIO(this->inputFileName, this->outputFileName);
    fileManager->readFile();
    // Building the new map
    DeltaGenerator* dg = new DeltaGenerator(fileManager->getDelta());
    vector<vector<vector<string>* >* >* newDelta = dg->powerSetDeltaMapGen();
    // Building the new set of elements
    PowerSetGenerator* psg = new PowerSetGenerator(newDelta);
    psg->buildPowerSet();
    vector<vector<string>* >* newSet = psg->getPowerSet();
    // Obtaining the new set of start and accept states
    vector<vector<string>* >* newStartStates = new vector<vector<string>* >();
    EpsilonClosureGenerator* ecg = new EpsilonClosureGenerator(fileManager->getDelta());
    for (int i = 0; i < fileManager->getStartStates()->size(); ++i)
    {
      newStartStates->push_back(ecg->closureOf(fileManager->getStartStates()->at(i)));
    }
    vector<vector<string>* >* newAcceptStates = new vector<vector<string>* >();
    for (int i = 0; i < fileManager->getAcceptStates()->size(); ++i)
    {
      newAcceptStates->push_back(ecg->closureOf(fileManager->getAcceptStates()->at(i)));
    }
    // Writing the obtained information to a file
    fileManager->writeFile(newSet, fileManager->getAlphabet(), newDelta, newStartStates, newAcceptStates);
    fileManager->~FileIO();
    // Clearing all allocated data
    ecg->~EpsilonClosureGenerator();
    psg->~PowerSetGenerator();
    dg->~DeltaGenerator();
    delete newStartStates;
    delete newAcceptStates;
  }
  else
  {
    cout << "The files have not been set." << endl;
  }
}

/*
Overloaded DFA generator method.  Sets the input file name, then generates the DFA.
*/
void DFAGenerator::generateDFA(string inputFile)
{
  setInputFile(inputFile);
  generateDFA();
}

/*
Overloaded DFA generator method.  Sets the input file name, the output
file name, and generates the DFA.
*/
void DFAGenerator::generateDFA(string inputFile, string outputFile)
{
  setInputFile(inputFile);
  setOutputFile(outputFile);
  generateDFA();
}
