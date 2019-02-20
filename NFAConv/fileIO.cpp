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
#include <iostream>
#include <fstream>
#include <sstream>
#include "fileIO.h"

using namespace std;

/*
Default constructor for a file IO class.  Initializes
pointers to null so they can be tested later.
*/
FileIO::FileIO()
{
  this->inputFileName = "NULL";
  this->outputFileName = "NULL";
  this->stateSet = new vector<string>();
  this->alphabet = NULL;
  this->deltaFunc = new vector<vector<string>* >();
  this->startStates = NULL;
  this->acceptStates = NULL;
}

/*
Overloaded constructor for a file IO class.  Sets the input
file name.
*/
FileIO::FileIO(string inputFile)
{
  this->inputFileName = inputFile;
  this->outputFileName = "NULL";
  this->stateSet = new vector<string>();
  this->alphabet = NULL;
  this->deltaFunc = new vector<vector<string>* >();
  this->startStates = NULL;
  this->acceptStates = NULL;
}

/*
Overloaded constructor for a file IO class.  Sets the input
file and output file names.
*/
FileIO::FileIO(string inputFile, string outputFile)
{
  this->inputFileName = inputFile;
  this->outputFileName = outputFile;
  this->stateSet = new vector<string>();
  this->alphabet = NULL;
  this->deltaFunc = new vector<vector<string>* >();
  this->startStates = NULL;
  this->acceptStates = NULL;
}

/*
Standard deconstructor function.
*/
FileIO::~FileIO()
{
  delete this->stateSet;
  delete this->deltaFunc;
}

/*
Reads in a given file, if formatted properly.  The file reads the file in
line by line, processing it according to the line found.  Primary work on the
lines is done by the stringSplitter helper method.
*/
void FileIO::readFile()
{
  if (this->inputFileName == "NULL")
  {
    cout << "A file must be provided to the program." << endl;
  }
  else
  {
    ifstream inputStream (this->inputFileName.c_str());
    string line;
    int lineNum = 0;
    while (getline(inputStream, line, '\n'))
    {
      switch(lineNum)
      {
        case 0: break;
        case 1: alphabet = stringSplitter(line, "\t \n");
                break;
        case 2: startStates = stringSplitter(line, "\t \n");
                break;
        case 3: acceptStates = stringSplitter(line, "\t \n");
                break;
        default: vector<string>* mapping = stringSplitter(line, "\t =,\n");
                 this->deltaFunc->push_back(mapping);
                 insertUniqueElement(stateSet, mapping->at(0));
                 break;
      }
      ++lineNum;
    }
    inputStream.close();
  }
}

/*
Iterates through the set of existing elements in the power set, and adds the new element only
if there is no existing copy of that set in the power set.
*/
void FileIO::insertUniqueElement(vector<string>* results, string entry)
{
  bool unique = true;
  for (int i = 0; i < results->size(); ++i)
  {
    if (results->at(i) == entry)
    {
      unique = false;
      break;
    }
  }
  if (unique)
  {
    results->push_back(entry);
  }
}

/*
Helper method for processign strings.  Each string taken in is split at
each delimiter, and then the non-delimiter portion of the string is pushed
into a vector.  This vector is then returned.
*/
vector<string>* FileIO::stringSplitter(string input, string delimiters)
{
  int pos = 0;
  int delim = 0;
  vector<string>* output = new vector<string>();
  while (pos != -1)
  {
    delim = input.find_first_of(delimiters, pos);
    output->push_back(input.substr(pos, delim - pos));
    pos = input.find_first_not_of(delimiters, delim);
  }
  return output;
}

/*
Overloaded file read method.  Simply sets the input file name, then calls
the read funciton.
*/
void FileIO::readFile(string fileName)
{
  this->inputFileName = fileName;
  readFile();
}

/*
A file output method for a given set of DFA parameters.  The function takes
inputs of vectors, and processes them to give proper formatting to all elements
being printed to the file.  The states are surrounded by braces and separated by tabs,
while the alphabet characters are simply separated.
File:
Line 1: State set {q1}, {q2}, ...
Line 2: alphabet a, b, c, ...
Line 3: Start State(s) {s1}, {s2}, ...
Line 4: Accept State(s) {a1}, {a2}, ...
Line >5: Delta function definitions {q1},a = {q2}
*/
void FileIO::writeFile(vector<vector<string>* >* powerSet, vector<string>* alphabet, vector<vector<vector<string>* >* >* map, vector<vector<string>* >* startSet, vector<vector<string>* >* acceptSet)
{
  if (this->outputFileName == "NULL")
  {
    cout << "A file has not been provided." << endl;
  }
  else
  {
    ofstream outputStream (this->outputFileName.c_str());
    for (int i = 0; i < powerSet->size(); ++i)
    {
      outputStream << "{";
      for (int j = 0; j < powerSet->at(i)->size(); ++j)
      {
        outputStream << powerSet->at(i)->at(j);
      }
      outputStream << "}  ";
    }
    outputStream << endl;
    for (int i = 0; i < alphabet->size(); ++i)
    {
      outputStream << alphabet->at(i) << "  ";
    }
    outputStream << endl;
    for (int i = 0; i < startSet->size(); ++i)
    {
      outputStream << "{";
      for (int j = 0; j < startSet->at(i)->size(); ++j)
      {
        outputStream << startSet->at(i)->at(j);
      }
      outputStream << "}  ";
    }
    outputStream << endl;
    for (int i = 0; i < acceptSet->size(); ++i)
    {
      outputStream << "{";
      for (int j = 0; j < acceptSet->at(i)->size(); ++j)
      {
        outputStream << acceptSet->at(i)->at(j);
      }
      outputStream << "}  ";
    }
    outputStream << endl;
    for (int i = 0; i < map->size(); ++i)
    {
      for (int j = 0; j < map->at(i)->size(); ++j)
      {
        outputStream << "{";
        for (int k = 0; k < map->at(i)->at(j)->size(); ++k)
        {
          outputStream << map->at(i)->at(j)->at(k);
        }
        outputStream << "}";
        if (j == 0)
        {
          outputStream << ",";
        }
        else if (j == 1)
        {
          outputStream << " = ";
        }
        else if (j == 2)
        {
          outputStream << endl;
        }
      }
    }
    outputStream.close();
  }
}

/*

*/
void FileIO::writeFile(string fileName, vector<vector<string>* >* powerSet, vector<string>* alphabet, vector<vector<vector<string>* >* >* map, vector<vector<string>* >* startSet, vector<vector<string>* >* acceptSet)
{
  this->outputFileName = fileName;
  writeFile(powerSet, alphabet, map, startSet, acceptSet);
}

/*
Accessor method for the state Set found by a read function.
*/
vector<string>* FileIO::getStates()
{
  return this->stateSet;
}

/*
Accessor method for the alphabet found by a read function.
*/
vector<string>* FileIO::getAlphabet()
{
  return this->alphabet;
}

/*
Accessor method for the delta funciton found by a read function.
*/
vector<vector<string>* >* FileIO::getDelta()
{
  return this->deltaFunc;
}

/*
Accessor method for the start state set found by a read function.
*/
vector<string>* FileIO::getStartStates()
{
  return this->startStates;
}

/*
Accessor method for the accept state set found by a read function.
*/
vector<string>* FileIO::getAcceptStates()
{
  return this->acceptStates;
}
