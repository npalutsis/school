//Author: Nick Palutsis
   // Class: CSE 20211
   // Review 2
   // Date: November 10, 2015
   
#include <stdio.h>
#include <ctype.h>

int main(void){
   char c;
   int i;
   int lTot = 0; // counts total letters
   int wTot = 0; // counts total white space characters
   int cTot = 0; // counts total characters
   int frequency[26]; // frequency of each letter
   char file[50]; // input for file name
   FILE *txt_file;
   
   printf("What is the name of the file you would like to read: ");
   scanf("%s", file);
   txt_file = fopen (file, "r");
 
   for (i = 0; i < 26; i++) //initialize array
      frequency[i] = 0;
 
   while (c != EOF) { //read until end of document
      c = fgetc(txt_file);
      if (c == EOF) 
         break; 
      else if ('a' <= c && c <= 'z'){ //lowercase letters
         frequency[c - 'a']++;
         lTot++;
      }
      else if ('A' <= c && c <= 'Z'){ //uppercase letters
         frequency[c - 'A']++;
         lTot++;
      }
      else if (c == '	' || c == ' ' || c == '\n') //for tab, space, and new line
         wTot++;
      
      cTot++;
   }
   
   for (i = 0; i < 26; i++)
      printf("%c: %d\n", 'A' + i, frequency[i]);
   
   printf("There were %d characters total.\n"
      "There were %d letters total.\n"
      "There were %d white space characters total.\n"
      "The space percentage was %.2lf\%\n", cTot, lTot, wTot, ((double) wTot * 100 / (double) cTot));
   
   return 0;
}
