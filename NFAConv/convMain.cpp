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
#include "epsilon.h"

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
  vector<string>* testAlphabet = new vector<string>();
  vector<vector<string>* >* testMap = new vector<vector<string>* >();
  testAlphabet->push_back("1");
  testAlphabet->push_back("2");
  testAlphabet->push_back("3");
  vector<string>* map1 = new vector<string>();
  map1->push_back("a");
  map1->push_back("1");
  map1->push_back("b");
  vector<string>* map2 = new vector<string>();
  map2->push_back("b");
  map2->push_back("2");
  map2->push_back("a");
  vector<string>* map3 = new vector<string>();
  map3->push_back("a");
  map3->push_back("EPS");
  map3->push_back("c");
  testMap->push_back(map1);
  testMap->push_back(map2);
  testMap->push_back(map3);
  EpsilonClosureGenerator* testECG = new EpsilonClosureGenerator(testMap);
  vector<string>* testClosure = testECG->closureOf("a");
  for (int i = 0; i < testClosure->size(); ++i)
  {
    cout << testClosure->at(i);
  }
  delete testECG;
  delete testGenerator;
}
