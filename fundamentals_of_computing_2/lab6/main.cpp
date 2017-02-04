/* Author: Nick Palutsis
	Date: March 4, 2016
	CSE 20212
	Lab 6 */
	
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include "puzzle.h"

int main(){
	Puzzle<int> sudoku(9);
	cout << "Let's play sudoku!" << endl;
	sudoku.simulate();
	
	return 0;
}
