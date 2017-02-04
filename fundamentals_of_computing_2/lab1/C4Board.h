/* Author: Nick Palutsis
   Date: January 26, 2016
   Class: CSE 20212
   Lab 1 */

#ifndef C4BOARD_H
#define C4BOARD_H
#include <iostream>
#include "C4Col.h"

class C4Board {
   public:
      C4Board();
      ~C4Board();
      void display();   // Prints out board
      void play();      // Cycles through turns
   private:
      int numColumns;      // number of column objects to initialize
      C4Col * Board;    // Generates array of column objects to use as board
      int checkWinner(char);     // checks if there is four in a row
      int testVertical(int, int, char); // checks vertically
      int testHorizontal(int, int, char); // checks horizontally
      int testDiagUp(int, int, char);  // checks diagonally
      int testDiagDown(int, int, char);   // checks diagonally
};

#endif
