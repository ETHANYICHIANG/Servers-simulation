//Programmer: Ethan Chiang
//Programmer ID: 1538719

#include <iostream>
using namespace std;

#include <cassert>

#include "Queue.h"
#include "Queue.h" // ifndef test

struct testType
{
  double num;
};

int main()
{
  cout << "Programmer: Ethan Yi Chiang\n"
       << "Programmer ID: 1538719\n"
       << "File: " << __FILE__ << endl;

  //Object.Double Test
  Queue<testType> da;

  //Queue::size
  cout << "Queue test: \n"
       << "-----------------"
       << "\nTesting Queue::size\n"
       << "EXPECTED: 0\n"
       << "ACTUAL: " << da.size() << endl;
  assert(0 == da.size());
  cout << "Pass!\n\n";

  //Queue::push & Queue::front 
  cout << "Tesing Queue::push & Queue::front \n";
  testType a; a.num = 1.1;
  da.push(a);
  cout << "EXPECTED: 1.1\n"
       << "ACTUAL: " << da.front().num << endl;
  assert(1.1 == da.front().num);
  cout << "Pass!\n\n";

  //Queue::pop
  cout << "Testing Queue::pop\n"
       << "Before pop: " << da.front().num << endl;
  assert(da.front().num == 1.1);
  testType b; b.num = 2.2;
  da.push(b);
  da.pop();
  cout << "After pop: " << da.front().num << endl;
  assert(da.front().num == 2.2);
  cout << "Pass!\n\n";

  //Queue::back
  cout << "Testing Queue::back\n";
  da.push(b);
  cout << "EXPECTED: 2.2\n"
       << "ACTUAL: " << da.back().num << endl;
  assert(2.2 == da.back().num);
  cout << "Pass!\n\n";

  //copy constructor
  cout << "Testing copy constructor\n";
  da.push(a);
  Queue<testType> db = da;
  assert(da.size() == db.size());
  while(db.size() != 0)
  {
    assert(da.front().num == db.front().num);
    da.pop(); db.pop();
  }
  cout << "Pass!\n\n";

  //Assignment operator
  cout << "Tesing assignment operator\n";
  da.push(a); da.push(b);
  Queue<testType> dc; dc = da;
  assert(da.size() == dc.size());
  while(dc.size() != 0)
  {
    assert(da.back().num == dc.back().num);
    da.pop(); dc.pop();
  }
  cout << "Pass!\n\n";

  //Queue::clear & empty
  cout << "Testing Queue::clear & empty\n";
  da.push(a); da.push(b);
  da.clear();
  assert(da.empty());
  cout << "Pass!\n\n";

  //constant pbject test //test getters (empty & size)
  cout << "Constant object test: \n";
  Queue<testType> dd; dd.push(a); dd.push(b);
  const Queue<testType> de = dd;
  cout << "size: " << de.size() << endl;
  if(dd.empty()) cout << "Its empty!\n";
  else if(!dd.empty()) cout << "Its NOT empty!\n";
  else cout << "Oops!\n";

  return 0;
}