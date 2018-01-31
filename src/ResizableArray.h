/*
 * ResizableArray.h
 *
 *  Created on: Sep 29, 2017
 *      Author: Eric Gonzalez
 */

#ifndef SRC_RESIZABLEARRAY_H_
#define SRC_RESIZABLEARRAY_H_
#include <iostream>
#include <iomanip>
#include <string>
#include "Exception.h"

using namespace std;


template <typename T>
class ResizableArray {
public:
	// constructors
	ResizableArray();
	ResizableArray(int customSize);
	// de-structor
	virtual ~ResizableArray();
	// mutator methods
	void add(T item);
	void addAt(T item, int index);
	void replaceAt(const T& temp, int index);
	void removeAt(int index);
	T& operator[] (int k);
	T* doubleArray();
	T* halveArray();
	bool isEmpty();
	int length();
	T* getData();

/**
 * private variables of the ResizableArray class
 */
private:
	// generic pointer of the array
	T* oldArray;
	// size of array
	int sizeArray;
	// current index
	int elementCounter;
};

/**
 * generic constructor
 */
template <typename T>
ResizableArray<T>::ResizableArray() {
	// create a new memory location of size ten
	oldArray = new T[10];
	// assign the size of the array to 10
	sizeArray = 10;
	// set the current index to zero
	elementCounter = 0;
}

// constructor of a custom size besides 10
template <typename T>
ResizableArray<T>::ResizableArray(int customArray) {
	// resize the size of the array's memory location according to the input
	oldArray = new T[customArray];
	// assign the user input to the size array variable
	sizeArray = customArray;
	// set elementCounter to zero
	elementCounter = 0;
}

template <typename T>
/**
 * destructor method
 */
ResizableArray<T>::~ResizableArray() {
	// leave empty
}
/* mutator method that takes an item as its parameter and
 adds the item to the end of the array.
 CODE SOURCE: Alex KloppenBurg
 */
template <typename T>
void ResizableArray<T>::add(T item) {
	if (elementCounter > sizeArray - 1)
	{
		oldArray = doubleArray();
	}
	// assign the item to the current index of the array
	oldArray[elementCounter] = item;

	// increment elementCounter
	elementCounter++;
}


/**
 * A mutator method that takes an item and an
 *  index as its parameters and adds the item
 */
// create a template to accept any generic variable
template <typename T>
void ResizableArray<T>::addAt(T item, int index) {
	// if the index is greater then the elementCounter or
	// if the index is less than
	if (index > elementCounter || index < 0) {
		throw Exception();
	}
	else {
		if (elementCounter == sizeArray - 1) {
			oldArray = doubleArray();
		}

		// loop the the size of the array
		for (int i = elementCounter; i > index; --i) {
			// shifting elements over to make room for the item being inserted
			oldArray[i+1] = oldArray[i];
		}

		oldArray[index] = item;
	}
}

template <typename T>
/**
 * A mutator method that takes an item and an index as its parameters and
 * replaces the item previously at the index given with the new item.
 * CODE SOURCE: Nathan Thomas
 */
void ResizableArray<T>::replaceAt(const T& item, int index) {
	// if the index is greater than the elementCounter
	// or index is less than 0
	if (index >= elementCounter || index < 0) {
		// throw the exception class
		throw Exception ();
	}
	// replace the item to the specified index
	oldArray[index] = item;
}

/**
 * A mutator method that takes an index as its parameter and removes
 * the item at that index from the array, shifting by one index as
 * necessary to fill the gap left in the array by the removal.
 * CODE SOURCE: Nathan Thomas
 */
template <typename T>
void ResizableArray<T>::removeAt(int index) {
	// if the index is greater than the current index
	// or if the index or index is less than zero
	if (index >= elementCounter || index < 0) {
		// throw the exception class
		throw Exception ();
	}
	// loop through up to the previous current index
	for (int i = index; i < elementCounter - 1; ++i) {
		// assign each index to the index next ot it
		oldArray[i] = oldArray[i + 1];
	}
	// decrement in order to correct the current index
	--elementCounter;

	// if dividing the size of the array by the current index
	// is greater than or equal to 2
	if (sizeArray / elementCounter >= 2)
	{
		// halve the array
		halveArray(oldArray, sizeArray);
	}
}

template <typename T>
T* ResizableArray<T>::doubleArray() {

	// double the size
	sizeArray *= 2;
	// allocate the string pointer to a new memory location with the
	// doubled size
	T* newArray = new T[sizeArray];

	// in order to copy over without overflow, half sizeNum in the loop
	//[................]	<- newArray
	//[.......]				<- oldArray
	//                 ^	<- the carrot is sizeNum
	// loop thru and copy over the data into the newArray
	for (int i = 0; i < (sizeArray / 2); i++) // half sizeNum to prevent stack overflow
	{
		// copy over the data from the old array into the new array
		newArray[i] = oldArray[i];
	}
	// delete the old array
	delete[] oldArray;
	// return the new array
	return newArray;
}

/**
 * this function should half the size of the array
 * whenever the array is too big
 */
template <typename T>
T* ResizableArray<T>::halveArray() {
	// halve the size of the array
	sizeArray /= 2;
	// create a new memory allocation for the array
	T* newArray = new T[sizeArray];
	// in order to copy over without overflow
	//[................]		<- newArray
	//[........]				<- oldArray
	//        ^					<- the carrot is sizeNum
	// loop through the size of the array
	for (int i = 0; i < sizeArray; i++) {
		// transfer the data from the old array to the new array
		newArray[i] = oldArray[i];
	}
	// delete the old memory allocation
	delete[] oldArray;
	// return the new correct array
	return newArray;
}
/**
 * this function checks if the array is empty
 */
template <typename T>
bool ResizableArray<T>::isEmpty() {
	// if the index is at zero
	if (elementCounter == 0) {
		// return true
		return true;
	}
	else {
		// else return false
		return false;
	}
}

/**
 * this function returns the length of the resizable array
 */
template <typename T>
int ResizableArray<T>::length() {
	return elementCounter;
}

/**
 * this functions gets the data of the array
 */
template <typename T>
T* ResizableArray<T>::getData()
{
	return oldArray;
}

/**
 *  overload operator array function that takes in an int
 */
template <typename T>
T& ResizableArray<T>::operator[] (int k) {
	if ((k < 0) || (k >= sizeArray))
	{
		throw exception();

	}
	return oldArray[k];
}

//template <typename T>
//void print() {
//	for (int i = 0; i < sizeArray; i++)
//	{
//		cout << oldArray
//	}
//}

#endif /* SRC_RESIZABLEARRAY_H_ */
