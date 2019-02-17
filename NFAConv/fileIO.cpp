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

FileIO::FileIO()
{
  this->inputStream = NULL;
  this->outputStream = NULL;
  this->stateSet = NULL;
  this->alphabet = NULL;
  this->deltaFunc = new vector<vector<string>* >();
  this->startStates = NULL;
  this->acceptStates = NULL;
}

FileIO::FileIO(string inputFileName)
{
  this->inputStream = new ifstream(inputFileName.c_str());
  this->outputStream = NULL;
  this->stateSet = NULL;
  this->alphabet = NULL;
  this->deltaFunc = new vector<vector<string>* >();
  this->startStates = NULL;
  this->acceptStates = NULL;
}

FileIO::FileIO(string inputFileName, string outputFileName)
{
  this->inputStream = new ifstream(inputFileName.c_str());
  this->outputStream = new  ofstream(outputFileName.c_str());
  this->stateSet = NULL;
  this->alphabet = NULL;
  this->deltaFunc = new vector<vector<string>* >();
  this->startStates = NULL;
  this->acceptStates = NULL;
}

void FileIO::readFile()
{
  if (!inputStream->is_open())
  {
    cout << "A file must be provided to the program." << endl;
  }
  else
  {
    string line;
    int lineNum = 0;
    while (getline(*inputStream, line, '\n'))
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
  }
}

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

void FileIO::readFile(string fileName)
{
  if (inputStream == NULL)
  {
    this->inputStream = new ifstream(fileName.c_str());
  }
  else
  {
    delete this->inputStream;
    this->inputStream = new ifstream(fileName.c_str());
  }
  readFile();
}

void FileIO::writeFile(vector<vector<string>* >* powerSet, vector<string>* alphabet, vector<vector<vector<string>* >* >* map, vector<vector<string>* >* startSet, vector<vector<string>* >* acceptSet)
{

}

void FileIO::writeFile(string fileName, vector<vector<string>* >* powerSet, vector<string>* alphabet, vector<vector<vector<string>* >* >* map, vector<vector<string>* >* startSet, vector<vector<string>* >* acceptSet)
{
  if (outputStream == NULL)
  {
    this->outputStream = new ofstream(fileName.c_str());
  }
  else
  {
    delete this->outputStream;
    this->outputStream = new ofstream(fileName.c_str());
  }
  writeFile(powerSet, alphabet, map, startSet, acceptSet);
}

vector<string>* FileIO::getStates()
{
  return this->stateSet;
}

vector<string>* FileIO::getAlphabet()
{
  return this->alphabet;
}

vector<vector<string>* >* FileIO::getDelta()
{
  return this->deltaFunc;
}

vector<string>* FileIO::getStartStates()
{
  return this->startStates;
}

vector<string>* FileIO::getAcceptStates()
{
  return this->acceptStates;
}
