/*
 * HashNode.h
 * This class creates the HashNode object so that It can be ready to be added
 * into the HashMap
 *  Created on: Nov 16, 2017
 *      Author: Eric Gonzalez
 */

#ifndef HASHNODE_H_
#define HASHNODE_H_
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "ResizableArray.h"
#include "Eclipse.h"
#include "EclipseR.h"
#include "Exception.h"
using namespace std;
int TABLE_SIZE = 128;
/**
 * HashNode Class definition
 * Note:
 * This code is based off of a code online, I've changed some code to better fit my base
 * code.
 * Source: http://www.sanfoundry.com/cpp-program-hash-tables-singly-linked-list/
 */
template<typename T>
class HashNode {
public:
	// HashTable key
	int key;
	// HashTable value
	T value;
	// HashNode pointer object
	HashNode* next;
	// HashNode constructor
	HashNode(int key, T value) // takes in a HashTable key and value
	{
		// the instance of key is initialized to itself
		this->key = key;
		// the instance of value is initialized to itself
		this->value = value;
		// initialize next variable to a nullpointer
		this->next = nullptr;
	}
};

#endif /* HASHNODE_H_ */
