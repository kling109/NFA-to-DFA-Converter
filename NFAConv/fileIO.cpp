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

*/
FileIO::FileIO()
{
  this->inputFileName = "NULL";
  this->outputFileName = "NULL";
  this->stateSet = NULL;
  this->alphabet = NULL;
  this->deltaFunc = new vector<vector<string>* >();
  this->startStates = NULL;
  this->acceptStates = NULL;
}

/*

*/
FileIO::FileIO(string inputFile)
{
  this->inputFileName = inputFile;
  this->outputFileName = "NULL";
  this->stateSet = NULL;
  this->alphabet = NULL;
  this->deltaFunc = new vector<vector<string>* >();
  this->startStates = NULL;
  this->acceptStates = NULL;
}

/*

*/
FileIO::FileIO(string inputFile, string outputFile)
{
  this->inputFileName = inputFile;
  this->outputFileName = outputFile;
  this->stateSet = NULL;
  this->alphabet = NULL;
  this->deltaFunc = new vector<vector<string>* >();
  this->startStates = NULL;
  this->acceptStates = NULL;
}

/*

*/
FileIO::~FileIO()
{
  delete this->deltaFunc;
}

/*

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
        case 0: stateSet = stringSplitter(line, "\t ");
                break;
        case 1: alphabet = stringSplitter(line, "\t ");
                break;
        case 2: startStates = stringSplitter(line, "\t ");
                break;
        case 3: acceptStates = stringSplitter(line, "\t ");
                break;
        default: vector<string>* mapping = stringSplitter(line, "\t =,");
                 deltaFunc->push_back(mapping);
                 break;
      }
      ++lineNum;
    }
    inputStream.close();
  }
}

/*

*/
vector<string>* FileIO::stringSplitter(string input, string delimiters)
{
  int pos = 0;
  int delim = 0;
  vector<string>* output = new vector<string>();
  while (pos != input.size())
  {
    delim = input.find(delimiters, pos);
    output->push_back(input.substr(pos, delim - pos));
    pos = input.find_first_not_of(delimiters, delim);
  }
  return output;
}

/*

*/
void FileIO::readFile(string fileName)
{
  this->inputFileName = fileName;
  readFile();
}

/*

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
        outputStream << powerSet->at(i)->at(j) << " ";
      }
      outputStream << "}  ";
    }
    outputStream << endl;
    for (int i = 0; i < alphabet->size(); ++i)
    {
      outputStream << alphabet->at(i) << "  " << endl;
    }
    outputStream << endl;
    for (int i = 0; i < startSet->size(); ++i)
    {
      outputStream << "{";
      for (int j = 0; j < startSet->at(i)->size(); ++j)
      {
        outputStream << startSet->at(i)->at(j) << " ";
      }
      outputStream << "}  ";
    }
    outputStream << endl;
    for (int i = 0; i < acceptSet->size(); ++i)
    {
      outputStream << "{";
      for (int j = 0; j < acceptSet->at(i)->size(); ++j)
      {
        outputStream << acceptSet->at(i)->at(j) << " ";
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
          outputStream << map->at(i)->at(j)->at(k) << " ";
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

*/
vector<string>* FileIO::getStates()
{
  return this->stateSet;
}

/*

*/
vector<string>* FileIO::getAlphabet()
{
  return this->alphabet;
}

/*

*/
vector<vector<string>* >* FileIO::getDelta()
{
  return this->deltaFunc;
}

/*

*/
vector<string>* FileIO::getStartStates()
{
  return this->startStates;
}

/*

*/
vector<string>* FileIO::getAcceptStates()
{
  return this->acceptStates;
}
