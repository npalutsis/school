/* Author: Nick Palutsis
   Date: May 5, 2016
   CSE 20212
   Lab 9 Redo */

#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#include "node.h" 
#include <iostream>   
#include <string>
#include <list>
#include <utility> 
#include <fstream>
#include <stdlib.h>   
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <time.h>    
#include <iomanip> 

using namespace std;

class BinaryTree{
	public:
		BinaryTree(); // constructor
		void preorder() const;
		void inorder() const;
		void postorder() const;
		int find(int) const; // looks for a value in the tree
		void findwinner() const; // names final four, finals, and winner
		void print(Node<int>*, int); // prints the binary tree
		void insert(int key, string lab);
		
	private:
		Node<int> *first; // points to the root node
		vector<Node<int> * > allNodes; // for the winner algorithm
		void insertUtility(int, string, Node<int> *);
		void preorderUtility(Node<int>*) const;
		void inorderUtility(Node<int>*) const;
		void postorderUtility(Node<int>*) const;
		

};

// constructor
BinaryTree::BinaryTree(){
	first = 0; // tree is empty

	// Read in values for tree from file
	string fileName, labelFile;
	int valueFile;

	fileName="data.txt";
	ifstream inFile;
	inFile.open(fileName.c_str());

	Node<int> *tempNode;
	while(!inFile.eof()){ 
		inFile >> labelFile;
		inFile >> valueFile;
		insert(valueFile, labelFile);
		tempNode = new Node<int>(valueFile, labelFile);
		allNodes.push_back(tempNode);	// add node
	}
}

// insert node to tree
void BinaryTree::insert(int key, string lab){
	if(first!=NULL)
		insertUtility(key, lab, first);
	else{
		first=new Node<int>(0, " ");	// make a new empty node
		first->data=key;	// sets key value
		first->label=lab;	// sets label
		// initialize its children to NULL
		first->left=NULL;
		first->right=NULL;
	}
}

// insert utility
void BinaryTree::insertUtility(int key, string lab, Node<int> *node){
	if(key <= node->data) { 
		if(node->left!=NULL) 	// add it to the left
			insertUtility(key, lab, node->left);
		else {
			node->left=new Node<int>(0, " ");
			node->left->data=key;	
			node->left->label=lab;
			node->left->left=NULL;
			node->left->right=NULL;  
		}  
		}
	else if(key > node->data) {
		if(node->right!=NULL) // add it to the right
			insertUtility(key, lab, node->right);
		else {
			node->right=new Node<int>(0, " ");
			node->right->data=key;
			node->right->label=lab;
			node->right->left=NULL;
			node->right->right=NULL;
		}
	}
}

// print the entire tree
void BinaryTree::print(Node<int>* p, int indent){
	if(p != NULL) {
		if(p->right)
			print(p->right, indent + 4);
		if (indent)
			cout << setw(indent) << ' ';
		if (p->right) 
			cout <<" /\n" << setw(indent) << ' ';
		cout<< p->data << "\n ";
		if(p->left) {
			cout << setw(indent) << ' ' <<" \\\n";
			print(p->left, indent + 4);
		}
	}
}


// findes the tree
int BinaryTree::find(int findVal) const{
	if (first == NULL)
		return 0;
	else
		return first->find(findVal);
}

// Randomly finds a winner
void BinaryTree::findwinner() const{
	int numOfNodes = allNodes.size();
	string FinalFour1, FinalFour2, FinalFour3, FinalFour4;
	int val1, val2, val3, val4, currNum;
	srand (time(NULL));
	val1 = (rand() % 4 + 1);
	srand (time(NULL));
	val2 = (rand() % 4 + 5);
	srand (time(NULL));
	val3 = (rand() % 4 + 9);
	srand (time(NULL));
	val4 = (rand() % 4 + 13);
	
	FinalFour1 = allNodes[val1]->label; 
	FinalFour2 = allNodes[val2]->label; 
	FinalFour3 = allNodes[val3]->label; 
	FinalFour4 = allNodes[val4]->label; 
	
	cout << "\n******************" << endl;
	cout << "*** Final Four *** " << endl;
	cout << "******************" << endl;
	cout << "  1: " << FinalFour1 << endl;
	cout << "  2: " << FinalFour2 << endl;
	cout << "  3: " << FinalFour3 << endl;
	cout << "  4: " << FinalFour4 << endl;
	
	// championship
	int champ1 = min(val1, val2);
	string champ1s = allNodes[champ1]->label;
	int champ2 = min(val3, val4);
	string champ2s = allNodes[champ2]->label;

	cout << "\n******************" << endl;
	cout << "** Championship **" << endl;
	cout << "******************" << endl;
	cout << "  1: " << champ1s << endl;
	cout << "  2: " << champ2s << endl;
	
	// winner
	int randomChamp, winner, dif1, dif2;
	srand (time(NULL));
	randomChamp = (rand() % numOfNodes);
	if (randomChamp > champ1)
		dif1 = randomChamp - champ1;
	else
		dif1 = champ1 - randomChamp;
	if (randomChamp > champ2)
		dif2 = randomChamp - champ2;
	else
		dif2 = champ2 - randomChamp;
	winner = min(dif1, dif2);
	if (winner == dif1){
		cout << "\n******************" << endl;
		cout << "***** WINNER *****" << endl;
		cout << "******************" << endl;
		cout << "  1: " << champ1s << "!" << endl << endl; 
	}
	else{
		cout << "\n******************" << endl;
		cout << "***** WINNER *****" << endl;
		cout << "******************" << endl;
		cout << "  1: " << champ2s << endl << endl; 
	}
}


// preorder traversal
void BinaryTree::preorder() const{
	preorderUtility(first);
}

// utility function
void BinaryTree::preorderUtility( Node<int> *first) const{
	if (first != 0){
		cout << first->data << ", ";
		preorderUtility(first->left); 
		preorderUtility(first->right); 
	}
}

// inorder traversal
void BinaryTree::inorder() const{
	inorderUtility(first);
}

// utility function
void BinaryTree::inorderUtility( Node<int> *first) const{
	if (first != 0){
		inorderUtility(first->left);
		cout << first->data << ", "; 
		inorderUtility(first->right); 
	}
}

// postorder traversal
void BinaryTree::postorder() const{
	postorderUtility(first);
}

// utility function
void BinaryTree::postorderUtility(Node<int> *first) const{
	if (first != 0){
		postorderUtility(first->left);
		postorderUtility(first->right);
		cout << first->data << ", "; 
	}
}

#endif
