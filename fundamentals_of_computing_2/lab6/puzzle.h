/* Author: Nick Palutsis
	Date: March 4, 2016
	CSE 20212
	Lab 6 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

template <class T> 
class Puzzle{
	
	public:
		Puzzle(int = 9);
		void print();
		void simulate();
		int checkAcross(int, T);
		int checkDown(int, T);
		int checkBox(int, int, T);
		int win();
		int onlyOne();
		void findOptions();
		int numOptions(int, int);
		int singleton();
		int rowSingleton(int, int, int);
		int colSingleton(int, int, int);
		int gridSingleton(int, int, int);
		
	private:
		vector<vector<vector<T> > > board;
};

//====================================

template<typename T>
Puzzle<T>::Puzzle(int arraySize){
	
	string FILE;
	cout << "Please enter a file name: ";		// reads in a file
	cin >> FILE;	

	ifstream infile;
	infile.open(FILE.c_str());
	
	T value;
	vector <T> oneDVec(9);
	vector<vector<T> > twoDVec;
	
	for(int i=0; i < 9; i++)				// creates a vector of vectors for the board
		twoDVec.push_back(oneDVec);
	
	for(int i=0; i < 10; i++)				// creates a 3D vector for the board
		board.push_back(twoDVec);
	
	for(int i=0; i < arraySize; i++){			// stores the characters from file in the vector
		for(int j=0; j < arraySize; j++){
			infile >> value;
			board[i][j][0] = value;
		}
	}
}

template<typename T>
void Puzzle<T>::print(){
	int countR = 0;
	int countC = 0;
	cout << "    1 2 3   4 5 6   7 8 9\n";		// titles the columns for the board
	cout << "  -------------------------\n";
	for(int i=0; i < 9; i++){
		cout << i+1 << " | ";
		for(int j=0; j < 9; j++){
			cout << board[i][j][0] << " ";
			if(++countR == 3){			// adds dividers every three columns for mini grid
				cout << "| ";
				countR = 0;
			}
		}	
		cout << endl;
		if(++countC == 3){			// adds dividers every three rows for mini grid
			cout << "  -------------------------\n";
			countC = 0;
		}
	}

}

// Checks for valid inputs in row
template<typename T>
int Puzzle<T>::checkAcross(int row, T value){
	for(int i=0; i < 9; i++){
		if(board[row][i][0] == value){;
			//cout << value << " matches row " << row << " column " << i << endl;
			return 0;
		}
	}
	//cout << "Row Works! " << row << endl;
	return 1;
}

// Checks for valid inputs in column
template<typename T>
int Puzzle<T>::checkDown(int col, T value){
	for(int i=0; i < 9; i++){
		if(board[i][col][0] == value){
			//cout << value << " matches row " << i << " column " << col << endl;
			return 0;
		}
	}
	//cout << "Column Works!" << col << endl;
	return 1;
}

// Checks for valid inputs in mini grid
template<typename T>
int Puzzle<T>::checkBox(int ROW, int COL, T value){

	int rowT = ROW / 3 * 3;
	int rowB = rowT + 2;
	int colL = COL / 3 * 3;
	int colR = colL + 2;
	
	for(int i=rowT; i <= rowB; i++){
		for(int j=colL; j <= colR; j++){
			if(board[i][j][0] == value){
				//cout << value << " matches row " << i << " column " << j << endl;
				return 0;
			}
		}
	}
	//cout << "Box Works!" << ROW << " " << COL << endl;
	return 1;
}

// checks if board is filled
template<typename T>
int Puzzle<T>::win(){
	for(int i=0; i < 9; i++){
		for(int j=0; j < 9; j++){
			if(board[i][j][0] == 0)
        		return 0;
    	}
    }
	return 1;
}

// Checks if there is only one option, and if so replaces zero with value
template<typename T>
int Puzzle<T>::onlyOne(){
	int found = 0;
	for(int row = 0; row < 9; row++){
		for(int col = 0; col < 9; col++){
			if(board[row][col][0] == 0){
				if(numOptions(row, col) == 1){
					for(int i = 1; i < 10; i++){
						if(board[row][col][i] == 1){
							board[row][col][0] = i;
							found = 1;
						}
					}
				}
			}
		}
	}
	return found;
}

// Finds which moves are possible and assigns 1/0 in 3-d array
template<typename T>
void Puzzle<T>::findOptions(){
	for(int row = 0; row < 9; row++){
		for(int col = 0; col < 9; col++){
			if(board[row][col][0] == 0){
				for(int i = 1; i < 10; i++){
					if(checkAcross(row, i) && checkDown(col, i) && checkBox(row, col, i))
						board[row][col][i] = 1;
					else
						board[row][col][i] = 0;
				}
			}
		}
	}

}

// returns how many possible values an element can be
template<typename T>
int Puzzle<T>::numOptions(int row, int col){
	int count = 0;
	for(int i = 0; i < 10; i++){
		if(board[row][col][i])
			count++;
	}
	return count;
}

// finds singleton and replaces value when found
template<typename T>
int Puzzle<T>::singleton(){
	int found = 0;
	for(int row = 0; row < 9; row++){						// Cycles through rows of board
		for(int col = 0; col < 9; col++){					// Cycles through columns of board
			if(board[row][col][0] == 0){
				for(int val = 1; val < 10; val++){			// Checks elements in third dimension
					if(board[row][col][val] == 1){
						rowSingleton(row, col, val);
						colSingleton(row, col, val);
						gridSingleton(row, col, val);

					}
				}
			}
		}
	}
	if(onlyOne()){
		found = 1;
		print();
	}
	findOptions();
	return found;
}

// finds singletons in column
template<typename T>
int Puzzle<T>::colSingleton(int row, int col, int val){
	for(int i = 0; i < 9; i++){
		if(i == row){}
		else if(board[i][col][val]){
			board[row][col][val] = 0;
			board[i][col][val] = 0;
		}
	}
	return 1;
}

// finds singleton in rows
template<typename T>
int Puzzle<T>::rowSingleton(int row, int col, int val){
	for(int i = 0; i < 9; i++){
		if(i == col){}
		else if(board[row][i][val]){
			board[row][col][val] = 0;
			board[row][i][val] = 0;
		}
	}
	return 1;
}

// finds singleton in grid
template<typename T>
int Puzzle<T>::gridSingleton(int row, int col, int val){

	int rowT = row / 3 * 3;
	int rowB = rowT + 2;
	int colL = col / 3 * 3;
	int colR = colL + 2;
	
	for(int i=rowT; i <= rowB; i++){
		for(int j=colL; j <= colR; j++){
			if(i == row && j == col){}
			else if(board[i][j][val]){
				board[row][col][val] = 0;
				board[i][j][val] = 0;
			}
		}
	}
	return 1;
}

// solves sudoku board
template<typename T>
void Puzzle<T>::simulate(){
		cout << endl;
		print();
	while(!win()){
		findOptions();
		if(onlyOne()){}
		else if(singleton()){}
		else
			break;
	}
	cout << endl << "Solved Puzzle:" << endl << endl;
	print();
}







