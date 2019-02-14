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
  NFAConverter::dfaDeltaFunc = new list<pair<string*, list<string>* > >();
}

void NFAConverter::DFAGenerator(string inputFileName, string outputFileName)
{
  NFAConverter::fileReader(inputFileName);
  NFAConverter::dfaStates = NFAConverter::powerSetGenerator(NFAConverter::nfaStates);
  for (int i = 0; i < sizeof(NFAConverter::dfaStates)/sizeof(NFAConverter::dfaStates[0]); ++i)
  {
    string* deltaKey = NFAConverter::dfaStates[i];
    list<string>* deltaData = new list<string>();
    for (int j = 0; j < deltaKey->size(); ++j)
    {
      deltaData->merge(*epsilonClosureGenerator(deltaKey[j], NFAConverter::nfaDeltaFunc));
    }
    deltaData->unique();
    if (!deltaData->empty())
    {
      NFAConverter::dfaDeltaFunc->push_back(pair<string*, list<string>* > (deltaKey, deltaData));
    }
  }
  NFAConverter::dfaAcceptStates = acceptStateGenerator(NFAConverter::nfaAcceptStates);
  NFAConverter::dfaStartStates = startStateGenerator(NFAConverter::nfaStartStates);
  NFAConverter::fileWriter(outputFileName);
}

void NFAConverter::fileReader(string inputFileName)
{

}

void NFAConverter::fileWriter(string outputFileName)
{

}

void NFAConverter::printList(list<string>* input)
{
  for (int i = 0; i < input->size(); ++i)
  {
    cout << input->front() << " ";
    input->push_back(input->front());
    input->pop_front();
  }
  cout << endl;
}

void NFAConverter::uniqueList(list<list<string>* >* input)
{
  int listLength = input->size();
  for (int i = 0; i < listLength; ++i)
  {
    list<string>* currentValue = input->front();
    input->pop_front();
    int subLength = input->size();
    for (int j = 0; j < subLength; ++j)
    {
      list<string>* testValue = input->front();
      if (*testValue == *currentValue)
      {
        input->pop_front();
      }
      else
      {
        input->push_back(testValue);
        input->pop_front();
      }
    }
    input->push_back(currentValue);
  }
}

string** NFAConverter::powerSetGenerator(string* stateSet)
{

}

void NFAConverter::powerSetHelper(list<list<string>* >* powerSet, list<string>* stateSet, int s)
{
  if (s == 0)
  {
    list<string>* result = new list<string>();
    result->push_back("EM");
    powerSet->push_back(result);
  }
  else
  {
    powerSet->push_back(stateSet);
    for (int i = 0; i < stateSet->size(); ++i)
    {
      list<string>* nextSet = new list<string>();
      list<string>* currentSet = new list<string>(*stateSet);
      for (int j = 0; j < i; ++j)
      {
        nextSet->push_back(currentSet->front());
        currentSet->pop_front();
      }
      currentSet->pop_front();
      for (int k = i+1; k < stateSet->size(); ++k)
      {
        nextSet->push_back(currentSet->front());
        currentSet->pop_front();
      }
      NFAConverter::powerSetHelper(powerSet, nextSet, s-1);
    }
  }
}

void NFAConverter::arraySetGenerator(string** iterationSet, string* stateSet, int startpos, int maxsize, int currentIterationSize)
{
  if (currentIterationSize == 0)
  {
    string* nextSet = new string[1];
    nextSet[0] = "EM";
    iterationSet[startpos] = nextSet;
  }
  else{
    int newStartPos = startpos + (combination(maxsize, currentIterationSize));
    cout << startpos << endl;
    cout << newStartPos << endl;
    cout << currentIterationSize << endl;
    bool newEntry = true;
    for (int i = startpos; i < newStartPos; ++i)
    {
      bool totalMatch = false;
      for (int j = 0; j < iterationSet[i]->size(); ++j)
      {
        if (iterationSet[i][j] == stateSet[i])
        {
          totalMatch = true;
        }
        if (totalMatch && iterationSet[i][j] != stateSet[i])
        {
          totalMatch = false;
          break;
        }
      }
      if (totalMatch)
      {
        newEntry = false;
        break;
      }
    }
    if (newEntry)
    {
      for (int i = startpos; i < newStartPos; ++i)
      {
        if (iterationSet[i]->size() == 0)
        {
          iterationSet[i] = stateSet;
          cout << "Added Element " << stateSet[0] << " at location " << i << endl;
        }
      }
    }
    for (int i = 0; i < stateSet->size(); ++i)
    {
      string* nextSet = new string[currentIterationSize-1];
      int unit = 0;
      for (int j = 0; j < unit; ++j)
      {
        nextSet[j] = stateSet[j];
      }
      for (int k = unit+1; k < currentIterationSize; ++k)
      {
        nextSet[k-1] = stateSet[k];
      }
      NFAConverter::arraySetGenerator(iterationSet, nextSet, newStartPos, maxsize, currentIterationSize-1);
    }
  }
}

int NFAConverter::combination(int n, int r)
{
  return (factorial(n)/((factorial(r))*(factorial(n-r))));
}

int NFAConverter::factorial(int n)
{
  if (n < 2)
  {
    return 1;
  }
  else
  {
    return n * factorial(n-1);
  }
}

list<string>* NFAConverter::epsilonClosureGenerator(string state, list<pair<string*, list<string>* > >* delta)
{

}

string** NFAConverter::acceptStateGenerator(string* initialAcceptStates)
{

}

string** NFAConverter::startStateGenerator(string* initialStartStates)
{

}

int main()
{
  NFAConverter* testConverter = new NFAConverter();
  list<list<string>* >* testPowerSet = new list<list<string>* >();
  list<string>* testSet = new list<string>();
  testSet->push_back("a");
  testSet->push_back("b");
  testSet->push_back("c");
  testSet->push_back("d");
  int x = 4;
  testConverter->powerSetHelper(testPowerSet, testSet, x);
  testConverter->uniqueList(testPowerSet);
  for (int i = 0; i < testPowerSet->size(); ++i)
  {
    testConverter->printList(testPowerSet->front());
    testPowerSet->push_back(testPowerSet->front());
    testPowerSet->pop_front();
  }
  cout << endl;
  cout << endl;
  string** testPowerArray = new string*[int(pow(2, 3))];
  for (int i = 0; i < int(pow(2, 3)); ++i)
  {
    string* holderArray = new string[3];
    testPowerArray[i] = holderArray;
    for (int j = 0; j < 3; ++j)
    {
      testPowerArray[i][j] = "x";
    }
  }
  string* testArray = new string[3];
  testArray[0] = "a";
  testArray[1] = "b";
  testArray[2] = "c";
  testConverter->arraySetGenerator(testPowerArray, testArray, 0, 3, 3);
  for (int i = 0; i < 8; ++i)
  {
    for (int j = 0; j < 3; ++j)
    {
      cout << testPowerArray[i][j] << " ";
    }
    cout << endl;
  }
};

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
