// ConsoleApplication3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<list>
#include<string>
#include<fstream>
using namespace std;


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
	string secondWord = lineOfCode.substr(lineOfCode.find(" "), lineOfCode.find(" "));
	return secondWord;
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
	//Get lines of code from file
	string linesOfCode[5]; // creates array to hold names
	readLines(linesOfCode);



	cout << endl;
	for (int i = 0; i < sizeof(linesOfCode) / sizeof(linesOfCode[0]); i++)
	{
		
		if (checkIfIdentifier(linesOfCode[i]))
		{
			//Do here what happens if first word in the line is an identifier
			string identifier = "";
			string variable = "";
			//cout << endl<< endl << "found identifier : " << getIdentifier(linesOfCode[i]) << " with variable: "<< getVariable(linesOfCode[i])<< "  in line " << i;
			identifier = getIdentifier(linesOfCode[i]);
			variable = getVariable(linesOfCode[i]);
		}
	}








	
	cout << endl << endl;
}
