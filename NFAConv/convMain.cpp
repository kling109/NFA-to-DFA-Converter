/*
Name: Trevor Kling
ID: 002270716
Email: kling109@mail.chapman.edu
Course: CPSC 406 Algorithm Analysis
Last Date Modified: 15 February 2019
Project: NFA to DFA Converter
*/

#include <vector>
#include <iostream>
#include "powerSetGen.h"

using namespace std;

int main()
{
  vector<string>* v = new vector<string>();
  v->push_back("a");
  v->push_back("b");
  v->push_back("c");
  PowerSetGenerator* testGenerator = new PowerSetGenerator(v);
  testGenerator->buildPowerSet();
  vector<vector<string>* >* set = testGenerator->getPowerSet();
  for (int i = 0; i < set->size(); ++i)
  {
    for (int j = 0; j < set->at(i)->size(); ++j)
    {
      cout << set->at(i)->at(j) << " ";
    }
    cout << endl;
  }
}
