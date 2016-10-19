//Programmer: Ethan Chiang
//Programmer ID: 1538719

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#include <cmath>
#include <cstdlib>

#include "Queue.h"
#include "DynamicArray.h"

struct Customer
{
  char id;
  int arrivalTime;
  int endTime;
};

//prototype(s)
int getRandomNumberOfArrivals(double);
int getServiceTime(const int, const int);
char assignName();

int main()
{
  cout << "Programmer: Ethan Yi Chiang\n"
       << "Programmer ID: 1538719\n"
       << "File: " << __FILE__ << endl;

  ifstream fin;
  fin.open("simulation.txt");
  if(!fin.good()) throw "I/O error!";
  srand(time(0)); rand( );

  // read the input values from a text file, one per line, in the order specified above.
  string buf;
  getline(fin,buf);
  int serversNum = atoi(buf.c_str());
  getline(fin,buf);
  double rate = atof(buf.c_str());
  getline(fin,buf);
  int waitLength = atoi(buf.c_str());
  getline(fin,buf);
  int minTime = atoi(buf.c_str());
  getline(fin,buf);
  int maxTime = atoi(buf.c_str());
  getline(fin,buf);
  int totalTime = atoi(buf.c_str());

  cout << "Number of servers: " << serversNum << endl;
  cout << "Customer arrival rate: " << rate << " per mintue, for "
       << totalTime << " mintues\n";
  cout << "Maximun queue length: " << waitLength << endl;
  cout << "Minimun service time: " << minTime << " mintues\n";
  cout << "Maximun service time: " << maxTime << " mintues\n\n";

  // declare and create and assign arrays and queues to be used in the solution
  Queue<Customer> waitLine;
  DynamicArray<Customer> serving;
  DynamicArray<bool> serverStatus;

  // the clock time loop
  for (int time = 0;; time++) // the clock time
  {
    // handle all services scheduled to complete at this clock time
    for(int i = 0; i < serversNum; i++)
    {
      if(serverStatus[i])
        if(serving[i].endTime == time)
          serverStatus[i] = false;
    }

    // handle new arrivals -- can be turned away if wait queue is at maximum length!
    if(time < totalTime)
    {
      int arrivalNum = getRandomNumberOfArrivals(rate);
      for(int i = 0; i < arrivalNum; i++)
      {
        if(waitLine.size() < waitLength)
        {
          Customer c;
          c.id = assignName();
          c.arrivalTime = time;
          waitLine.push(c);
        }
      }
     }

    // for idle servers, move customer from wait queue and begin service
    for(int i = 0; i < serversNum; i++)
    {
      if(!serverStatus[i] && !waitLine.empty())
      {
        serving[i] = waitLine.front(); // assign first customer to server
        waitLine.pop(); // remove customer from waut line
        serving[i].endTime = time + getServiceTime(minTime, maxTime);
        serverStatus[i] = true; // mark that server as busy
      }
    }

    // output the summary
    cout << "Time: " << time << endl;
    cout << "----------------------------\n"
         << "server now serving wait line\n"
         << "------ ----------- ---------\n";
    for(int i = 0; i < serversNum; i++)
    {
      // output server #
      cout << "  " << i ;
      if(serverStatus[i])
      {
        cout.width(10);
        cout << serving[i].id;
        if(i == 0 && !waitLine.empty()) // output wait line on server 0
        {
          cout << "      ";
          Queue<Customer> temp = waitLine;
          while(temp.size() != 0)
          {
            cout << temp.front().id;
            temp.pop();
          }
        }    
      }
      cout << endl;
    }

    // if the end of the simulation has been reached, break
    bool end;
    if(waitLine.size() == 0 && time >= totalTime) // reach time and no waitings 
    {
      for(int i = 0; i < serversNum; i++) // all servers idle
      {
        if(serverStatus[i]) break;
        end = true;
      }
    }   
    if(end)
    {
      cout << "\nSimulation end!\n";
      break;
    }

    // pause for the user to press ENTER
    cout << "Press enter to continue....\n";
    cin.get();
  }

  return 0;
}

// possion function
int getRandomNumberOfArrivals(double averageArrivalRate)
{
  int arrivals = 0;
  double probOfnArrivals = exp(-averageArrivalRate);
  for(double randomValue = (double)rand( ) / RAND_MAX;
    (randomValue -= probOfnArrivals) > 0.0;
    probOfnArrivals *= averageArrivalRate / static_cast<double>(++arrivals));
  return arrivals;
}

// function(s)
int getServiceTime(const int min, const int max)
{
  return min + (rand() % max);
}

char assignName()
{
  static int name = 65;

  if(name == 91) name = 65;

  char id = name;
  name++;

  return id;
}
