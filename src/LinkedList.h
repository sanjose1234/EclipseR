/*
 * LinkedList.h
 *
 *  Created on: Nov 2, 2017
 *      Author: Eric Gonzalez
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "ResizableArray.h"
#include "Eclipse.h"
#include "EclipseR.h"

using namespace std;

//template<typename T>
//class LinkedList {
//private:
//	T* info;
//	T* next;
//
//public:
////	LinkedList();
////	LinkedList(T& info);
////	LinkedList(T& info, T* next);
////	void copy(const LinkedList<T>& II);
////	LinkedList(const LinkedList<T>& ll);
////	bool isempty();
////	T& info();
////	int size();
////	T& find(T& key);
////	T& infoat(int position);
////	void add(T& object);
////	void insertat(T& newObj,int position);
////	T remove();
////	T removeat(int position);
////	void operator=(const LinkedList<T>& ll);
////	virtual LinkedList<T>*next();
//
//	// default constructor of LinkedList class
//	LinkedList()
//	{
//		info = nullptr;
//		next = nullptr;
//	}
//
//	LinkedList(T& info)
//	{
//		info = new T(info);
//		if(info == nullptr)
//		{
//			throw exception();
//			next = nullptr;
//		}
//	}
//
//};

/**
 * --NOTE!--
 * This linked list class based is based off of code online.
 * I've modified it to best suit my code.
 * Source:
 * https://www.codementor.io/codementorteam/a-comprehensive-guide-to-implementation-of-singly-linked-list-using-c_plus_plus-ondlm5azr
 */
template <typename T>
class LinkedList
{
	/**
	 * define a struct which defines a single node
	 */
	struct node
	{
		// templated variable for the data section
		T data;
		// node pointer variable that points to the next node
		node *next;

		node()
		{
			next = nullptr;
		}
	};

private:
	// crate a head and tail pointers of type node
	node *head, *tail, *curr;
	// used to count nodes created
	int sizeNodeCounter;
//	T* info;

public:

	/**
	 * LinkedList constructor to initialize variables
	 */
	LinkedList()
	{
		// initialize variables
		head = nullptr;
		tail = nullptr;
		curr = nullptr;
		sizeNodeCounter = 0;
//		info = 0;
	}

	/**
	 * destructor
	 */
	~LinkedList()
	{
		// leave empty
	}

	/**
	 * these following functions will set up the linked list
	 * ---------------------------------------------------------------------
	 */

	/**
	 * this function will create a new node at the end
	 * of the linked list and takes in a given value input
	 */
	void createNode(T value)
	{
		// create a temporary node pointer
		node *newNode = new node;
		// have newNode point to the data section and it is assigned by the given value input
		newNode->data = value;
		// have newNode point to the next node (which is currently null)
		newNode->next = nullptr;

		// if the head is null
		if (head == nullptr) // then the linked list is empty
		{
			// assign newNode to the head
			head = newNode;
			// assign newNode to the tail
			tail = newNode;
			// assign newNode to null
			newNode = nullptr;
		}
		else // else if the head is not null
		{
			// point the tail to the next node (which is newNode)
			tail->next = newNode;
			// assign the newNode variable as the new tail
			tail = newNode;

			// count the new node
			sizeNodeCounter++;
		}
	}

	/**
	 * this function shows see what is in our linked list
	 */
	void display()
	{
		// create a temporary node
		node *newNode = head;
		//new node;
		// assign the head to the newNode node
		//	newNode = head;

		// while the newNode node is not null
		while(newNode != nullptr)
		{
			// print the node that is pointing to data
			cout << newNode->data;
			// point the newNode node to the next node
			newNode = newNode->next;
		}
	}

	/**
	 * this function adds a new node at the front of the linked list
	 */
	void addAtFront(T value)
	{
		// create a newNode node
		node *newNode = new node;
		// assign the specified value to the newNode node that is pointing to the data section
		newNode->data = value;
		// put the new node at the front
		newNode->next = head;
		// re-assign the head as the newNode node that is placed at the front
		head = newNode;

		// count the new node that has been added at the front
		sizeNodeCounter++;
	}

//	void insertAt(T& newObj, int position)
//	{
//		if(position == 0)
//		{
//
//		}
//	}

	/**
	 * this function adds a new node at the end of the linked list
	 */
	void addAtEnd(T value)
	{
		// create a new node
		node *newNode = new node;
		// point the new node to the data section, and assign it to the specified value
		newNode->data = value;
		// assign the new node to the tail
		newNode->next = tail;
		// the new node becomes the tail at the end of the linked list
		tail = newNode;

		// count the new node that has been added at the end
		sizeNodeCounter++;
	}

	/**
	 * this function keeps the linked list sorted when it adds new nodes
	 * NOTE:
	 * This function is based off from an online website. I've changed it accordingly to fit my program code
	 * Citation: https://stackoverflow.com/questions/41959004/keeping-a-linkedlist-always-sorted
	 */
	void add(T x) // takes in a eclipse data type
	{
		// create start, previous, current, new node pointers
		node *newNode = new node();
		// assign the data type eclipse as the new node
		newNode->next = nullptr;
		// assign the new eclipse variable to a new node variable pointing to the data
		newNode->data = x;
		// if the start node is node
		if(head == nullptr)
		{
			// set the new node as the start node
			head = newNode;
			// set the start node as the current node
			curr = newNode;
			sizeNodeCounter++;
			// return to break out the function
			return;
		}

		// if the new node column element is less than the column element of the head
		if (newNode == nullptr)
		{
			// state that the new node is null
			cout << "new node is null" << endl;
		}

		/**
		 * There is a bug located in this if conditional statement
		 */
		if(newNode->data.getColumnElement(0) < head->data.getColumnElement(0))
		{
			// assign the start node as the new node
			newNode->next = head;
			// assign the new node as the start node
			head = newNode;
			// assign the start node as the current node
			curr = head;
			// counts the node added to the list
			sizeNodeCounter++;
			return;
		}
		// assign the head node to a node pointer previous
		node *previous = head;
		// assign the current to the previous node
		curr = head;

		// while the current node is not null and if the column element of the current is less
		// than the column element of the new node
		while(curr != nullptr && curr->data.getColumnElement(0) < newNode->data.getColumnElement(0))
		{
			// then assign each current node as the previous node
			previous = curr;
			// point the current node to the next node
			curr = curr->next;
		}
		// assign previous node to the new node to point to the next node
		newNode->next = previous->next;
		// assign the new node as the previous node
		previous->next = newNode;
		// assign the new node as the current node
		curr = newNode;
		sizeNodeCounter++;
		return;
	}

	/**
	 * gets the length of the linked list
	 */
	int length()
	{
		return sizeNodeCounter;
	}

	/**
	 * this function adds a new node at a specified position in the linked list
	 */
	void insertNodeAt(int position, T value)
	{
		// create a new node that is previous to the current node
		node *previousNode = new node;
		// create a current node
		node *currentNode = new node;
		// crate a new node that is between the previous and current node
		node *newNode = new node;
		// the current node now becomes the head
		currentNode = head;

		// loop the list to the specified node
		for (int i = 1; i < position; i++)
		{
			// the previous node becomes the current node
			previousNode = currentNode;
			// assign the current pointed to the next node to the current node
			currentNode = currentNode->next;
		}
		// the new node to data becomes the value
		newNode->data = value;
		// the new node becomes the previous node to the next
		previousNode->next = newNode;
		// new node to the next is the current node
		newNode->next = currentNode;

		// count the new node that has been added at the specified location
		sizeNodeCounter++;
	}

	/**
	 * linked list manipulation functions
	 * ----------------------------------------------------------------------------
	 */

	/**
	 * deletes the node at the beginning of the loop
	 */
	void deleteAtStart()
	{
		// create a new removeNode node
		node *removeNode = new node;
		// have the temp node be the head node
		removeNode = head;
		// point the head to the next node
		head = head->next;
		// delete the oldNode
		delete removeNode;

		// decrement the node that has been removed
		sizeNodeCounter--;
	}

	/**
	 * deletes the end of the node
	 */
	void deleteAtEnd()
	{
		// create the node we want to delete
		node *currentNode = new node;
		// create the node that is previous to current node
		node *previousNode = new node;
		// the current node is the head
		currentNode = head;

		// while the current node is not point to null
		while(currentNode->next != nullptr)
		{
			// the previous node is the current node
			previousNode = currentNode;
			// the current node then points to the next node
			currentNode = currentNode->next;
		}
		// the previous node becomes the tail
		tail = previousNode;
		// the previous node now points to a null node
		previousNode->next = nullptr;
		// delete the current node
		delete currentNode;

		// decrement the size, since we deleted the node at the end
		sizeNodeCounter--;
	}

	/**
	 * deletes a node at a specified position
	 */
	void deleteAt(int position)
	{
		// create the current node
		node *currentNode = new node;
		// create the previous node
		node *previousNode = new node;
		// the current node becomes the head
		currentNode = head;
		// loop to the specified position node
		for (int i = 1; i < position; i++)
		{
			// current node becomes the previous node
			previousNode = currentNode;
			// the current node points the next node
			currentNode = currentNode->next;
		}
		// the current node becomes the previous node and both point to the next node
		previousNode->next = currentNode->next;

		// decrement the node that has been removed
		sizeNodeCounter--;
	}

	/*
	 * a replace function to replace a node at a specified value and position
	 */
	void replaceNode(T value, int position)
	{
		// create a current pointer node
		node *currentNode = new node;
		// loop through the linked list until we reach the desired position node
		for(int i = 0; i < position; i++)
		{
			// have the current node point to the data section
			currentNode = currentNode->data;
		}
		// the specified value becomes the current node
		currentNode->data = value;
	}
};

#endif /* LINKEDLIST_H_ */
