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

#ifndef FILEIO_H
#define FILEIO_H

class FileIO
{
  /*
  Provides methods for processing DFA formatted files.
  */
  private:
    std::string inputFileName;
    std::string outputFileName;
    std::vector<std::string>* stateSet;
    std::vector<std::string>* alphabet;
    std::vector<std::vector<std::string>* >* deltaFunc;
    std::vector<std::string>* startStates;
    std::vector<std::string>* acceptStates;
    std::vector<std::string>* stringSplitter(std::string input, std::string delimiters);
    void insertUniqueElement(std::vector<std::string>* results, std::string input);
  public:
    FileIO();
    FileIO(std::string inputFileName);
    FileIO(std::string inputFileName, std::string outputFileName);
    ~FileIO();
    void readFile();
    void readFile(std::string fileName);
    void writeFile(std::vector<std::vector<std::string>* >* powerSet, std::vector<std::string>* alphabet, std::vector<std::vector<std::vector<std::string>* >* >* map, std::vector<std::vector<std::string>* >* startSet, std::vector<std::vector<std::string>* >* acceptSet);
    void writeFile(std::string fileName, std::vector<std::vector<std::string>* >* powerSet, std::vector<std::string>* alphabet, std::vector<std::vector<std::vector<std::string>* >* >* map, std::vector<std::vector<std::string>* >* startSet, std::vector<std::vector<std::string>* >* acceptSet);
    std::vector<std::string>* getStates();
    std::vector<std::string>* getAlphabet();
    std::vector<std::vector<std::string>* >* getDelta();
    std::vector<std::string>* getStartStates();
    std::vector<std::string>* getAcceptStates();
};

#endif /* FILEIO_H */
