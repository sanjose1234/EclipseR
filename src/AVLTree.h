/*
 * TreeNode.h and AVLTree.h
 * This class creates the nodes for the AVL Tree
 * so that eclipses can be added on to it, including Tree nodes
 *  Created on: Dec 5, 2017
 *      Author: Eric Gonzalez
 */

#ifndef SRC_TREENODE_H_
#define SRC_TREENODE_H_
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "ResizableArray.h"
#include "Eclipse.h"
#include "EclipseR.h"
#include "Exception.h"
#include "HashNode.h"

using namespace std;


/**
 * PLEASE NOTE!!!
 *
 * This AVLTree class data structure implementation has been taken from
 * a website online. I have changed some code accordingly to better fit my overall
 * code.
 * Citation URL: http://www.sanfoundry.com/cpp-program-implement-avl-trees/
 */
/*
 * Node Declaration in a struct
 */
template<typename T>
struct AVLNode
{
    T data;
    AVLNode<T>* left;
    AVLNode<T>* right;
};

/*
 * Class Declaration
 */
template<typename T>
class AVLTree
{
private:

	AVLNode<T> *root;
public:
	int height(AVLNode<T>* temp);
	int diff(AVLNode<T>* temp);
	AVLNode<T>* rr_rotation(AVLNode<T>* parent); // right right rotations
	AVLNode<T>* ll_rotation(AVLNode<T>* parent); // left left rotations
	AVLNode<T>* lr_rotation(AVLNode<T>* parent); // left right rotations
	AVLNode<T>* rl_rotation(AVLNode<T>* parent); // right left rotation
	AVLNode<T>* balance(AVLNode<T>* temp);
	void setRoot(AVLNode<T>* tree);
	AVLNode<T>* insertNode(AVLNode<T>* root, T value);
	AVLNode<T>* getRoot();
	void display(AVLNode<T>* ptr, int level);
	void inorder(AVLNode<T>* tree);
	void preorder(AVLNode<T>* tree);
	void postorder(AVLNode<T>* tree);
	AVLNode<T>* find(AVLNode<T>* root, const T& value) const;
	void replace(AVLNode<T>* root, T value);
	AVLTree()
	{
		// initialize root to null
		root = nullptr;
	}
};

/*
 * Height of AVL Tree
 */
template<typename T>
int AVLTree<T>::height(AVLNode<T>* temp)
{
    int h = 0; // initialize
    if (temp != NULL) //
    {
        int l_height = height (temp->left);
        int r_height = height (temp->right);
        int max_height = max (l_height, r_height);
        h = max_height + 1;
    }
    return h;
}

/*
 * Height Difference
 */
template<typename T>
int AVLTree<T>::diff(AVLNode<T>* temp)
{
    int l_height = height (temp->left);
    int r_height = height (temp->right);
    int b_factor= l_height - r_height;
    return b_factor;
}

/**
 * right right rotation
 */
template<typename T>
AVLNode<T>* AVLTree<T>::rr_rotation(AVLNode<T>* parent)
{
	// create a temp node
	AVLNode<T>* temp;
	// assign temp as the parent pointing to the right node
	temp = parent->right;
	// assign the parent to the temp pointing to the left
	parent->right = temp->left;
	// assign the left temp as the parent
	temp->left = parent;
	return temp;
}

/*
 * Left- Left Rotation
 */
template<typename T>
AVLNode<T>* AVLTree<T>::ll_rotation(AVLNode<T>* parent)
{
    AVLNode<T>* temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

/**
 * Left- Right rotation
 */
template<typename T>
AVLNode<T>* AVLTree<T>::lr_rotation(AVLNode<T>* parent)
{
   AVLNode<T>* temp;
   temp = parent->left;
   parent->left = rr_rotation (temp);
   return ll_rotation (parent);
}

/**
 * Left- Right rotation
 */
template<typename T>
AVLNode<T>* AVLTree<T>::rl_rotation(AVLNode<T>* parent)
{
	AVLNode<T>* temp;
	temp = parent->right;
	parent->right = ll_rotation (temp);
	return rr_rotation (parent);
}

/*
 * Balancing AVL Tree
 */
template<typename T>
AVLNode<T>* AVLTree<T>::balance(AVLNode<T>* temp)
{
    int bal_factor = diff (temp);
    if (bal_factor > 1)
    {
        if (diff (temp->left) > 0)
        {
            temp = ll_rotation (temp);
        }
        else
        {
            temp = lr_rotation (temp);
        }
    }
    else if (bal_factor < -1)
    {
        if (diff (temp->right) > 0)
            temp = rl_rotation (temp);
        else
            temp = rr_rotation (temp);
    }
    return temp;
}

/**
 * sets the selected tree
 */
template<typename T>
void AVLTree<T>::setRoot(AVLNode<T>* tree)
{
	this->root = tree;
}


/*
 * Insert Element into the tree
 */
template<typename T>
AVLNode<T>* AVLTree<T>::insertNode(AVLNode<T> *root, T value)
{
	/**
	 * FIME: This application has requested the Runtime to terminate it in an unusual way.
		Please contact the application's support team for more information.
		terminate called after throwing an instance of 'std::invalid_argument'
  	  	what():  stoi.

  	  	This gives a runtime error above. The debug below shows that it enters the first
  	  	cout, but does not enter any of the if statements nor goes to whwere return is at??
	 */
//	cout << "I AM BEFORE INSERTING NODE" << endl;

    if (root == nullptr)
    {
 //       cout << "I AM IN ROOT == NULLPTR" << endl;
        root = new AVLNode<T>;
        root->data = value;
        root->left = nullptr;
        root->right = nullptr;
        return root;
    }
    else if (value < root->data)
    {
//        cout << "I AM IN VALUE < ROOT->DATA" << endl;

        root->left = insertNode(root->left, value);
        root = balance(root);
    }
    else if (value >= root->data)
    {
//    	cout << "I AM IN VALUE >= ROOT->DATA" << endl;

        root->right = insertNode(root->right, value);
        root = balance(root);
    }
 //   cout << "I TRYING TO RETURN THIS SHIT" << endl;

    return root;

}

/**
 * gets the root of the AVL Root
 */
template<typename T>
AVLNode<T>* AVLTree<T>::getRoot()
{
	return this->root;
}

/*
 * Display AVL Tree
 */
template<typename T>
void AVLTree<T>::display(AVLNode<T>* ptr, int level)
{
    int i;
    if (ptr!=nullptr)
    {
        display(ptr->right, level + 1);
        printf("\n");
        if (ptr == root)
        cout<<"Root -> ";
        for (i = 0; i < level && ptr != root; i++)
            cout<<"        ";
        cout<<ptr->data;
        display(ptr->left, level + 1);
    }
}


/*
 * Inorder Traversal of AVL Tree
 */
template<class T>
void AVLTree<T>::inorder(AVLNode<T>* tree)
{
	if (tree == nullptr) // of the tree is empty
	{
		return;
	}
	// print the inorder of the tree
	inorder (tree->left);
	cout<<tree->data<<"  ";
	inorder (tree->right);
}

/*
 * Preorder Traversal of AVL Tree
 */
template<typename T>
void AVLTree<T>::preorder(AVLNode<T>* tree)
{
	if (tree == nullptr) // if the tree is empty
	{
		return;
	}
	// print in pre order of the tree
	cout<<tree->data<<"  ";
	preorder (tree->left);
	preorder (tree->right);
}

/*
 * Postorder Traversal of AVL Tree
 */
template<typename T>
void AVLTree<T>::postorder(AVLNode<T>* tree)
{
    if (tree == nullptr) // if the tree is empty
    {
        return;
    }
    // print the post order of the tree
    postorder (tree ->left);
    postorder (tree ->right);
    cout<<tree->data<<"  ";
}

/**
 * Note this Find method was taken online, I've edited some parts to better fit
 * my overall code.
 * Citation URL: https://gist.github.com/danicat/7075125
 */
// Depth-First Search
template<typename T>
AVLNode<T>* AVLTree<T>::find(AVLNode<T>* root, const T& value) const {
  if(root)
  {
    //std::cout << root->GetValue() << std::endl;
    if(root->getValue() == value)
      return root; // Found
    else if(value < root->getValue())
      return Find(root->getLeft(), value);
    else
      return Find(root->getRight(), value);
  }

  return nullptr;
}

/**
 *	Citation URL: https://gist.github.com/danicat/7075125
 */
template<typename T>
void AVLTree<T>::replace(AVLNode<T> *root, T value)
{
	if (root == nullptr)
	{
		return;
	}
	replace(root->left, value);
	if(value->data == value)
	{
		value->data = value;
	}
	replace(root->right, value);
}

#endif /* SRC_TREENODE_H_ */
