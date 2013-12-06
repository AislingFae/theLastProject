#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Alphabets.hpp"
#include "Tape.hpp"
#include "Transition.hpp"

using namespace std;

int parser(ifstream &ifl,transitionTable &transitionTable, alphabets &alphabet)
{
  string buffer;
  int numStates;
  int testString;

  getline(ifl,buffer);
  for(int i=0;i<buffer.size();i++)
    {
      if(buffer[i].addToTape<1)
	return -1;

    }//close for i
  
  getline(ifl,buffer);

  for(int i=0;i<buffer.size();i++)
    {
      if(buffer[i].addToInput<1)
	return -1;

    }//close for i
  
  getline(ifl,buffer);

  for(int i=0;i<buffer.size();i++)
    {
      bool isInAlphabet=false;
      for(int j=0;j<tape.inputAlphabet();j++)
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

  testString=buffer; // If String pans out assign it


  getline(ifl,buffer);

  numStates=strtol(buffer,NULL,10);
  if(numStates<1)
    {
      cout<<"There must be at least one state"<<endl;
      return -1;
    }
  for(int i=0;i<numStates;i++)
    {
      getline(ifl,buffer)
	vector<transition> rowBuffer;
	for(int j=0;j<buffer.size;j+=7)
	  {
	    
	    if((buffer[j]!='[')||(buffer[j+6]!=']')||(buffer[j+2]!=',')||(buffer[j+4=!=']'))
	      {
		cout<<"Formating error in line: "<<5+i<<endl;
		return -1;
	      }
	      transition bufferTransition;

	      if(strtol(buffer[j+1],NULL,10)>numStates)
		{
		  cout<<"States must be numbered sequentially, state: "<<buffer[j+1]<<" is out of the given number of states."<<endl;
		  return -1; 
		}
	      bool isIn=false;
	      for(int k=0;k<alphabet.tapeAlphabet.size();k++)
		{
		  if(buffer[j+3]==alphabet.tapeAlphabet[k])
		    isIn=true;
		} //close for k

	      if(!isIn)
		{
		  cout<<"Symbol '"<<buffer[j+3]<<"' is not in the provided tape Alphabet"<<endl;
		  return -1;
		}
	      if((buffer[j+5]!='+')&&(buffer[j+5]!='-'))
		{
		  cout<<"The symbol '"<<buffer[j+5]<<"' is incorrect, please use '+' or '-'."<<endl;
		  return -1;
		}

	      if(bufferTransition.set(strtol(buffer[j+1],NULL,10),buffer[j+3],buffer[j+5])<0)
		return -1;
	      rowBuffer.push_back(bufferTransition);

	  }//close for j
	    transitionTable.table.push_back(rowBuffer);

    }//close for i

	transitionTable.numStates=numStates;

}//close func

int main(int argc,char *argv[])
{

  ifstream ifl;
  ifl.open(argv[1]);
  transitionTable  transitionTable1;
  alphabets alphabet1;
  tape tape1;

  parser(ifl, transitionTable1, alphabet1);
  initializeTape(transitionTable,alphabet1,tape1);


  return 1;
}

