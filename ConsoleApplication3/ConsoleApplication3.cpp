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
			cout <<"variable: "<< ptrav->variable << " ||| identifier: " << ptrav->identifier << "  |||  value:  " << ptrav->value << "  |||" << endl;
			ptrav = ptrav->pNext;
		}
	}
};

void insertValueInMemory(string targetVariable, string insertionValue, CList& memory)
{
	bool foundVariable = false;

	CNode* ptrav;
	ptrav = memory.pHead;
	while (ptrav != NULL)
	{
		if (targetVariable == ptrav->variable)
		{
			foundVariable = true;
			ptrav->value = insertionValue;
		}
		ptrav = ptrav->pNext;
	}
}
string returnTargetVariable(string lineOfCode, CList& memory)
{
	int tmpPos = lineOfCode.find(" ");
	if (tmpPos > lineOfCode.find("=")) tmpPos = lineOfCode.find("=");
	string firstWord = lineOfCode.substr(0, tmpPos);
	bool foundVariable = false;

	CNode* ptrav;
	ptrav = memory.pHead;
	while (ptrav != NULL)
	{
		if (firstWord == ptrav->variable) return firstWord;
		ptrav = ptrav->pNext;
	}
}
string returnTargetValue(string targetVariable, CList& memory)
{
	bool foundVariable = false;

	CNode* ptrav;
	ptrav = memory.pHead;
	while (ptrav != NULL)
	{
		if (targetVariable == ptrav->variable)
		{
			foundVariable = true;
			return ptrav->value;
		}
		ptrav = ptrav->pNext;
	}
	//return "not found";
}
string returnTargetIdentifier(string targetVariable, CList& memory)
{
	bool foundVariable = false;

	CNode* ptrav;
	ptrav = memory.pHead;
	while (ptrav != NULL)
	{
		if (targetVariable == ptrav->variable)
		{
			foundVariable = true;
			return ptrav->identifier;
		}
		ptrav = ptrav->pNext;
	}
}

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
bool checkIfVariable(string lineOfCode, CList &memory)
{
	int tmpPos = lineOfCode.find(" ");
	if (tmpPos > lineOfCode.find("=")) tmpPos = lineOfCode.find("=");
	string firstWord = lineOfCode.substr(0, tmpPos);
	bool foundVariable = false;

	CNode* ptrav;
	ptrav = memory.pHead;
	while (ptrav != NULL)
	{
		if (firstWord == ptrav->variable) foundVariable = true;
		ptrav = ptrav->pNext;
	}
	//if (foundVariable) cout << endl<< endl<< endl<< "found variable: " << firstWord << endl;
	if (foundVariable) return true;
	else return false;
}
bool checkIfOperator(string sign)
{
	
	string operatorsList[6] = { "+", "-", "/", "%", "*" };
	
	bool foundOperator = false;
	for (int i = 0; i < 5; i++)
	{
		if (operatorsList[i] == sign) foundOperator = true;
	}
	if (foundOperator) return true;
	else return false;
}
bool checkIfInitialized(string lineOfCode, string variable)
{
	bool equalsExist = false;
	int variablePos = lineOfCode.find(variable);
	//cout << endl<< endl<< lineOfCode.substr(variablePos)<< endl << endl;

	for (int i = variablePos; lineOfCode[i] != '\0'; i++)
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
bool checkIfSemicolonExists(string lineOfCode)
{
	char semicolon = lineOfCode[size(lineOfCode) - 1];
	if (semicolon == ';')return true;
	return false;
}
bool checkIfVariableExists(string targetVariable, CList& memory)
{
	CNode* ptrav;
	ptrav = memory.pHead;
	while (ptrav != NULL)
	{
		if (ptrav->variable == targetVariable) return true;
		ptrav = ptrav->pNext;
	}
	return false;
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
	while (lineOfCode[pos] != ' ' && lineOfCode[pos] != '=' && lineOfCode[pos] != ';' && lineOfCode[pos] != '\0' )
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
	while (lineOfCode[pos] != ';' && lineOfCode[pos] != '\0')
	{
		value += lineOfCode[pos];
		pos++;
	}

	return value;
}

string resolveValue(string identifier, string variable, string value, CList &memory)
{
	string splittedWords[100];

	int strCt = 0;
	for (int i = 0; value[i] != '\0'; i++)
	{
		while (value[i] == ' ')
		{
			if (value[i + 1] == '\0')break;
			if (value[i + 1] != ' ')strCt++;
			i++;
		}
		if (value[i] != ' ' && value[i] != '\0')
		{
			splittedWords[strCt] += value[i];
		}
		
	}
	splittedWords[strCt + 1] = "\0";


	

	//Checking if splitted array contains variables that should be resolved
	for (int i = 0; splittedWords[i] != "\0"; i++)
	{
		//Checking if the current cell is an exiting variable
		if (checkIfVariableExists(splittedWords[i], memory))
		{
			//If such a variable exists, extract the raw value of that variable from the memory.
			splittedWords[i] = returnTargetValue(splittedWords[i], memory);
		}
	}

	//Running the higher priority arithmetic operations within the splitted list
	for (int i = 0; splittedWords[i] != "\0"; i++)
	{
		if (splittedWords[i] == "*" )
		{
			int tmpVal = stoi(splittedWords[i - 1]) * stoi(splittedWords[i+1]);
			splittedWords[i - 1] = to_string(tmpVal);
			
			int j = 0;
			for (j = i; splittedWords[j + 2] != "\0"; j++)
			{
				splittedWords[j] = splittedWords[j + 2];
			}
			splittedWords[j] = "\0";
			i--;
		}
		if (splittedWords[i] == "/")
		{
			int tmpVal = stoi(splittedWords[i - 1]) / stoi(splittedWords[i+1]);
			splittedWords[i - 1] = to_string(tmpVal);

			int j = 0;
			for (j = i; splittedWords[j + 2] != "\0"; j++)
			{
				splittedWords[j] = splittedWords[j + 2];
			}
			splittedWords[j] = "\0";
			i--;
		}
		if (splittedWords[i] == "%")
		{
			int tmpVal = stoi(splittedWords[i - 1]) % stoi(splittedWords[i + 1]);
			splittedWords[i - 1] = to_string(tmpVal);

			int j = 0;
			for (j = i; splittedWords[j + 2] != "\0"; j++)
			{
				splittedWords[j] = splittedWords[j + 2];
			}
			splittedWords[j] = "\0";
			i--;
		}
	}
	//Running the lower priority arithmetic operations within the splitted list
	for (int i = 0; splittedWords[i] != "\0"; i++)
	{
		if (splittedWords[i] == "+" )
		{
			int tmpVal = stoi(splittedWords[i - 1]) + stoi(splittedWords[i + 1]);
			splittedWords[i - 1] = to_string(tmpVal);

			int j = 0;
			for (j = i; splittedWords[j + 2] != "\0"; j++)
			{
				splittedWords[j] = splittedWords[j + 2];
			}
			splittedWords[j] = "\0";
			i--;
		}
		if (splittedWords[i] == "-")
		{
			int tmpVal = stoi(splittedWords[i - 1]) + stoi(splittedWords[i + 1]);
			splittedWords[i - 1] = to_string(tmpVal);

			int j = 0;
			for (j = i; splittedWords[j + 2] != "\0"; j++)
			{
				splittedWords[j] = splittedWords[j + 2];
			}
			splittedWords[j] = "\0";
			i--;
		}
	}
	if (identifier == "int")return splittedWords[0];
	else return value;

	//Printing the splitted words list after change
	for (int i = 0; splittedWords[i] != "\0"; i++)
	{
		//cout << splittedWords[i] << " | ";
	}

	
}




void readLines(string(&linesOfCode)[20])
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
	string errorList[100];
	int errorCt = 0;

	//Get lines of code from file
	string linesOfCode[20]; // array that holds lines of codes in the file
	readLines(linesOfCode); //insert the lines in file into the array



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
			
			//Checking if the variable is initialized with a value
			if (checkIfInitialized(linesOfCode[i], variable))
			{
				//cout << endl << endl << "variable is initialized" << endl << endl << endl;
				string value = getValue(linesOfCode[i]);
				string resolvedValue = resolveValue(identifier, variable, value, memory);

				if (checkIfSemicolonExists(linesOfCode[i]))
				{
					if (!checkIfVariableExists(variable, memory))
					{
						pnn = new CNode(variable, identifier, resolvedValue);
						memory.attach(pnn);
					}
					else
					{
						errorList[errorCt] = "REDECLARATION OF VARIABLE: " + variable + " IN LINE: " + to_string(i);
						errorCt++;
					}
					
				}
				if (!checkIfSemicolonExists(linesOfCode[i]))
				{
					errorList[errorCt] = "SEMICOLON MISSING IN LINE: " + to_string(i);
					errorCt++;
				}

			}
			//If value is declared but not initialized
			else
			{
				if (checkIfSemicolonExists(linesOfCode[i]))
				{
					if (!checkIfVariableExists(variable, memory))
					{
						pnn = new CNode(variable, identifier, "");
						memory.attach(pnn);
					}
					else
					{
						errorList[errorCt] = "REDECLARATION OF VARIABLE: " + variable + " IN LINE: " + to_string(i);
						errorCt++;
					}
				}
				if(!checkIfSemicolonExists(linesOfCode[i]))
				{
					errorList[errorCt] = "SEMICOLON MISSING IN LINE: " + to_string(i);
					errorCt++;
				}
				
			}
		}


		//Checking if the current line starts with a variable
		if (checkIfVariable(linesOfCode[i], memory))
		{
			string targetVariable = returnTargetVariable(linesOfCode[i], memory);
			string insertionValue = getValue(linesOfCode[i]);
			string targetIdentifier = returnTargetIdentifier(targetVariable, memory);
			string resolvedValue = resolveValue(targetIdentifier, targetVariable, insertionValue, memory);
			insertValueInMemory(targetVariable, resolvedValue, memory);
		}


		//Checking if "if condition starts here..



		//Checking if Reserved words starts here..



		//else print unsupported syntax on line i

	}
	


	
	//Printing error list starts here
	cout << endl << endl << endl<< endl << "Error List: " << endl<< endl;
	for (int i = 0; i <= errorCt; i++)
	{
		cout << errorList[i] << endl;
	
	}


	//Previewing memory state here
	cout << endl << "Memory: " << endl << endl;
	memory.dispall();
	




	
	cout << endl << endl;
}
