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

NFAConverter::NFAConverter(void)
{

}

void NFAConverter::DFAGenerator(string inputFileName, string outputFileName)
{
  NFAConverter::fileReader(inputFileName);
  NFAConverter::dfaStates = NFAConverter::powerSetGenerator(NFAConverter::nfaStates);
  for (int i = 0; i < NFAConverter::dfaStates->size(); ++i)
  {
    for (int j = 0; j < NFAConverter::alphabet->size(); ++j)
    {
      string* deltaKey = NFAConverter::dfaStates[i];
    }
  }
}

int main()
{

}

/*void nfaConverter::printsystem()
{
  for (int i = 0; i < nfaConverter::alphabet->size(); ++i)
  {
    cout << "Alphabet: " << nfaConverter::alphabet[i] << endl;
  }
  for (int i = 0; i < nfaConverter::nfaStates->size(); ++i)
  {
    cout << "States: " << nfaConverter::nfaStates[i] << endl;
  }
  cout << "Start States: " << **nfaConverter::nfaStartStates << endl;
  cout << "Accept States: " << *nfaConverter::nfaAcceptStates << endl;
  //cout << "Delta Function: " << nfaConverter::nfaDeltaFunc << endl;
}

void nfaConverter::fileReader(string inputFileName)
{
  ifstream nfaFile (inputFileName.c_str());
  if (nfaFile.is_open())
  {
    string currentLine;
    getline(nfaFile, currentLine);
    int numStates = 1;
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
      nfaStates[i] = currentLine.substr(lastpos, currentLine.find('\t', lastpos));
      lastpos = currentLine.find('\t', lastpos);
    }
    getline(nfaFile, currentLine);
    int numSymbols = 1;
    for (int i = 0; i < currentLine.size(); ++i)
    {
      if (currentLine[i] == '\t')
      {
        ++numSymbols;
      }
    }
    lastpos = 0;
    alphabet = new string[numSymbols+1];
    for (int i = 0; i < numSymbols; ++i)
    {
      alphabet[i] = currentLine.substr(lastpos, currentLine.find('\t', lastpos));
      lastpos = currentLine.find('\t', lastpos);
    }
    alphabet[numSymbols] = "EPS";
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
    int numAcceptStates = 1;
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
      currentState = currentLine.substr(lastpos, currentLine.find('\t', lastpos));
      lastpos = currentLine.find('\t', lastpos);
      for (int j = 0; j < numStates; ++j)
      {
        cout << nfaStates[j] << endl;
        cout << currentState << endl;
        if (nfaStates[j] == currentState)
        {
          nfaAcceptStates[i] = &nfaStates[j];
        }
      }
    }
    while (getline(nfaFile, currentLine))
    {
      lastpos = 0;
      string* stateAddress;
      string* symbolAddress;
      string* transitionStateAddress;
      string state = currentLine.substr(lastpos, (currentLine.find(',', lastpos)-lastpos));
      lastpos = currentLine.find(',', lastpos)+1;
      string symbol = currentLine.substr(lastpos, (currentLine.find('=', lastpos)-lastpos));
      lastpos = currentLine.find('=', lastpos)+1;
      string transitionState = currentLine.substr(lastpos, (currentLine.find('\n', lastpos)-lastpos));
      for (int i = 0; i < numStates; ++i)
      {
        if (nfaStates[i] == state)
        {
          stateAddress = &nfaStates[i];
        }
        else if (nfaStates[i] == transitionState)
        {
          transitionStateAddress = &nfaStates[i];
        }
      }
      for (int i = 0; i < numSymbols; ++i)
      {
        if (alphabet[i] == symbol)
        {
          symbolAddress = &alphabet[i];
        }
      }
      string** nfaFuncKey = new string*[2];
      nfaFuncKey[0] = stateAddress;
      nfaFuncKey[1] = symbolAddress;
      if (nfaDeltaFunc.count(nfaFuncKey) == 0)
      {
        list<string*>* nfaData = new list<string*>();
        nfaData->push_back(transitionStateAddress);
        nfaDeltaFunc.insert(pair<string**, list<string*>* >(nfaFuncKey, nfaData));
      }
      else
      {
        list<string*>* nfaData = new list<string*>();
        nfaData->push_back(transitionStateAddress);
        nfaDeltaFunc[nfaFuncKey]->merge(*nfaData);
      }
    }
    nfaFile.close();
  }
}

void nfaConverter::DFAGenerator(string inputFileName, string outputFileName)
{
  fileReader(inputFileName);
  printsystem();
}

void testfunction()
{
  nfaConverter* testConverter = new nfaConverter();
  testConverter->DFAGenerator("testTextFile.txt", "EMPTY");
}*/
