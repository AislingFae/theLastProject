#include <vector>
#include <iostream>


using namespace std;

class alphabets
{

public:

  vector<char> tapeAlphabet;
  vector<char> inputAlphabet;
  bool hasBlank;
  alphabets();
  int addToTape(char add);
  int addToInput(char add);
  int readOut();

};

alphabets::alphabets()
{
  hasBlank=false;
}

int alphabets::addToTape(char add)
{

  if(((add>='0') && (add<='9'))||((add>='@')&&(add<='Z'))||(add>='a')&&(add<='z'))
    {
      if(add=='@')
	hasBlank=true;
      tapeAlphabet.push_back(add);
      return 1;
    }
  else
    {
      cout<<"Unacceptable character: '"<<add<<"' for the tape alphabet. UNACCEPTABLE!!"<<endl;
      return -1;
    }
}

int alphabets::addToInput(char add)
{

  if(((add>='0') && (add<='9'))||((add>='@')&&(add<='Z'))||(add>='a')&&(add<='z'))
    {
      if(add=='@')
	{
	  cout<<"The Blank character '@' cannot be in the input alphabet. UNACCEPTABLE!!"<<endl;
	  return -1;
	}
      
      inputAlphabet.push_back(add);
      return 1;
    }
  else
    {
      cout<<"Unacceptable character: '"<<add<<"' for the input alphabet. UNACCEPTABLE!!"<<endl;
      return -1;
    }
} 

int alphabets::readOut()
{

  cout<<"Tape Alphabet:"<<endl;
  for(int i=0;i<tapeAlphabet.size();i++)
    {
      cout<<tapeAlphabet[i]<<flush;
    }
  cout<<"\n"<<endl;
  cout<<"Input Alphabet:"<<endl;
  for(int i=0;i<inputAlphabet.size();i++)
    cout<<inputAlphabet[i]<<flush;
  cout<<endl;
  return 1;

}
