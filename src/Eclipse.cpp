/*
 * Eclipse.cpp
 *
 *  Created on: Oct 11, 2017
 *      Author: Eric Gonzalez
 */

#include "Eclipse.h"
#include <string>
#include <iostream>

using namespace std;

// Eclipse constructor
Eclipse::Eclipse() {
	// initialize the line string variable
	this->line = "";
	// loop thru the eclipseInfo string array and initialize
	for (int i = 0; i < 18; i++)
	{
		eclipseInfo[i] = "";
	}

}

Eclipse::Eclipse(string e) {
	this->line = e;

	// remove a whitespace if any
	for (int i = 0; i < 1; i++)
	{
		// if there is a detection of a whiteSpace...
		if (e.at(i) == ' ') {

			// ...then remove the whiteSpace
//			cout << "REMOVING WHITESPACE" << endl; // DEBUGGING

			// remove whitespace
			e.replace(i, 1, "");
			// keep decrementing i so that it can keep removing whitespace,
			// so when there are no more whitespace, then exit this for loop
			--i;
		}
//		else // if there is no detection of a whitespace (debugging)
//		{
//			cout << "e.at(i) is _" << e.at(i) << "_" << endl; // debugging
//		}
	}
//	cout << "With LEADING white space removed: " << e << endl; // debugging

	while (e.find("  ") != string::npos)
	{
		e.replace(e.find("  "), 2, " ");
	}

	/**
	 * visual representation of the comments of the line file
	 */
	//  Name  Age   Weight  Height
	// [ A ] [ B ] [   ]  [ D ]
	// a,b,,d
	// [ A ] [ B ] [ D ]



	// while there is a whitespace, replace it with a comma
	while (e.find(" ") != string::npos)
	{
		e.replace(e.find(" "), 1, ",");
	}
//	cout << "Replacing with commas: " << e << endl;

	// while there is a case of multiple commas, replace
	// it with a single comma
	//while (e.find(",,") != string::npos) {
	//	e.replace(e.find(",,"), 2, ",");
	//}
//	cout << "Dropping double commas: " << e << endl;

	// remove an unnecessary comma that is at the end of each line
	if ((e.at(e.length() - 1) == ','))
	{
		e.replace(e.length() - 1, 1, "");
	}
//	cout << "Dropping initial comma: " << e << endl;

	this->csvDataLine = e;
//	cout << "CSV Data Line: " << this->csvDataLine << endl;


	bool isPartial;

//	cout << "I am storing " << e << " into " << this->line << endl;
//	cout << "That lines length is " << this->line.length() << endl;
	int pIndex = 0;
	int commaCount = 0;
	//22,002,-1990,Jan,06,13:10:01,46230,-49350,19,P,1.0749,0.8256,65.4N,163.3E,0,167
	//                                             ^cc=9
	//
	while(commaCount < 9 && pIndex < this->csvDataLine.length())
	{
		if(this->csvDataLine.at(pIndex) == ',') {
			commaCount++;
		}
		pIndex++;
	}
//	cout << "I FOUND A " << this->csvDataLine.at(pIndex) << endl;
	if(this->csvDataLine.at(pIndex) == 'P')
	{
		isPartial = true;
	}
	else
	{
		isPartial = false;
	}


	/**
	 * assigns each element in the string array to the correct category section
	 */
	eclipseInfo[0] = getCategorySection(1, isPartial); // catNum to 0th ...
	eclipseInfo[1] = getCategorySection(2, isPartial);
	eclipseInfo[2] = getCategorySection(3, isPartial);
	eclipseInfo[3] = getCategorySection(4, isPartial);
	eclipseInfo[4] = getCategorySection(5, isPartial);
	eclipseInfo[5] = getCategorySection(6, isPartial);
	eclipseInfo[6] = getCategorySection(7, isPartial);
	eclipseInfo[7] = getCategorySection(8, isPartial);
	eclipseInfo[8] = getCategorySection(9, isPartial);
	eclipseInfo[9] = getCategorySection(10, isPartial);
	eclipseInfo[10] = getCategorySection(11, isPartial);
	eclipseInfo[11] = getCategorySection(12, isPartial);
	eclipseInfo[12] = getCategorySection(13, isPartial);
	eclipseInfo[13] = getCategorySection(14, isPartial);
	eclipseInfo[14] = getCategorySection(15, isPartial);
	eclipseInfo[15] = getCategorySection(16, isPartial);
	eclipseInfo[16] = getCategorySection(17, isPartial);
	eclipseInfo[17] = getCategorySection(18, isPartial);
	eclipseInfo[18] = getCategorySection(19, isPartial); // ... until 18th category section

//	// loop through each column and print out the # column and its contents
//	for(int i=0;i<=18;i++)
//	{
//		cout << "#" << i << ": " << eclipseInfo[i] << endl;
//	}
}



// Eclipse constructor that takes in a string
Eclipse::Eclipse(string catNum, string canonPlate, string calenderYear, string calenderMonth, string calenderDay,
		string tdGreatestEclipse, string dt, string lunaNum, string sarosNum, string eclipseType, string gamma,
		string eclipseMag, string latitude, string longitude, string sunAlt, string azm, string width, string centralDur) {
	//line = str;

	/**
	 * TODO: literally initialize all of your eclipse variables to a certain index
	 */
	// this string arrays holds all of the column variables
	//eclipseInfo[0] = catNum;
	string eclipseInfo[18] = {catNum, canonPlate, calenderYear, calenderMonth, calenderDay, tdGreatestEclipse,
			dt, lunaNum, sarosNum, eclipseType, gamma, eclipseMag, latitude, longitude,
			sunAlt, azm, width, centralDur};
}

// de-structor
Eclipse::~Eclipse() {
	//leave empty
}

/**
 * this function get the selected column from the user to perform a certain action
 * TODO: Don't forget to convert the (string) userResponse into an int using stoi(string userResponse)
 */
string Eclipse::getColumnElement(int response) const {
	// return the string column that the user wants
//	string userTempResponse = "";
//	if (userTempResponse == " ")
//	{
//
//	}
	return eclipseInfo[response];
}

/**
 * returns the csvDataLine
 */
string Eclipse::getcsvDataLine() {
	return this->csvDataLine;
}

/**
 * this function gets the column section that is between commas
 * Note: this code has been taken from a fellow student, I have made accommodations to my
 * code to better fit my overall code
 * Citation: Cavan Gary
 */
string Eclipse::getCategorySection(int numCol, bool isPartial)
{
	// used to count the number of commas
	int commaCounter = 0;
	// used to find the column we want
	int targetColumn = 0;

	// set the targetColumn to the max # of columns
	if(isPartial)
	{
		// set to 16 for partial
		targetColumn = 16;
	}
	else
	{
		// set to 18 if its not partial
		targetColumn = 18;
	}

	// loop the length of the file
	for(unsigned int i = 0; i < csvDataLine.length(); i++)
	{
		// count the amount of commas
		if(csvDataLine.at(i) == ',')
		{
			commaCounter++;
		}
		// if you reach a comma and the numCol is 1
		if(csvDataLine.at(i) == ',' && numCol == 1)
		{
			// return the first column (categoryNums)
			return csvDataLine.substr(0, 1);
		}
		// if we want any of the columns that is in between the first and last column
		else if(csvDataLine.at(i) == ',' && numCol == targetColumn && commaCounter == numCol - 1)
		{
			// return the specified column
			return csvDataLine.substr(i + 1, csvDataLine.length() - i - 1);
		}
		// if we want the last column
		else if(csvDataLine.at(i) == ',' && commaCounter == numCol - 1)
		{
			// return the last column
			return csvDataLine.substr(i + 1, csvDataLine.find(',', i + 1) - i - 1);
		}
	}
	return ""; // must have this in here or else I get errors
}

//  for(int i=0;i<=string.length();i++) {
//       V 56 letters
//  if( word.at(i) >= this->size() )
//  {

/** A copy constructor.*/
Eclipse::Eclipse(const Eclipse &source) {
	line = source.line;

	for (int i = 0; i < 18; i++)
	{
		eclipseInfo[i] = source.eclipseInfo[i];
	}
	// loop through the eclipseInfo array
//	for (int i = 0; i < 18; i++)
//	{
//		// assign each eclipseInfo to the source eclipseInfo
//		this->eclipseInfo[i] = source.eclipseInfo[i];
//	}
}

/**
 * print off the eclipse info in csv
 */
void Eclipse::print()
{
	for(int i = 0; i < 18; i++)
	{
		cout << eclipseInfo[i] << ",";
	}


}

/**
 * less than operator
 */
bool Eclipse::operator < (const Eclipse& e) {
	if(this->catNum < e.catNum)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * greater than operator
 */
bool Eclipse::operator > (const Eclipse& e)
{
	if(this->catNum >= e.catNum)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * greater than or equal to operator
 */
bool Eclipse::operator >= (const Eclipse& e)
{
	if(this->catNum >= e.catNum)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * less than or equal to operator
 */
bool Eclipse::operator <= (const Eclipse& e)
{
	if(this->catNum >= e.catNum)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/**
 * An overloaded equals operator.
 */
Eclipse Eclipse::operator= (const Eclipse& source)
{
	line = source.line;

	for (int i = 0; i < 18; i++)
	{
		this->eclipseInfo[i] = source.eclipseInfo[i];
	}

	return *this;
}

/**
 * Overloaded operator
 */
std::ostream& operator<<(std::ostream& output, const Eclipse& e) {
	output << e.line << endl;

	return output;
}

