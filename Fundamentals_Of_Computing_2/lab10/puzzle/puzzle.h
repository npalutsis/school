/* Author: Nick Palutsis
	Date: April 20, 2016
	CSE 20212
	Lab 10 */

#ifndef PUZZLE_H
#define PUZZLE_H
 
#include <vector>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include <set>
#include <map>
using namespace std;
 
//Puzzle class definition
template <typename T>
 
class Puzzle {
    public:
        Puzzle(int = 9); //default constructor   
        void printBoard(); //display sudoku
        auto checkEntryValidity(auto entry, auto rowNum, auto colNum);
        void addEntry(auto entry, auto rowNum, auto colNum);
        void updateSolutions(); //update possible solutions for board
        void singlePossibility(); //adds number to board if there is only one option
        auto isBoardFull(); //checks if board is full
        void sudokuSolver();
   
    private:
        int size; //size of board
        vector<vector <T > > board; //2D vector
        vector<vector<set <T > > > solutions;//2D vector of possible solutions
}; //end class Puzzle
 
 
//Constructor
template <typename T>
Puzzle<T>::Puzzle(int boardSize){
    size = boardSize;
   
    //Fill 2D board with 0's
    vector<T> tmp;
    for(auto k = 0;k < size; k++){
        tmp.push_back(0);
    }
    for(auto l = 0;l < size; l++){
        board.push_back(tmp);
    }
    
    string FILE;
    cout << "Please enter a file name: ";       // reads in a file
    cin >> FILE;    

    ifstream infile;
    infile.open(FILE.c_str());
    if( !infile ) {
        cout << "Error opening file " << FILE << "!" << endl;
        return;
    }
    T temp;

    for(auto i = 0;i < size;i++){
        for(auto j = 0;j < size;j++){
            infile >> temp;
            board[i][j] = temp;
        }  
    }
   
    //Initialize 2D vector of sets of auto
    for(auto j = 0;j < size; j++){
        solutions.push_back(vector<set<T > > (9));
    }
   
}
 
//Print out sudoku board
template <typename T>
void Puzzle<T>::printBoard(){
    auto countR = 0;
    auto countC = 0;
    cout << "    1 2 3   4 5 6   7 8 9\n";      // titles the columns for the board
    cout << "  -------------------------\n";
    for(auto i=0; i < 9; i++){
        cout << i+1 << " | ";
        for(auto j=0; j < 9; j++){
            cout << board[i][j] << " ";
            if(++countR == 3){          // adds dividers every three columns for mini grid
                cout << "| ";
                countR = 0;
            }
        }   
        cout << endl;
        if(++countC == 3){          // adds dividers every three rows for mini grid
            cout << "  -------------------------\n";
            countC = 0;
        }
    }
}
 
 
//Check validity of an entry, ensures correct entries all the way to end of game
template <typename T>
auto Puzzle<T>::checkEntryValidity(auto entry, auto rowNum, auto colNum){
 
    //check if entry is in desinated row and column
    for(auto i = 0;i < size;i++){
            if(entry == board[i][colNum] || entry == board[rowNum][i]){
                //cout << "Entry already present in row/column" << endl;
                return 0;
            }
    }
    //check if entry is in designated minigrid
    int gridSize = 3, gridRow, gridCol, gridTotal;
    //grab top left corner of minigrid that [rowNum][colNum] is in through integer division
    gridRow = rowNum/gridSize;
    gridRow *= gridSize;
    gridCol = colNum/gridSize;
    gridCol *= gridSize;
    //check through from top left corner of minigrid
    for(auto a = gridRow; a < gridRow + 3; a++){
        for(auto b = gridCol; b < gridCol + 3; b++){
            if(entry == board[a][b]){
                //cout << "Entry already present in minigrid" << endl;
                return 0;
            }
        }
    }
    return 1;
}
 
//Add entry into designated spot on board
template <typename T>
void Puzzle<T>::addEntry(auto entry, auto rowNum, auto colNum){
    board[rowNum][colNum] = entry;
}
 
//Updates Solutions
template <typename T>
void Puzzle<T>::updateSolutions(){
    for(auto row = 0;row < 9;row++){
        for(auto col = 0;col < 9;col++){
            if(board[row][col] == 0){ //for 0 spots
                for(auto value = 1;value < size + 1;value++){
                    if(checkEntryValidity(value, row, col)) //if valid, insert to set
                        solutions[row][col].insert(value);
                    else if(solutions[row][col].find(value) != solutions[row][col].end())
                        solutions[row][col].erase(value);
                }
            }
        }
    }
}
 
//Single Possibility
template <typename T>
void Puzzle <T>::singlePossibility(){
    for(auto row = 0;row < 9;row++){
        for(auto col = 0;col < 9;col++){
            if(board[row][col] == 0 ){ //check only squares of value 0
                if(solutions[row][col].size() == 1){
                    auto solution = *solutions[row][col].begin();
                    board[row][col] = solution;
                    for(auto i = 0; i < size; i++){
                            if(solutions[row][i].find(solution) != solutions[row][i].end())
                                solutions[row][i].erase(solution);
                            if(solutions[i][col].find(solution) != solutions[i][col].end())
                                solutions[i][col].erase(solution);
                    }
                }  
            }
        }
    }
}
 
//Checks if sudoku board is full
template <typename T>
auto Puzzle<T>::isBoardFull(){
    for(auto i = 0;i < size;i++){
        for(auto j = 0;j < size;j++){
            if(board[i][j] == 0) //if a spot on the board is = to 0, board is not full, return 0
                return 0;
        }
    }
    return 1; //if no 0's return 1
}
 
 
//3D function
template <typename T>
void Puzzle<T>::sudokuSolver(){
    auto unsolved = 1;
    cout << "Unsolved Board" << endl;
    printBoard();
    while(unsolved){
        updateSolutions();
        singlePossibility();
        updateSolutions(); 
        //printBoard();
        if(isBoardFull()){
            cout << "Solved Board!" << endl;
            unsolved = 0;
            printBoard();
        }
       
    }
}
 
#endif