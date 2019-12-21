// ConsoleApplication3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<list>
#include<string>
#include<fstream>
using namespace std;


class CNode
{
public:
	string variable;
	string identifier;
	string value;
	CNode* pNext;
	CNode(string var, string iden, string val)
	{
		this->variable = var;
		this->identifier = iden;
		this->value = val;
	}
};

class CList
{
public:
	CNode* pHead;
	CNode* pTail;

	CList()
	{
		pHead = NULL;
		pTail = NULL;
	}
	void attach(CNode* pnn)
	{
		if (pHead == NULL)
		{
			pHead = pnn;
			pTail = pnn;
		}
		else
		{
			pTail->pNext = pnn;
			pTail = pnn;
		}
	}
	void dispall()
	{
		CNode* ptrav;
		ptrav = pHead;
		while (ptrav != NULL)
		{
			cout <<"variable: "<< ptrav->variable << " ||| identifier: " << ptrav->identifier << "  |||  value:  " << ptrav->value << endl;
			ptrav = ptrav->pNext;
		}
	}
};

class Memory
{
public:
	list<string> variableList;
	list<string> identifierList;
	list<string> valueList;
};


bool checkIfIdentifier(string lineOfCode)
{
	//Declaration of the valid data types (identifiiers)
	string identifiersList[6] = { "int", "float", "string", "double", "bool", "char" };
	//cout << "The recognizable data types (identifiers) are: " << "\n";
	//for (int i = 0; i < sizeof(identifiersList) / sizeof(identifiersList[0]); i++)
	//{
		//cout << identifiersList[i] << "\n";
	//}

	//Capturing the first word and checking if it is an identifier
	string firstWord = lineOfCode.substr(0, lineOfCode.find(" "));
	bool foundDataType = false;
	for (int i = 0; i < 6; i++)
	{
		if (identifiersList[i] == firstWord) foundDataType = true;
	}
	if (foundDataType) return true;
	else return false;
}
string getIdentifier(string lineOfCode)
{
	string firstWord = lineOfCode.substr(0, lineOfCode.find(" "));
	return firstWord;
}
string getVariable(string lineOfCode)
{
	string variable = "";
	string identifier = getIdentifier(lineOfCode);
	int pos = lineOfCode.find(" ");
	while (lineOfCode[pos] == ' ') pos++;
	while (lineOfCode[pos] != ' ' && lineOfCode[pos] != '=' && lineOfCode[pos] != ';' )
	{
		variable += lineOfCode[pos];
		pos++;
	}

	return variable;
}
string getValue(string lineOfCode)
{
	string value = "";
	int pos = lineOfCode.find("=");
	pos++;
	while (lineOfCode[pos] == ' ')pos++;
	while (lineOfCode[pos] != ';')
	{
		value += lineOfCode[pos];
		pos++;
	}

	return value;
}
bool initialized(string lineOfCode, string variable)
{
	bool equalsExist = false;
	int variablePos = lineOfCode.find(variable);
	//cout << endl<< endl<< lineOfCode.substr(variablePos)<< endl << endl;

	for (int i = variablePos; lineOfCode[i] != '\0' ; i++)
	{
		//cout << lineOfCode[i];
		if (lineOfCode[i] == '=')
		{
			equalsExist = true;
			break;
		}
	}

	return equalsExist;
}

void readLine(string& lineOfCode)
{
	cout << "Please enter your line of code: \n";
	getline(cin, lineOfCode);
}

void readLines(string(&linesOfCode)[5])
{
	//Get lines of code from file
	short loop = 0; //short for loop for input
	string line; //this will contain the data read from the file
	ifstream myfile("code.txt"); //opening the file.
	if (myfile.is_open()) //if the file is open
	{
		cout << endl << endl << "the read lines of code are: ";
		while (!myfile.eof()) //while the end of file is NOT reached
		{
			getline(myfile, line); //get one line from the file
			linesOfCode[loop] = line;
			cout << endl << linesOfCode[loop]; //and output it
			loop++;
		}
		myfile.close(); //closing the file
	}
	else cout << "Unable to open file"; //if the file is not open output
}

int main()
{
	CList memory;
	CNode* pnn;

	//Get lines of code from file
	string linesOfCode[5]; // creates array to hold names
	readLines(linesOfCode);



	//Loop over the lines of code
	cout << endl;
	for (int i = 0; i < sizeof(linesOfCode) / sizeof(linesOfCode[0]); i++)
	{
		//Checking if the current line of code starts with an identifier
		if (checkIfIdentifier(linesOfCode[i]))
		{
			//capture the identifier and the variable declared
			string identifier = "";
			string variable = "";
			//cout << endl<< endl << "found identifier : " << getIdentifier(linesOfCode[i]) << " with variable: "<< getVariable(linesOfCode[i])<< "  in line " << i;
			identifier = getIdentifier(linesOfCode[i]);
			variable = getVariable(linesOfCode[i]);
			if (initialized(linesOfCode[i], variable))
			{
				//cout << endl << endl << "variable is initialized" << endl << endl << endl;
				string value = getValue(linesOfCode[i]);
				pnn = new CNode(variable, identifier, value);
				memory.attach(pnn);
			}
			else
			{
				pnn = new CNode(variable, identifier, "none");
				memory.attach(pnn);
			}
		}

	}
	


	//Previewing memory state here
	cout << endl << endl << endl << endl;
	memory.dispall();
	







	
	cout << endl << endl;
}
