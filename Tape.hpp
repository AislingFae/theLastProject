#include <vector>
#include <iostream>

using namespace std;

class tape
{
public:
struct square
{
  int sqNum;
  char sqChar;

  square *next;
  square *prev;

};

  int currentState;
  square *currentSquare,*startSquare;


  tape(string init);
  void moveForward();
  void moveBack();
  char read();
  void write(char add);
  void setState(int newState);
  int getState();
  string toString();
};

  tape::tape(string init)
{
  currentSquare=new square;
  startSquare=currentSquare;
  currentSquare->sqNum=0;
  currentSquare->sqChar=init[0];
  currentSquare->prev=NULL;
  currentSquare->next=NULL;
  for(int i=1;i<init.length();i++)
    {
      square *prevSquare=currentSquare;
      currentSquare=new square;
      prevSquare->next=currentSquare;
      currentSquare->prev=prevSquare;
      currentSquare->next=NULL;
      currentSquare->sqChar=init[i];
      currentSquare->sqNum=i;
    }
  currentSquare=startSquare;

}

void tape::moveForward()
{
  if(currentSquare->next==NULL)
    {
      square *nextSquare=new square;
      currentSquare->next=nextSquare;
      nextSquare->prev=currentSquare;
      nextSquare->sqNum=currentSquare->sqNum+1;
      nextSquare->sqChar='@';
      nextSquare->next=NULL;
      currentSquare=nextSquare;
    }
  else
    currentSquare=currentSquare->next;

}

void tape::moveBack()
{
  if(currentSquare->prev==NULL)
    {
      square *prevSquare=new square;
      currentSquare->prev=prevSquare;
      prevSquare->next=currentSquare;
      prevSquare->sqNum=currentSquare->sqNum-1;
      prevSquare->sqChar='@';
      prevSquare->prev=NULL;
      currentSquare=prevSquare;
      startSquare=currentSquare;
    }
  else
    currentSquare=currentSquare->prev;

}

char tape::read()
{
  return currentSquare->sqChar;
}

void tape::write(char add)
{
  currentSquare->sqChar=add;
}

int tape::getState()
{
  return currentState;
}

void tape::setState(int newState)
{
 currentState=newState;
}

string tape::toString()
{

  string returnString="";
  string buffer;
  square *readSquare=startSquare;

  while(readSquare!=NULL)
    {
      buffer=readSquare->sqChar;
      returnString.append(buffer);
      readSquare=readSquare->next;
    }
  return returnString;
}
