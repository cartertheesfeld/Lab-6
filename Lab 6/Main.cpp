/*
Carter Theesfeld
C++ Fall 2022
Due 
Lab 5 Random Number Guessing Game
Description: Write a C++ program that reads characters representing binary (base 2) 
numbers from a data file called BinaryIn.dat and translates them to decimal (base 10) 
numbers. The binary and decimal numbers should be output in two columns with 
appropriate headings. There is only one binary number per input line, but an arbitrary number of blanks can 
precede the number.  The program must read the binary numbers one character at a 
time.  As each character is read, the program multiplies the total decimal value by 2 and 
adds either a 1 or 0, depending on the input character.  The program should check for 
bad data; if it encounters anything except a 1 or 0, it should output the message “Bad 
digit on input.”  The maximum number of spaces that could exist between any two digits 
of a binary number in the input file will be one, in which case, the binary digit would be 
considered bad.  The output for this program should be to the screen and not an output 
file.  In order to read in one character at a time, you will need to use the cin.get 
command.   
*/

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <math.h>
using namespace std;

//precondition:there are no files opened. fstream is included
//postcondition:files are opened
void OpenFile(ifstream& inFile, ifstream& inFile2, string inputFileName);
//precondition:There is no heading in the terminal. iostream is included
//postcondition:There is now a heading in the terminal
void Heading();
//precondition:The files are opened and can be read. 
//postcondition: The computer reads through the file to find the location of the one value. It keeps track of the position to use for later. If the start as an item that is not
// a 1 0 or space then it calls the bad digit function
void GetBiNum(char bi, int& position, int &startPosition, int count, int dec, ifstream& inFile, ifstream& inFile2, string inputFileName);
//precondition:Get bi num is called and has found the position of 1. 
//postcondition:The binary number is outputed and checked to see if there are no random characters inserted
void OutputBi(char& bi, int& count, int& position, int startPosition, int dec, ifstream& inFile, ifstream& inFile2, string inputFileName);
void Conversion(int startPosition, char& bi, int& dec, int& count, ifstream& inFile, ifstream& inFile2, string inputFileName);
void BadDigit(char bi, int& position, int startPosition, int count, int dec, ifstream& inFile, ifstream& inFile2, string inputFileName);

int main()
{
	char bi=' ';
	int count = 0;
	int startPosition = 0;
	int position = -1;
	int dec=0;
	string inputFileName = "BinaryIn.dat";
	ifstream inFile;
	ifstream inFile2;
	OpenFile(inFile,inFile2, inputFileName);
	Heading();
	GetBiNum(bi,position, startPosition, count, dec,inFile,inFile2, inputFileName);
	inFile.close();
	return 0;
}
void OpenFile(ifstream& inFile,ifstream& inFile2,string inputFileName)
{
	inFile.open(inputFileName);
	inFile2.open(inputFileName);
	if (!inFile)
		cout << "can't find the file!\n";
}
void Heading()
{
	cout << "         Binary Number                         Decimal Equivalent" << endl;
}
void GetBiNum(char bi, int& position, int& startPosition, int count,int dec, ifstream& inFile, ifstream& inFile2, string inputFileName)
{
	while (inFile)
	{
		inFile.get(bi);
		position++;
		if (bi == '1')
		{
			cout << setw(15);
			startPosition = position;
			OutputBi(bi, count, position, startPosition, dec, inFile,inFile2,inputFileName);
		}
		else if (bi == '0' || bi == ' ')
		{

		}
		else
			BadDigit(bi, position,startPosition, count, dec, inFile,inFile2,inputFileName);
	}
}
void OutputBi(char& bi, int& count, int& position, int startPosition, int dec, ifstream& inFile, ifstream& inFile2, string inputFileName)
{
	inFile.seekg(startPosition);
	inFile.get(bi);
	
	while (bi != '\n' && inFile)
	{
		if (bi == '1')
		{
			count++;
			cout << bi;
			inFile.get(bi);
			position++;
		}
		else if (bi == '0')
		{
			count++;
			cout << bi;
			inFile.get(bi);
			position++;
		}
		else
		{
			cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
			BadDigit(bi, position, startPosition, count, dec, inFile,inFile2, inputFileName);
		}
		
	}

	if (bi == '\n')
		position++;

	if (inFile2)
		Conversion(startPosition, bi, dec, count, inFile, inFile2, inputFileName);

}
void Conversion(int startPosition, char& bi, int& dec, int& count, ifstream& inFile, ifstream& inFile2,string inputFileName)
{
	cout << setw(40-count);
	if (inFile.eof())
	{
		inFile2.seekg(startPosition);
		inFile2.get(bi);
		while (bi != '\n' && inFile2)
		{

			if (bi == '1')
			{
				dec = dec + pow(2, count - 1);
				count--;

			}
			else if (bi == '0')
				count--;
			inFile2.get(bi);
		}
		inFile2.close();
	}
	inFile.seekg(startPosition);
	inFile.get(bi);

	while (bi != '\n' && inFile)
	{
		
		if (bi == '1')
		{
			dec = dec + pow(2, count-1);
			count--;
			
		}
		else if (bi == '0')
			count--;
		inFile.get(bi);
	}
	cout << dec << endl;
	dec = 0;
	count = 0;
	
}
void BadDigit(char bi, int& position, int startPosition, int count, int dec, ifstream& inFile,ifstream& inFile2, string inputFileName)
{
	for (int i = 0; i <= count; i++)
		cout << '\b';
	cout << "     Bad digit on input" << endl;
	while (bi != '\n')
	{
		inFile.get(bi);
		position++;
	}
	position++;
	count = 0;
	GetBiNum(bi, position, startPosition, count, dec, inFile, inFile2, inputFileName);
}