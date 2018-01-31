/*
 * EclipseR.h
 *
 *  Created on: Oct 30, 2017
 *      Author: User
 */

#ifndef ECLIPSER_H_
#define ECLIPSER_H_

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "ResizableArray.h"
#include "Eclipse.h"
#include "EclipseR.h"
#include "LinkedList.h"
#include "HashMap.h"
#include "HashNode.h"
#include "AVLTree.h"

using namespace std;

class EclipseR {
public:
	EclipseR();
	string dataManipulationInput(string headerLine[10]);
	int startInput();
	int eclipseIsValid;
	int main();
private:
	// Creates an array in which each element is a row of data
	ResizableArray<Eclipse> eclipsesRA;
	// creates a linked list object to store eclipses
	LinkedList<Eclipse> eclipsesLL;
	// creates a hash map object to store eclipses
	HashMap<Eclipse> eclipsesHM;
	// creates a AVLTree object to store eclipses
	AVLTree<Eclipse> eclipsesAVL;
	// Input file stream
	ifstream inputFileFS;
	// Output file stream
	ofstream outputFileFS;

	// the maximum number of columns
	const int MAX_COL_INDEX = 18;
	// the minimum number of columns
	const int MIN_COL_INDEX = 16;
};

#endif /* ECLIPSER_H_ */
