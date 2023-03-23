//*****************************************************************************
// purpose: driver Lab 3
//  author: Anne Heidebreicht alh1310
//*****************************************************************************
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "nodes.h"

void nodeExamples(){
  IntegerNode a(14);
  cout << a << endl;

  FloatNode b(99.99);
  cout << b << endl;

  StringNode c("testing");
  cout << c << endl;

  cout << endl;
}

int main( int argc, char* argv[] ) {

  // create and print an example of each of the DataNodes
  nodeExamples();
  cout << endl;
  
  // Create a vector (a resizable list) of pointers to DataNodes
  vector<DataNode*> aVector;

  // Add four data item pointers to the vector: "first", 2, 3.14, "fourth"
  aVector.push_back(new StringNode("first"));
  aVector.push_back(new IntegerNode(2));
  aVector.push_back(new FloatNode(3.14));
  aVector.push_back(new StringNode("fourth"));

  // Output the size of the vector
  cout << "Size of the vector: " << aVector.size() << endl;
  // Output the items pointed to by vector elements using the .at method
  for (int i=0; i < aVector.size(); i = i + 1) {
    cout << *(aVector.at(i)) << endl;
  }
  cout << endl;

  // Add four more data item pointers to the vector: 5, 6.28, "seventh", "eighth"
  aVector.push_back(new IntegerNode(5));
  aVector.push_back(new FloatNode(6.28));
  aVector.push_back(new StringNode("seventh"));
  aVector.push_back(new StringNode("eighth"));
  // Output the size of the vector
  cout << "Size of the vector: " << aVector.size() << endl;
  // Output the items pointed to by vector elements using an iterator
  vector<DataNode*>::iterator it; // source: https://cplusplus.com/reference/vector/vector/
  for (it = aVector.begin(); it < aVector.end(); it++)
  {
    cout << *(*it) << endl;
  }
  cout << endl;
  // Delete the items pointed to by vector elements
  // Do NOT hard code the size of the vector
  // To indicate that the node is deleted, set the item pointer to nullptr
  for (int i = 0; i < aVector.size(); i++)
  {
    delete aVector[i];
    aVector[i] = nullptr;
  }
  cout << endl;  

  // Output the size of the vector
  cout << "Size of the vector: " << aVector.size() << endl;
  // Clear the vector
  aVector.clear();
  // Output the size of the vector
  cout << "Size of the vector: " << aVector.size() << endl;
  return 0;
}

