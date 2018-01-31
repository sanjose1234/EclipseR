/*
 * HashMap.h
 *
 *  Created on: Nov 16, 2017
 *      Author: Eric Gonzalez
 */

#ifndef HASHMAP_H_
#define HASHMAP_H_
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "ResizableArray.h"
#include "Eclipse.h"
#include "EclipseR.h"
#include "Exception.h"
#include "HashNode.h"
/**
 * This class will create a HashMap data structure to handle eclipse data
 * Note:
 * This class is based off of code online and I have made changes that would benefit my code
 * Source: http://www.sanfoundry.com/cpp-program-hash-tables-singly-linked-list/
 */
template<typename T>
class HashMap {
private:
	// double pointer of type HashNode
	HashNode<T>** htable;
public:
	// constructor that intializes the htable variable
	HashMap()
	{
		int TABLE_SIZE = 128;
		// create a new memory pointer of the const variable size (128)
		htable = new HashNode<T>*[TABLE_SIZE];
		// loop through the size of the table
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			// initialize it to a null pointer
			htable[i] = nullptr;
		}
	}

	HashMap(LinkedList<T>* list)
	{
		TABLE_SIZE = list->getLength();
		htable = new HashNode<T>*[TABLE_SIZE];
		for(int i = 0; i < TABLE_SIZE; i++)
		{
			htable[i] = nullptr;
		}

		int hashVal;
		int key;
		HashNode<T>* previous;
		HashNode<T>* entry;
		for(int j = 0; j < TABLE_SIZE; j++)
		{
			hashVal = hashFunction(stoi(list->getData(j).getColumnElement(1)));
			key = stoi(list->getData(j).getColumnElement(1));
			previous = nullptr;
			entry = htable[hashVal];


			while(entry != nullptr)
			{
				previous = entry;
				entry = entry->next;
			}
			if(entry = nullptr)
			{
				entry = new HashNode<T>(key, list->getData(j));
				if(previous == nullptr)
				{
					htable[hashVal] = entry;
				}
				else
				{
					previous->next = entry;
				}
			}
			else {
				entry->value = list->getData(j);
			}
		}
	}

	// destructor
	~HashMap()
	{
		// loop through the size of the hash table
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			// take each element of the hash table and
			// assign it to a HashNode pointer variable called entry
			HashNode<T>* entry = htable[i];
			// while the HashNode is not null pointer
			while (entry != nullptr)
			{
				// take the entry pointer and assign it to the previous pointer
				HashNode<T>* previous = entry;
				// point the entry variable to the next hashNode
				entry = entry->next;
				// delete the previous node
				delete previous;
			}
		}
		// delete the hashtable
		delete[] htable;
	}

	/**
	 * Hash Function
	 */
	int HashFunction(int key)
	{
		// mods the key to the size of the hash table
		return key % TABLE_SIZE;
	}

	/**
	 * this function will Insert a Hash Node w/ a value
	 */
	void Insert(int key, T value)
	{
		// gets the hash function of the key and assign it to a hash value variable
		int hash_val = HashFunction(key);
		// previous HashNode pointer initialized
		HashNode<T>* previous = nullptr;
		// assign the hash value and assign it to a entry pointer
		HashNode<T>* entry = htable[hash_val];
		// while the entry node is not null
		while (entry != nullptr)
		{
			// take the entry and assign to the previous
			previous = entry;
			// point the entry node to the next node
			entry = entry->next;
		}

		//  myName.at(i)

		// if the entry node is null
		if (entry == nullptr)
		{
			// take entry and create a new instance in the memory location
			entry = new HashNode<T>(key, value);
			// if the previous node is null
			if (previous == nullptr)
			{
				// take the entry and assign it to the hash table wherever the hash value is
				htable[hash_val] = entry;
			}
			else // if previous node is not null
			{
				// take the entry node and assign it to the previous node that is pointing to the next node
				previous->next = entry;
			}
		}
		else // if entry node is not null
		{
			// take value and assign to the entry variable that is pointing to the value
			entry->value = value;
		}
	}

	/**
	 * this function removes a hashNode
	 */
	void Remove(int key)
	{
		// Takes the hash function of the key and assign it to a
		int hashVal = HashFunction(key);
		// takes the element of the value of the hashTable and assign it to a entry HashNode pointer
		HashNode<T>* entry = htable[hashVal];
		// initialize the previous hashnode
		HashNode<T>* previous = nullptr;
		// if the entry node is null OR the entry
		if (entry == nullptr || entry->key != key)
		{
			cout << "No Element found at key " << key << endl;
		}
		while (entry->next != nullptr)
		{
			previous = entry;
			entry - entry->next;
		}
		if (previous != nullptr)
		{
			previous->next = entry->next;
		}
		delete entry;
		cout << "Element has been Deleted!" << endl;
	}

	/**
	 * Search Element at a key
	 */
	int Search(int key)
	{
		// boolean flag used to catch is the item has been found
		bool isFlag = false;
		// takes the hashFunction of the key and assign it to a hashVal variable
		int hashVal = HashFunction(key);
		// takes the element in the hashtable and assign it to a entry hashnode variable
		HashNode<T>* entry = htable[hashVal];
		// while the entry hashnode is not null
		while (entry !=  nullptr)
		{
			// if the entry node pointing to the key is actually the key
			if (entry->key == key)
			{
				// output the entry node pointing to the value
				cout << entry->value << " ";
				// set the bool flag to true
				isFlag = true;
			}
			// point entry node to the next node
			entry = entry->next;
		}
		// if the flag is true
		if (!isFlag)
		{
			// return a -1
			return -1;
		}
	}

	/**
	 * displays the buckets within the hash table
	 */
	void display()
	{
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			if (htable[i] != nullptr && htable[i]->key != -1)
			{
				cout << "Bucket = " << htable[i]->key << "," << " value = " << htable[i]->value << endl;
			}
		}
	}
};

#endif /* HASHMAP_H_ */
