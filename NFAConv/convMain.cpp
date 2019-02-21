/*
Name: Trevor Kling
ID: 002270716
Email: kling109@mail.chapman.edu
Course: CPSC 406 Algorithm Analysis
Last Date Modified: 16 February 2019
Project: NFA to DFA Converter
*/

#include <vector>
#include <iostream>
#include "dfaGen.h"

using namespace std;

/*
Main function for the DFA converter.  Handles interfacing with the user, taking inputs for
file names.
*/
int main(int argc, char** argv)
{
  string inputFileName;
  string outputFileName;
  switch (argc)
  {
    case 1: cout << "Input a formatted file name: ";
            cin >> inputFileName;
            cout << "Input a desired output file name:";
            cin >> outputFileName;
            break;
    case 2: inputFileName = argv[1];
            cout << "Input a desired output file name:";
            cin >> outputFileName;
            break;
    default: inputFileName = argv[1];
             outputFileName = argv[2];
             break;
  }
  DFAGenerator* testGen = new DFAGenerator(inputFileName, outputFileName);
  testGen->generateDFA();
  testGen->~DFAGenerator();
  return 0;
}
