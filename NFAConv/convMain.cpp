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

int main()
{
  DFAGenerator* testGen = new DFAGenerator("testTextFile.txt", "testOutput.txt");
  testGen->generateDFA();
  testGen->~DFAGenerator();
}
