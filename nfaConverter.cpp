/*
Name: Trevor Kling
ID: 002270716
Email: kling109@mail.chapman.edu
Course: CPSC 406 Algorithm Analysis
Last Date Modified: 11 February 2019
Project: NFA to DFA Converter
*/

#include "nfaConverter.h"

using namespace std;

void nfaConverter::fileReader(string* inputFileName)
{
  if (inputFileName)
  {
    ifstream nfaFile (*inputFileName);
    if (nfaFile.is_open())
    {
      string currentLine;
      getline(nfaFile, currentLine);
      int numStates = 0;
      for (int i = 0; i < currentLine.size(); ++i)
      {
        if (currentLine[i] == '\t')
        {
          ++numStates;
        }
      }
      int lastpos = 0;
      nfaStates = new string[numStates];
      for (int i = 0; i < numStates; ++i)
      {
        nfaStates[i] = currentLine.substr(lastpos, currentLine.find('\t'));
        lastpos = currentLine.find('\t');
      }
      getline(nfaFile, currentLine);
      int numSymbols = 0;
      for (int i = 0; i < currentLine.size(); ++i)
      {
        if (currentLine[i] == '\t')
        {
          ++numSymbols;
        }
      }
      lastpos = 0;
      alphabet = new string[numSymbols];
      for (int i = 0; i < numSymbols; ++i)
      {
        alphabet[i] = currentLine.substr(lastpos, currentLine.find('\t'));
        lastpos = currentLine.find('\t');
      }
      getline(nfaFile, currentLine);
      nfaStartStates = new string*[1];
      int position = 0;
      for (int i = 0; i < numStates; ++i)
      {
        if (nfaStates[i] == currentLine)
        {
          nfaStartStates[position] = &nfaStates[i];
          ++position;
        }
      }
      getline(nfaFile, currentLine);
      int numAcceptStates = 0;
      for (int i = 0; i < currentLine.size(); ++i)
      {
        if (currentLine[i] == '\t')
        {
          ++numAcceptStates;
        }
      }
      nfaAcceptStates = new string*[numAcceptStates];
      string currentState;
      for (int i = 0; i < numAcceptStates; ++i)
      {
        currentState = strtok(currentLine, '\t');
        for (int j = 0; j < numStates; ++j)
        {
          if (nfaStates[j] == currentState)
          {
            nfaAcceptStates[i] = &nfaStates[j];
          }
        }
      }
      while (getline(nfaFile, currentLine))
      {
        string state = strtok(currentLine, " ,");
        string symbol = strtok(currentLine, " =");
        string transitionState = strtok(currentLine, " ");
      }
      nfaFile.close();
    }
  }
  else
  {
    std::cout << "The input file has not been set." << '\n';
  }
}

int main()
{
  printf("%s\n", "Compiled");
}
