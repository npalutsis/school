/* Author: Nick Palutsis
   Date: May 5, 2016
   CSE 20212
   Lab 9 Redo */

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "binaryTree.h"
#include <string>
#include <list>
#include <utility> 
#include <fstream>

using namespace std;
int main(){
	int choice;
	BinaryTree marchMadness;		// Create bracket

	cout << "What would you like to do?" << endl;
	cout << "  [1] Find a value in the tree" << endl;
	cout << "  [2] Traverse the tree" << endl;
	cout << "  [3] Run March Madness simulator" << endl;
	cin >> choice;

	if(choice == 1){
		cout << "What value would you like to look for: ";
		cin >> choice;
		if (marchMadness.find(choice)){
			cout << "The number " << choice << " has been found in the tree!" << endl;
		}
		else{
			cout << "The number " << choice << " has not been found in the tree!" << endl;
		}
	}
	else if(choice == 2){
		cout << "Pre-order traversal:" << endl;
		marchMadness.preorder();
		cout << endl << endl;
		cout << "In-order traversal:" << endl;
		marchMadness.inorder();
		cout << endl << endl;
		cout << "Post-order traversal:" << endl;
		marchMadness.postorder();
		cout << endl;
	}
	else if(choice == 3)
		marchMadness.findwinner();		// Name final four, finals, and winner
	else
		cout << "ERROR: Invalid input" << endl;
}
