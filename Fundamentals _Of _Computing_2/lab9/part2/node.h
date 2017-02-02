/* Author: Nick Palutsis
   Date: May 5, 2016
   CSE 20212
   Lab 9 Redo */
 
#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>
#include <string>
#include <stdlib.h>     
#include <vector>

using namespace std;
template<typename T> 
class Node {

  friend class BinaryTree;// make the main class a friend

 public:
  	Node(const T &, string);		// constructor
	T getData() const;				// gets the data
	string getLabel() const;		// gets the label
	bool find(int value );			// findes for a number

 private:
 	T data;				// data for linked list node
	Node<T> *right; 	// pointer to the right child
	Node<T> *left; 		// pointer to the left child
	string label; 		// string label
};

template<typename T>
Node<T>::Node(const T &info, string lab) :data(info),left(0),right(0),label(lab) {}

template<typename T>
T Node<T>::getData(void) const { return data; }

template<typename T>
string Node<T>::getLabel(void) const { return label; }

template<typename T>
bool Node<T>::find(int value ) {
	if (value  == this->data)
		return true;
	else if (value  < this->data) {
		if (left == NULL)
			return false;
		else
			return left->find(value);
	} 
	else if (value  > this->data) {
		if (right == NULL)
			return false;
		else
			return right->find(value);
    }
    return false;
}


#endif
