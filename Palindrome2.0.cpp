#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

string removeSpaces(string str) //function to remove spaces
{
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	return str;
}

string ConverttoLower(string upper) //function to convert all letters to lowercase
{
	string upper1 = upper;
	transform(upper1.begin(), upper1.end(), upper1.begin(), (int(*)(int))tolower);
	return upper1;
}


string RemovePunct(string lower) //function to remove punctuation
{
	string lower1 = lower;
	for (int i = 0, len = lower1.size(); i < len; i++)
	{
		if (ispunct(lower1[i]))
		{
			lower1.erase(i--, 1);
			len = lower1.size();
		}
	}
	return lower1;
}

string convertString(string original) //function that calls all previous functions (does the following in order for each string)
{
	string nospace = removeSpaces(original);
	string lower = ConverttoLower(nospace);
	string punct = RemovePunct(lower);
	return punct;
}

bool Palindrome(string str) //function that checks to see if the converted string is a palindrome
{
	string string1 = str;

	for (int i = 0, j = string1.size() - 1; i < (string1.size() / 2); i++, j--) {
		if (string1[i] != string1[j])
			return false;
	}
	return true;
}

int main()
{
	cout << "Enter name of input file: "; //asks for the name of the input file
	string InputFile;
	cin >> InputFile;
	cout << "Enter the name of output file: "; //asks what the name of the output file should be 
	string OutputFile;
	cin >> OutputFile;
	string line;
	ifstream myfile(InputFile);
	getline(myfile, line);
	const int Length = stoi(line);

	const int arraylength = Length;

	string * stringArray = new string[arraylength]; //makes array of size whatever number is in the first line of input file

	if (myfile.is_open())
	{
		for(int lcv = 0; lcv < arraylength; lcv++) //this for loop enters each line into the array
		{
			getline(myfile, line);
			stringArray[lcv] = line;
		}
		myfile.close();
	}
	else cout << "Unable to open file";

	ofstream PalindromeText;
	PalindromeText.open(OutputFile); //creates and opens the output file 

	for (int lcv = 0; lcv < arraylength; lcv++)
	{
		string String = stringArray[lcv]; //takes the sentence in the string array and puts it into a string
		string convert = convertString(String); //removes punctuation, uppercase, and spaces
		bool Pal = Palindrome(convert); //checks whether or not it is a palindrome

		string Pali;
		if (Pal == true) //if it is a palindrome, it prints out "PALINDROME"
		{
			Pali = "PALINDROME";
		}
		else if (Pal == false) //if it is not a palindrome, it prints out "NOT A PALINDROME"
		{
			Pali = "NOT A PALINDROME";
		}

		cout << String << endl << Pali << endl; //prints original sentence with the PALINDROME/NOT PALINDROME underneath it

		PalindromeText << String << endl << Pali << endl; //prints it into the output file

	}

	PalindromeText.close(); //closes text file

	return 0;

}
