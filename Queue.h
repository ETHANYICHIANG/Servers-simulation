//Programmer: Ethan Chiang
//Programmer ID: 1538719

#ifndef Queue_h
#define Queue_h

#include <iostream>
using namespace std;

template <typename V>
class Queue
{
  struct node
  {
    V value;
    node* next;
  };
  int siz;
  node* first;
  node* last;
  
  public:
  Queue(); 
  Queue(const Queue&); // copy constructor
  ~Queue();
  void push(const V&);
  V& front() {return first->value;} // return a mutable reference to the oldest node
  V& back() {return last->value;} // return a mutable reference to the newest node
  void pop(); // remove the oldest node
  int size() const {return siz;}
  bool empty() const {return siz == 0 ? true : false;}
  void clear();
  Queue<V>& operator=(const Queue<V>&);
};

//constructor(s)
template <typename V>
Queue<V>::Queue()
{
  first = 0;
  last = 0;
  siz = 0;
}

template <typename V>
Queue<V>::Queue(const Queue<V>& original)
{
  first = 0;
  last = 0;
  siz = original.siz;

  for(node* p = original.first; p; p = p->next)
  {
    node* temp = new node;
    temp->value = p->value;
    temp->next = 0;
    if(last) last->next = temp;
    else first = temp;
    last = temp;
  }
}

//push
template <typename V>
void Queue<V>::push(const V& value)
{
  node* temp = new node;
  temp->value = value;
  temp->next = 0;
  if(last) last->next = temp;
  else first = temp;
  last = temp;
  siz++;
}

//pop
template <typename V>
void Queue<V>::pop()
{
  if(first)
  {
    node* p = first;
    first = first->next;
    delete p;
    siz--;
  }
  if(siz == 0) last = 0;
}

//clear
template <typename V>
void Queue<V>::clear()
{
  while(first)
  {
    node* p = first;
    first = first->next;
    delete p;
    siz--;
  }
  first = 0;
  last = 0;
}

//assignment operator
template <typename V>
Queue<V>& Queue<V>::operator=(const Queue<V>& original)
{
  if (this != &original) // of it's not a self copy...
  {
    // do what the destructor does
    while(first)
    {
      node* p = first;
      first = first->next;
      delete p;
    }

    // build new queue
    last = 0;
    for(node* p = original.first; p; p = p->next)
    {
      node* temp = new node;
      temp->value = p->value;
      temp->next = 0;
      if(last) last->next = temp;
      else first = temp;
      last = temp;
    }
    siz = original.siz;
  }
  return *this; // return a self reference
}

//destructor
template <typename V>
Queue<V>::~Queue()
{
  while(first)
  {
    node* p = first;
    first = first->next;
    delete p;
  }
}

#endif