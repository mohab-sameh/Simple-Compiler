// ConsoleApplication3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<list>
#include<string>
#include<fstream>
using namespace std;


bool checkIfIdentifier(string lineOfCode, string &firstWord)
{
	//Declaration of the valid data types (identifiiers)
	string identifiersList[6] = { "int", "float", "string", "double", "bool", "char" };
	//cout << "The recognizable data types (identifiers) are: " << "\n";
	//for (int i = 0; i < sizeof(identifiersList) / sizeof(identifiersList[0]); i++)
	//{
		//cout << identifiersList[i] << "\n";
	//}

	//Capturing the first word and checking if it is an identifier
	firstWord = lineOfCode.substr(0, lineOfCode.find(" "));
	bool foundDataType = false;
	for (int i = 0; i < 6; i++)
	{
		if (identifiersList[i] == firstWord) foundDataType = true;
	}
	if (foundDataType) return true;
	else return false;
}

void readLine(string& lineOfCode)
{
	cout << "Please enter your line of code: \n";
	getline(cin, lineOfCode);
	cout << "\n" << lineOfCode;
}


int main()
{
	





	//Input of user line of code
	string lineOfCode;
	readLine(lineOfCode);

	//Get lines of code from file
	string linesOfCode[5]; // creates array to hold names
	short loop = 0; //short for loop for input
	string line; //this will contain the data read from the file
	ifstream myfile("code.txt"); //opening the file.
	if (myfile.is_open()) //if the file is open
	{
		cout << endl << "the read line of code are: " << endl;
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




	//Capturing the first word within the user input to check if it's valid input
	string firstWord = "";
	if (checkIfIdentifier(lineOfCode, firstWord))
	{
		cout << endl<< endl << "found identifier : " << firstWord;
	}








	
	cout << endl << endl;
}
