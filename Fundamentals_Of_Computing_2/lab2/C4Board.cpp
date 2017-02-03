/* Author: Nick Palutsis
   Date: February 2, 2016
   Class: CSE 20212
   Lab 2 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "C4Board.h"
using namespace std;

C4Board::C4Board(){
   numColumns = 7;
   C4Col Board[numColumns];
}
//====================================================
ostream &operator<<(ostream &output, C4Board &boardToDisplay){
   output << endl;
   for (int i = boardToDisplay.Board[0].getMaxDiscs() - 1; i >= 0; i--) {
      if(i == boardToDisplay.Board[0].getMaxDiscs() - 1){
         for(int k = 1; k <= boardToDisplay.numColumns; k++)
            output << " " << k;
         output << endl;
         for(int n = 0; n < boardToDisplay.numColumns; n++)
            output << "==";
         output << "=" << endl;
      }
      for (int j = 0; j < boardToDisplay.numColumns; j++)
         output << "|" << boardToDisplay.Board[j].getDisc(i);
      output << "|" << endl;
   }
   for(int m = 0; m < boardToDisplay.numColumns; m++)
      output << "==";
   output << "=" << endl << endl;
   return(output);
}
//====================================================
void C4Board::play(){
   int move;
   int turn = 0;
   int i;
   int count = 0;
   int quit = 0;
   
   while(1){
      cout<<*this<<endl;
      
      while(1){   // Runs until there is a winner or the board is full
         if(turn % 2 == 0){
            cout << "Player 1, where would you like to add your disc? (Press -1 to quit): ";
            cin >> move;
            if(move == -1){
               cout << endl << "Thank you for playing." << endl << endl;
               quit = 1;
               break;
            }
            else if(Board[move-1].isFull())
               cout << "ERROR: That column is full. Please choose another column." << endl;
            else if(move - 1 < 0 || move - 1 >= numColumns)
               cout << "ERROR: That is not a valid column. Please choose a different one." << endl;
            else
               break;
         }
         
         // Creates a random computer move
         else if(turn % 2 == 1){
            srand(time(NULL));
            move = rand() % numColumns + 1;
            if(Board[move-1].isFull()){}
            else{
               cout << "Player 2 goes in column " << move << endl;
               break;
            }
         }
      }
      
      if(quit)
         break;
         
      // Adds appropriate disc for player
      switch(turn % 2){
         case 0:
            Board[move-1].addDisc('X');
            break;      
         case 1:
            Board[move-1].addDisc('O');
            break;
      }
      
      // Evaluates for any winners
      if(checkWinner('X')){
         cout<<*this<<endl;
         cout << "Congratulations you win!" << endl << endl;
         break;
      }
      else if(checkWinner('O')){
         cout<<*this<<endl;
         cout << "Sorry, Player 2 wins." << endl << "Better luck next time." << endl << endl;
         break;
      }
      // counts if all columns are full
      for(i = 0; i < numColumns; i++){
         if(Board[i].isFull())
            count++;
      }
      
      // Ends game if the board is full and there are no moves left
      if(count == numColumns){
         cout<<*this<<endl;
         cout << "The board is full. You tied." << endl << "Great game." << endl << endl;
         break;
      }
      count = 0;
      turn++;
   }
}
//====================================================

int C4Board::checkWinner(char c){
   int count;
   
   for(int i = 0; i < numColumns; i++){
      for(int j = Board[0].getMaxDiscs() - 1; j >= 0; j--){
         if(Board[i].getDisc(j) == c){
            // test vertical
            if(testVertical(i, j, c))
               return 1;
            // test to the right
            else if(testHorizontal(i, j, c))
               return 1;
            // test diagonal up
            else if(testDiagUp(i, j, c))
               return 1;
            // test diagonal down
            else if(testDiagDown(i, j, c))
               return 1;
         }
      }
   }
   return 0;
}
//====================================================

int C4Board::testVertical(int col, int row, char c){
   int count = 0;
   
   for(int i = row; i < Board[0].getMaxDiscs(); i++){
      if(i >= Board[0].getMaxDiscs())
         return 0;
      else if(Board[col].getDisc(i) == c && count == 3)
         return 1;
      else if(Board[col].getDisc(i) == c)
         count++;
      else
         return 0;
   }
}
//====================================================

int C4Board::testHorizontal(int col, int row, char c){
   int count = 0;
   
   for(int i = col; i < numColumns + 1; i++){
      if(i >= numColumns)
         return 0;
      else if(Board[i].getDisc(row) == c && count == 3)
         return 1;
      else if(Board[i].getDisc(row) == c)
         count++;
      else
         return 0;
   }
}
//====================================================

int C4Board::testDiagUp(int col, int row, char c){
   int count = 0;
   int i = col;
   int j = row;
   
   while(i < numColumns && j < Board[0].getMaxDiscs()){
      if(i >= numColumns || j >= Board[0].getMaxDiscs())
         return 0;
      else if(Board[i].getDisc(j) == c && count == 3)
         return 1;
      else if(Board[i].getDisc(j) == c)
         count++;
      else
         return 0;
      
      i++;
      j++;
   }
}
//====================================================

int C4Board::testDiagDown(int col, int row, char c){
   int count = 0;
   int i = col;
   int j = row;
   
   while(i < numColumns && j < Board[0].getMaxDiscs()){
      if(j < 0 || i >= numColumns)
         return 0;
      else if(Board[i].getDisc(j) == c && count == 3)
         return 1;
      else if(Board[i].getDisc(j) == c)
         count++;
      else
         return 0;
      
      i++;
      j--;
   }
}













