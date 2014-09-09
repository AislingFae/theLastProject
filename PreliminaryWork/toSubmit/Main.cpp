#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Alphabets.hpp"
#include "Tape.hpp"
#include "Transition.hpp"
#include <cstdlib>
using namespace std;

int parser(ifstream &ifl,transitionTable &transitionTable, alphabets &alphabet, string &init)
{
  string buffer;
  int numStates;

  getline(ifl,buffer);
  for(int i=0;i<buffer.size();i++)
    {
      if(alphabet.addToTape(buffer[i])<1)
	return -1;

    }//close for i
  
  getline(ifl,buffer);

  for(int i=0;i<buffer.size();i++)
    {
      if(alphabet.addToInput(buffer[i])<1)
	return -1;

    }//close for i
  
  getline(ifl,buffer);

  for(int i=0;i<buffer.size();i++)
    {
      bool isInAlphabet=false;
      for(int j=0;j<alphabet.inputAlphabet.size();j++)
	{
	  if(buffer[i]==alphabet.inputAlphabet[j])
	    isInAlphabet=true;

	}//close for j
      if(!isInAlphabet)
	{
	  cout<<"Input String contains character '"<<buffer[i]<<"' Which is not in the input Alphabet"<<endl;
	  return -1;
	}
    }//close for i

  init=buffer; // If String pans out assign it


  getline(ifl,buffer);

  numStates=strtol(buffer.c_str(),NULL,10);
  if(numStates<1)
    {
      cout<<"There must be at least one state"<<endl;
      return -1;
    }
 
  for(int i=0;i<numStates;i++)
    {
      getline(ifl,buffer);
      vector<transition> rowBuffer;

      if(buffer.find(']')==string::npos)
	{
	  cout<<"Unproperly formatted transition triples"<<endl;
	  return -1;
	}

      while(buffer.find(']')!=string::npos)
	{
	  string miniBuffer=buffer;
	  string anotherBuffer;
	  transition bufferTransition;
	  int addState;
	  char addChar;
	  char addDirection;

	  miniBuffer.erase(miniBuffer.find(']')+1,string::npos);
	  buffer.erase(0,buffer.find(']')+1);
	  anotherBuffer=miniBuffer;
	  anotherBuffer.erase(anotherBuffer.find(','),string::npos);
	  miniBuffer.erase(0,miniBuffer.find(',')+1);

	  if((anotherBuffer=="")||(anotherBuffer[0]!='['))
	   { 
	     cout<<"Unproperly formatted transition in line "<<4+i<<" Missing '['"<<endl;
	     cout<<anotherBuffer<<"  |||   "<<miniBuffer<<endl;
	      return -1;
	    }
	  anotherBuffer.erase(0,1);
	  addState=strtol(anotherBuffer.c_str(),NULL,10);
	  if(addState>numStates)
	    {
	      cout<<"states must be numbered sequentially and state "<<addState<<" is larger than the given maximun number of states"<<endl;
	     cout<<anotherBuffer<<"  |||   "<<miniBuffer<<endl;
	      return -1;
	    }

	  if(miniBuffer.find(',')==string::npos)
	    {	      
	      cout<<"Unproperly formatted transition in line "<<4+i<<" Missing Commas"<<endl;
	     cout<<anotherBuffer<<"  |||   "<<miniBuffer<<endl;
	      return -1;
	    }
	  anotherBuffer=miniBuffer;
	  anotherBuffer.erase(anotherBuffer.find(','),string::npos);
	  miniBuffer.erase(0,miniBuffer.find(',')+1);

	  if((anotherBuffer=="")||(anotherBuffer.size()>1))
	   { 
	     cout<<"Unproperly formatted transition in line "<<4+i<<" Write char incorrect:"<<anotherBuffer<<endl;
	     cout<<anotherBuffer<<"  |||   "<<miniBuffer<<endl;
	     return -1;
	    }



	  addChar=anotherBuffer[0];
	  anotherBuffer=miniBuffer;
	  anotherBuffer.erase(anotherBuffer.find(']'),string::npos);
	  miniBuffer.erase(0,miniBuffer.find(']')+1);
	  if(((anotherBuffer!="+")&&(anotherBuffer!="-"))||(miniBuffer!=""))
	    {
	      cout<<"Unproperly formatted transition in line "<<4+i<<" Direction wrong"<<anotherBuffer<<endl;
	     cout<<anotherBuffer<<"  |||   "<<miniBuffer<<endl;
	     return -1;
	    }

	  addDirection=anotherBuffer[0];
	  bufferTransition.set(addState,addChar,addDirection);
	  rowBuffer.push_back(bufferTransition);

	}//close while

      transitionTable.table.push_back(rowBuffer);
    }//close for i

  if(!ifl.eof())
    cout<<"There's extraneous lines in the program, they will be ignored"<<endl;
    
	transitionTable.numStates=numStates;
	return 1;
}//close func


int run(transitionTable &transitionTable,alphabets &alphabet,tape &tape)
{
  ofstream ofl;
  ofl.open("log.txt");
  int count=0;
  while(tape.currentState>=0)
    {
      char compareChar;
      char direction;
      int nextState;
      char writeChar;
     compareChar=tape.read();
     ofl<<compareChar<<endl;
     int charPos=-1;
     for(int i=0;i<alphabet.tapeAlphabet.size();i++)
       {
	 if(compareChar==alphabet.tapeAlphabet[i])
	   charPos=i;
       }
     if(charPos<0)
       {
	 cout<<"Unrecognizable character '"<<compareChar<<"' on tape."<<endl;
	 return -1;
       }
     direction=transitionTable.table[tape.currentState][charPos].direction;
     nextState=transitionTable.table[tape.currentState][charPos].nextState;
     writeChar=transitionTable.table[tape.currentState][charPos].writeChar;

     cout<<tape.currentState<<":"<<tape.currentSquare->sqNum<<":"<<tape.toString()<<endl;


     ofl<<"["<<nextState<<","<<writeChar<<","<<direction<<"]"<<endl;    
     tape.write(writeChar);
     if(direction=='+')
       tape.moveForward();
     else
       tape.moveBack();

     tape.setState(nextState);
     string returnString=tape.toString();
     ofl<<returnString<<endl;
     ofl<<"Setting State '"<<nextState<<"' Moving '"<<direction<<"'writing char '"<<writeChar<<"'"<<endl;
     ofl<<"Current State: "<<tape.currentState<<endl;
 
    }//close while

  cout<<tape.currentState<<":"<<tape.currentSquare->sqNum<<":"<<tape.toString()<<endl;

  return 1;
}//close func


int main(int argc,char *argv[])
{

  ifstream ifl;
  ifl.open(argv[1]);
  transitionTable  transitionTable1;
  alphabets alphabet1;
  string init;

  if(parser(ifl, transitionTable1, alphabet1, init)<0)
    return-1;
  tape tape1(init);
 

  if(run(transitionTable1,alphabet1,tape1)<0)
    return -1;


  cout<<"Result on Tape: "<<tape1.toString()<<endl;
  cout<<"Final State: " <<tape1.currentState<<endl;
  if(tape1.currentState==-1)
    cout<<"Which is the YES state"<<endl;
  else if(tape1.currentState==-2)
    cout<<"Which is the NO state"<<endl;

  return 1;
}

