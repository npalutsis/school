/* Author: Nick Palutsis
   Date: January 26, 2016
   Class: CSE 20212
   Lab 1 */
// Prototypes to initiate columns

#ifndef C4COL_H
#define C4COL_H
#include <iostream>

class C4Col {
   public:
      C4Col();
      int isFull();        // determines if column is full
      char getDisc(int);    // returns requested element of character array
      void addDisc(char);  // adds disc character to array
   int getMaxDiscs();      // returns number of rows
      void setMaxDiscs(int);  // set maximum rows
      int getNumDiscs();      // return number of discs per column
      void setNumDiscs(int);  // set the number of discs in a column
   private:
      int numDiscs;
      int maxDiscs;
      char discs[6];
};

#endif
