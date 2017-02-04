/* Author: Nick Palutsis
   Date: January 26, 2016
   Class: CSE 20212
   Lab 1 */
// Initializes the columns for the connect 4 board

#include <iostream>
#include "C4Col.h"
using namespace std;

C4Col::C4Col(){
   int i;
   
   numDiscs = 0;
   maxDiscs = 6;
   
   for(i = 0; i < getMaxDiscs(); i++)
      addDisc(' ');
   numDiscs = 0;
}
//====================================================
int C4Col::isFull(void) {
   if(numDiscs == maxDiscs)
      return 1;
   else
      return 0;
}

//====================================================
void C4Col::addDisc(char c) {
   if(isFull()){
      cout << "ERROR: The column is full" << endl;
      return;
   }
   else{
      discs[numDiscs] = c;
      numDiscs++;
   }
}
//====================================================
char C4Col::getDisc(int i){
   if((i < 0 || i >= maxDiscs) && i != ' '){
      cout << "ERROR: Invalid input" << endl;
   }
   return discs[i];
}
//====================================================
int C4Col::getMaxDiscs(void){
   return maxDiscs;
}
//====================================================
void C4Col::setMaxDiscs(int max){
   maxDiscs = max;
}
//====================================================
int C4Col::getNumDiscs(){
   return numDiscs;
}
//====================================================
void C4Col::setNumDiscs(int num){
   numDiscs = num;
}
//====================================================













