//============================================================================
// Name        : Lab3.cpp
// Author      : Eric Gonzalez
// Version     : 9/18/2017
// Copyright   : Your copyright notice
// Description : I/O file of EclipseR data into CSV
//============================================================================

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "ResizableArray.h"
#include "Eclipse.h"
#include "EclipseR.h"
#include "HashMap.h"
#include "HashNode.h"
#include "AVLTree.h"
//can use math library when calculating hash table

using namespace std;

EclipseR::EclipseR() {
	// create a string line to store file into
	string line = "";

	// count the number of commas in the file
	int commaCounter = 0;

	// counts the line the error has occurred
	int lineCounter = 1;

	// counts the amount of decimals in the line
	int decimalCount = 0;

	// if an error has occurred
	bool isError = false;

	// set lineError false
	bool lineError = false;

	// create a temp string
	string temp = "";

	// the maximum number of columns
	string columns[MAX_COL_INDEX];

	// create a string array of the first column with a maximum size hard-coded
	string categoryNums[12000];

	// create a category temp string to store strings that will be changed
	string catTemp = "";

	// category number counter
	int catNumCount = 0;

	// keeps tracks of the amount of rows
	int rowsIndex = 0;

	// create a string array of size 10 to store the header info of the file into an array
	string headerLine[10];

	// used to store the response of the user
	string response = "";

//	string catNum = "";
//	string canonPlate = "";
//	string calenderYear = "";
//	string calenderMonth = "";
//	string calenderDay = "";
//	string tdGreatestEclipse = "";
//	string dt = "";
//	string lunaNum = "";
//	string sarosNum = "";
//	string elcipseType = "";
//	string gamma = "";
//	string eclipseMag = "";
//	string latitude = "";
//	string longitude = "";
//	string numAlt = "";
//	string azm =  "";
//	string width = "";
//	string centralDur = "";

	// begin prompting the user to begin data input loop
	// START **************************************************

	// stores the user response to a string
	string userResponse = "";

	// the return value if the user types enter to help exit the manipulation loop
	int returnVal = 0;

	// start the program by prompting the user
	returnVal = startInput();

	// if the user presses enter
	if (returnVal == 1) {
		// exit the program loop
		exit(0);
	}
	// ************************************************** END

	// get the first ten lines of header info
	for (int i = 0; i < 10; i++)
	{
		// and store it into an array
		getline(inputFileFS, line);
		headerLine[i] = line;
	}

	/**
	 * This large while loop should loop through the file until
	 * it reaches the end of the file. It csv the file
	 * and also does error checking
	 *
	 * START: of csv manipulation and error checking
	 * *********************************************************
	 */
	// Loop thru text file
	while (!inputFileFS.eof()) {
		// clear the file line string
		line.clear();
		// gets the line of the ifstream
		getline(inputFileFS, line);

		// Check to see if the line/row of data is empty. then read in the next line of data, if there is one.
		// If not, the end of the file (eof) has been reached; exit the while loop.
		if(line.empty())
		{
			// goes to the next iteration of the while loop
			continue;
		}
//		cout << line << endl;
		// encapsulate the line string file to an eclipse object
		Eclipse eclipse = Eclipse(line);
//		cout << "Original eclipse data line: " << endl;
//		cout << line << endl;
//		cout << "Eclipse object created: " << endl;
//		cout << eclipse << endl;
		//eclipse.print();

		// string variable used get the csv data eclipse
		string csvEclipse = "";
		// a csvEclipse to get the csv data line
		csvEclipse = eclipse.getcsvDataLine();

		//		****************************************FIRST ERROR CHECK****************************************
		// reset the commaCount to zero to correctly count the number of columns
		commaCounter = 0;

		// loop through and count the number of commas that represent columns
		for (unsigned int i = 0; i < csvEclipse.length() - 1; ++i) {
			// if there's a comma
			if (csvEclipse.at(i) == ',') {
				// count the comma
				commaCounter++;
			}
		}

		// create an index variable to assign the eclipse letter to a char variable
		int index = 0;
		// assign a Letter of eclipse to a char variable
		for (int i = 1; i < 10; ++i) {
			index = csvEclipse.find(",", index + 1);
		}
		// assign the eclipseLetter at index plus one
		char eclipseLetter = csvEclipse.at(index + 1);

		// set the default error to where there is no error (false)
		isError = false;
		// if the eclipseLetter is a 'P' and if the number of columns isn't 16...
		if ((eclipseLetter == 'P') && (commaCounter != 15)) {
			// ...then output the error message including the incorrect number
			// of columns and stating how many columns it should be.
			string errorMessage = "Error in data row " + to_string(lineCounter)
							+ ": " + to_string(commaCounter + 1)
							+ " columns found. Should be 16.\n";

			// output the error message ^above^
			cerr << errorMessage;
			isError = true;
		}

		// if the eclipseLetter ISN'T  a 'P' and columns isn't 18...
		else if ((eclipseLetter == 'A' || eclipseLetter == 'T'
				|| eclipseLetter == 'H') && (commaCounter != 17)) {
			// ...then output an error message on which line it occurred and
			// state the correct number of columns it should be.
			string errorMessage2 = "Error in data row " + to_string(lineCounter)
							+ ": " + to_string(commaCounter + 1)
							+ " columns found. Should be 18.\n";

			// output the error message ^above^
			cerr << errorMessage2;
			isError = true;
		}
		// else there are no errors found within the lines of the file...
		else {
			// do nothing (this prevents errors for some reason)
		}

		// if there is an error
		if (isError) {
			// count the line
			lineCounter++;
			// then continue on with the loop instead of breaking
			continue;
		}

		//		****************************************SECOND ERROR CHECK****************************************
		/** Separate the columns into each allocation of the array index and
		 ensure that each entry in columns (1,2,3,5,7,8,9,15,16 and if present 17)
		 */

		// create a string temp to assign certain chars to import each
		// element into an array.
		string temp = "";
		// loop through each line of the file
		int j = 0;  // create a column index variable

		// This loops through the line
		for (unsigned int i = 0; i < csvEclipse.length(); i++) {
			// ... if there is a comma encountered...
			if (csvEclipse.at(i) == ',') {
				// ...populate the chars before each set of commas into their
				// respective array index
				columns[j++] = temp;
				// reset the temp to be ready to input chars into the next element of
				// the array
				temp = "";
			}
			// ... if no comma is encountered...
			else {
				// ... store the chars into the temp string
				temp = temp + csvEclipse.at(i);
			}
			// when i reaches the end of the line...
			if (i == csvEclipse.length() - 1) {
				// ... store that last set of chars into the last array.
				columns[j++] = temp;
			}
		}

		/* Code source: Zak Koskovoch, some code has been tweaked to accommodate my code
		 *  CODE SOURCE START */
		lineError = false;
		// If there are 16 columns, then...
		if (commaCounter == 15) {
			// loop through the 16 columns
			for (int i = 0; i < MIN_COL_INDEX; ++i) {
				// set isError to default false
				isError = false;
				// create a temp string to store the columns into to it
				temp = "";

				// use a switch statement to detect the correct columns
				// and see if errors have occurred
				switch (i) {
				case 0:
				case 1:
				case 2:
				case 4:
				case 6:
				case 7:
				case 8:
				case 14:
				case 15:
					// store each columns into a temporary string
					temp = columns[i];

					// loop thru the length of the temp string
					for (unsigned int j = 0; j < temp.length(); ++j) {
						// ... if at the 0th element if there is no digit
						// and if there isn't a negative
						if ((j == 0) && !isdigit(temp.at(j))
								&& temp.at(j) != '-') {
							// ...an error is detected
							isError = true;
						}
						// ... if anywhere there is an extra negative
						if (j != 0 && (temp.at(j) == '-')) {
							// ... an error is detected
							isError = true;
						}
					}
					// if there is an error...
					if (isError) {
						// output the error message
						string errorMessage3 = "Error in data row "
								+ to_string(lineCounter) + ":" + " Column "
								+ to_string(i + 1) + " is not a "
								"whole number.";

						cerr << errorMessage3 << endl;
						// set the error bool to true
						lineError = true;
					}
				}
			}
		}

		// If there are 18 columns, then...
		if (commaCounter == 17) {
			// loop thru the 18 columns
			for (int i = 0; i < MAX_COL_INDEX; ++i) {
				// set isError to default to false
				isError = false;
				temp = "";

				// use a switch statement to detect
				// if there are any errors
				switch (i) {
				case 0:
				case 1:
				case 2:
				case 4:
				case 6:
				case 7:
				case 8:
				case 14:
				case 15:
				case 16:
					// assign the columns to a temp string
					temp = columns[i];

					// loop thru the length of the temp string
					for (unsigned int j = 0; j < temp.length(); ++j) {
						// if at the 0th index there is no digit and
						// if there is not a negative...
						if ((j == 0) && !isdigit(temp.at(j))
								&& temp.at(j) != '-') {
							// ... then there is an error
							isError = true;
						}
						// if anywhere in the string there is an extra
						// negative
						if (j != 0 && (temp.at(j) == '-')) {
							// ... then there is an error
							isError = true;
						}
					}
					// if an error has been detected...
					if (isError) {
						// then output an error message
						string errorMessage3 = "Error in data row "
								+ to_string(lineCounter) + ":" + " Column "
								+ to_string(i + 1) + " is not a "
								"whole number.";

						cerr << errorMessage3 << endl;
						// set isError to true
						lineError = true;
					}
				}
			}
		}

		/* check to ensure columns 11 and 12 is a decimal number
		 Output: Error in data row r: Column c is not a t number.
		 loop through the minimum number of columns which is 16
		 */
		for (int i = 0; i < MIN_COL_INDEX; ++i) {
			// set bool value to default false
			isError = false;
			// create a temp string to store each columns
			temp = "";
			// keep track of the amount of decimals
			decimalCount = 0;
			// switch statements to see if there decimals in columns
			// 11 and 12.
			switch (i) {
			case 10:
			case 11:
				// store the columns into the temp string
				temp = columns[i];

				// loop thru the length of the temp string
				for (unsigned int j = 0; j < temp.length(); ++j) {
					// if there is no digit and at the 0th element
					// there is no negative...
					if (!isdigit(temp.at(j)) && (j == 0) && temp.at(j) != '-') {
						// ... there is an error
						isError = true;
					}
					// if anywhere in the string is an extra negative
					if (j != 0 && (temp.at(j) == '-')) {
						// ... there is an error
						isError = true;
					}
					// if there is an error and there is a decimal anywhere
					if (!isError && temp.at(j) == '.') {
						// count the decimals
						decimalCount++;
						// if there is more than one decimal...
						if (decimalCount != 1) {
							// ... there is an error
							isError = true;
						}
					}
				}
				// if there is an error anywhere...
				if (isError) {
					// ... then output an error message
					string errorMessage3 = "Error in data row "
							+ to_string(lineCounter) + ":" + " Column "
							+ to_string(i + 1) + " is not a "
							"decimal number.";

					cerr << errorMessage3 << endl;
					// there is a error within the line, so set true
					lineError = true;
				}
			}
		}

		// if there is an error
		if (isError || lineError) {
			// count the line
			lineCounter++;
			// then continue on with the loop instead of breaking
			continue;
		}
		/* CODE SOURCE END: Zak Koskovich */

		//		****************************************THIRD ERROR CHECK****************************************
		/** Check to ensure that the catalog number of each eclipse is unique
		 * (not repeated). If it encounters a duplicate catalog number, it will
		 * send to standard error an error message with the following format
		 * Error in data row r: Duplicate catalog number n.
		 */
		// reset catTemp to be ready to assign
		catTemp.clear();
// TODO: USED FOR NAVIGATION
		// assign the first category into a temp string
		catTemp = csvEclipse.substr(0, csvEclipse.find(','));

		// the temp string to the array
		categoryNums[lineCounter - 1] = catTemp;

		// count the amount of category numbers
		catNumCount = 0;
		// loop through the length of the line file
		for (unsigned int i = 0; i < csvEclipse.length(); ++i) {
			// if the catTemp is duplicated
			if (catTemp == categoryNums[i]) {
				// count wherever there is a duplicate
				catNumCount++;
			}

			// if a category number is duplicated
			if (catNumCount > 1 && !isError) {
				// output the error message
				string errorMessage = "Error in data row "
						+ to_string(lineCounter) + ": "
						+ "Duplicate catalog number " + catTemp + ".";

				cerr << errorMessage << endl;
				// set the error boolean flag to true
				isError = true;
			}
		}

		// if there is an error in each column OR within the line
		if (isError || lineError) {
			// count the number of rows
			lineCounter++;
			// go to the next loop
			continue;
		}
		eclipseIsValid = 0;
		// if there is no error at all throughout the each line
//		cout << (!isError && !lineError) << endl;
		if (!isError && !lineError) {
			// fill up the rows to the row index
			//			rows[rowsIndex] = line;
			// ...print out the line as normal
			//cout << rows[rowsIndex] << endl;

			// add eclipses to the Re-sizable Array
//			cout << "Eclipse being added: " << endl;
//			cout << eclipse << endl;
			eclipsesRA.add(eclipse);
			// add eclipses to the Linked List
			eclipsesLL.add(eclipse);

//			// debugging
//			cout << "I am converting the number __" << eclipse.getColumnElement(0) << "__ into an integer, "
//					"stand back!" << endl;

			// insert eclipses into the Hash Table
			eclipsesHM.Insert(stoi(eclipse.getColumnElement(0)), eclipse);

//			cout << "I AM BEFORE AVL CALL" << endl;
			eclipsesAVL.setRoot(eclipsesAVL.insertNode(eclipsesAVL.getRoot(), eclipse));
//			cout << "I AM AFTER AVL CALL" << endl;
			// linkedList output

			// count the amount of valid eclipses
			eclipseIsValid++;
		}

		// Increment index for array rows
		rowsIndex++;
		// Increment the amount of lines
		lineCounter++;
	}

	cout << "\nError checking finished. Eclipses have been added..." << endl;
	cout << "Proceeding to data manipulation loop..." << endl << endl;


	/**
	 * this section of code handles the data manipulation loop
	 * START: of data manipulation loop
	 * ********************************************************
	 */
	// clear the userResponse string
	userResponse.clear();

	// data manipulation loop
	// this will prompt the user with a selection of options
	userResponse = dataManipulationInput(headerLine);

	// if user presses q
	if (userResponse == "q") {
		// end program
		cout << "You have pressed 'Q' for Quit, Goodbye!" << endl;
		exit(0);
	}
}

/**
 * This function was inspired by an algorithm online, some changes have
 * been made to accommodate my code.
 * Link Source: http://www.sanfoundry.com/cpp-program-implement-merge-sort/
 * UNIMPLEMENTED
 */
// A function to merge the two half into a sorted data.
//void Merge(int *a, int low, int high, int mid) {
//	ResizableArray<Eclipse> eclipse;
//	// We have low to mid and mid+1 to high already sorted.
//	int i, j, k, temp[high - low + 1];
//	i = low;
//	k = 0;
//	j = mid + 1;
//
//	// Merge the two parts into temp.
//	while (i <= mid && j <= high) {
//		if (a[i] < a[j]) {
//			temp[k] = a[i];
//			k++;
//			i++;
//		} else {
//			temp[k] = a[j];
//			k++;
//			j++;
//		}
//	}
//
//	// Insert all the remaining values from i to mid into temp[].
//	while (i <= mid) {
//		temp[k] = a[i];
//		k++;
//		i++;
//	}
//
//	// Insert all the remaining values from j to high into temp[].
//	while (j <= high) {
//		temp[k] = a[j];
//		k++;
//		j++;
//	}
//
//	// Assign sorted data stored in temp[] to a[].
//	for (i = low; i <= high; i++) {
//		a[i] = temp[i - low];
//	}
//}
//
///**
// * This function was inspired by an algorithm online, some changes have
// * been made to accommodate my code.
// * Link: http://www.sanfoundry.com/cpp-program-implement-merge-sort/
// * UNIMPLEMENTED
// */
//// A function to split array into two parts.
//void MergeSort(int *a, int low, int high) {
//	int mid;
//	if (low < high) {
//		mid = (low + high) / 2;
//		// Split the data into two half.
//		MergeSort(a, low, mid);
//		MergeSort(a, mid + 1, high);
//
//		// Merge them to get sorted output.
//		Merge(a, low, high, mid);
//	}
//}

/** A recursive binary search function. It returns location of x in
 given array arr[l..r] is present, otherwise -1
 UNIMPLEMENTED
 */
//int binarySearch(int arr[], int l, int r, int x) {
//	if (r >= l) {
//		int mid = l + (r - l) / 2;
//
//		// If the element is present at the middle itself
//		if (arr[mid] == x)
//			return mid;
//
//		// If element is smaller than mid, then it can only be present
//		// in left subarray
//		if (arr[mid] > x)
//			return binarySearch(arr, l, mid - 1, x);
//
//		// Else the element can only be present in right subarray
//		return binarySearch(arr, mid + 1, r, x);
//	}
//
//	// We reach here when element is not present in array
//	return -1;
//}

/**
 * this function will prompt the user with a selection of options to choose from
 */
string EclipseR::dataManipulationInput(string headerLine[10]) {
	// prompt the user for a selection of options
	//cout << "--------------------------" << endl;
	string userResponse = "";
	bool quit = false;
	ofstream outputStream;
	Eclipse eclipse;
	while (!quit)
	{
		// prompt user
		cout << "Please select an option: \n 'O' for output, 'S' for sort, 'F' for find, "
				"'M' for Merge, 'P' for Purge, 'H' for Hash Display, \n 'C' for "
				"Catalog Number, 'L' for Linked List, 'R' for pre-order of the AVL Tree,"
				"\n 'T' for post-order traversal of the AVL Tree, \n or 'Q' for quit." << endl;

		// gets the line of the user
		getline(cin, userResponse);

		if (userResponse == "o" && "O")
		{
			string fileName = "";
			cout << "*You have selected 'O' for Output.*" << endl;
			cout << "-> Please type in file you want to open: " << endl;
			getline(cin,fileName);

			// if the user hits enter without entering any data...
			if (fileName.empty())
			{
				// ... print to console
				// print out the first 10 lines of header info
				for (int i = 0; i < 10; i++)
				{
					cout << headerLine[i] << endl;
				}

				// then print out the array of eclipses (use for loop)
				for(int i = 0; i < eclipsesRA.length(); i++)
				{
					cout << eclipsesRA.getData()[i];
				}

				// print a row showing the internal tallies
				cout << "Data Lines read: " << eclipsesRA.length() <<
						";" << " Valid eclipses read: " << eclipseIsValid << ";" <<
						" Eclipses in memory: "<< endl;
			}
			// otherwise, try to open the specified file...
			else
			{
				inputFileFS.open(fileName);

				// if the file cannot be accessed...
				if(!inputFileFS.is_open())
				{
					// ... print out an error; cerr and break
					cerr << "File not found, Please try again." << endl;

				}
				// if the file is accessible...
				else
				{
					// ... write the data to the file
					// print out the first 10 lines of header info
					for (int i = 0; i < 10; i++)
					{
						outputFileFS << headerLine[i] << endl;
					}

					// print out the array of eclipses (use for loop)
					for (int i = 0; i < 100; i++)
					{
						// output the eclipse info
						outputFileFS << eclipsesRA[i] << endl;
					}
					// print a row showing the internal tallies
				}
			}
		}
		else if (userResponse == "s" && "S")
		{
			// TODO: implement sorting algorithm
			cout << "*You pressed 'S' for sort*" << endl;
			userResponse = "";
		}
		else if (userResponse == "f" && "F")
		{
			// TODO: implement binary search algorithm
			cout << "You pressed 'f' for find!*" << endl;

		}
		else if (userResponse == "m" && "M")
		{
			// TODO: implement merge function
			cout << "You pressed 'm' for merge!" << endl;

//			eclipsesAVL.replace(eclipsesAVL.getRoot(), eclipse);
		}
		else if (userResponse == "p" && "P")
		{
			// TODO: implement purge function
			cout << "You pressed 'p' for purge!" << endl;
			userResponse = "";
		}
		else if (userResponse == "h" && "H")
		{
			cout << "*You pressed 'h' Hash Display" << endl;
			cout << "Outputting the Hash Table Now..." << endl;
			eclipsesHM.display(); // display hash map buckets
		}
		else if (userResponse == "c" && "C")
		{

			cout << "You pressed 'C' for Catalog Number!" << endl;
			cout << "Outputting for Catalog Number that runs through the linked list..." << endl;
			// ... write the data to the file
			// print out the first 10 lines of header info
			for (int i = 0; i < 10; i++)
			{
				outputFileFS << headerLine[i] << endl;
			}
			eclipsesAVL.inorder(eclipsesAVL.getRoot()); // print inorder of AVL
		}
		else if (userResponse == "l" && "L")
		{
			// print out the linked list in sorted order according to catalog number
			cout << "You pressed 'L' for linked list!" << endl;
			cout << "Outputting linked list in sorted order based on catalog number..." << endl;
			eclipsesLL.display(); // use display function of linked list
		}
		else if (userResponse == "r" && "R")
		{
			cout << "You pressed 'R' for pre-order traversal of the AVL Tree!" << endl;
			cout << "Outputting the AVL Tree in pre-order traversal..." << endl;
			eclipsesAVL.preorder(eclipsesAVL.getRoot()); // use preorder from AVL Tree
		}
		else if (userResponse == "t" && "T")
		{
			cout << "You pressed 'T for post-order traversal of the AVL Tree!" << endl;
			cout << "Outputting the AVL Tree in post-order traversal..." << endl;
			eclipsesAVL.postorder(eclipsesAVL.getRoot()); // use postorder form AVL Tree
		}
		else if (userResponse == "q" && "Q") {
			quit = true; // set quit flag to true to exit while loop
		}

		// if user replies with a key that is not one of the options
		else
		{
			cout << "-> You did not select a specified option. Please try again." << endl;
			//continue;
			userResponse = "";
		}
	}
	return userResponse;
}


/**
 * This function prompts the user when the program begins, mainly to
 * handle the file input
 */
int EclipseR::startInput()
{
	// string to store the user response
	string userResponse = "";
	// bool if the file exist
	bool fileExist = false;
	ifstream inputFileStream;

	// the return exit value flag the main would use
	int returnExitValue = 0;

	//
	string line = "";

	// while the file exists
	while (!fileExist)
	{
		// prompt user to enter a file name
		cout << "Please enter the name of the file." << endl;
		// get the user response
		getline(cin, userResponse);

		// Trying to open the file specified
		cout << "Attempting to open file..." << endl;
		// open the file
		inputFileFS.open(userResponse);

		// if the user just presses enter
		if (userResponse.empty())
		{
			// output that the user pressed enter then exit function
			cout << "You pressed enter, exiting data input loop. Goodbye!" << endl;
			// set the bool to true to break loop
			fileExist = true;
			// set return val to 1
			returnExitValue = 1;
			// return the exit value flag for main method
			return returnExitValue;
		}

		// if the file doesn't open
		if (!inputFileFS.is_open())
		{
			// output an error and prompt user for another file name
			cerr << "File is not available" << endl;
		}
		else
		{
			// the has typed the correct file
			cout << "File open successful!" << endl;

			// return the exit value flag which is zero, meaning continue
			// running the program
			fileExist = true;
		}
	}
	// return the exit value flag, meaning the program should continue normally
	return returnExitValue;
}

/**
 * Creates an eclipseR object, which will then perform operations relating to
 * fstream (reading in from a file and writing output to console or a file),
 * error-checking, and sorting and searching.
 */
int main() {
	EclipseR eclipseR;

	return 0;
}

