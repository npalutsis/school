/* Author: Nick Palutsis
	Date: April 20, 2016
	CSE 20212
	Lab 10 */
	
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include "puzzle.h"

int main(){
	Puzzle<int> sudoku(9);
	cout << "Let's play sudoku!" << endl;
	sudoku.sudokuSolver();
	
	return 0;
}
