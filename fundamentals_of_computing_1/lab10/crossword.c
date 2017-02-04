// Author: Nick Palutsis
   // Date: December 6, 2015
   // Class: CSE 20211
   // Lab: 10
   
// Generate a crossword puzzle and disply the board, solution, and clues to the user

#include <stdio.h>
#include <string.h> 

int enter_words(int, int, char [20][16]);
void swap(int, int, char [20][16], int);
void print_words(char [20][16], int);
void create_clues(int, int, char [20][16], char [20][16], int);
void initialize_solution(int, int, char [15][16], char);
void create_board(int, int, char [15][16], char, char);
void print_board(char [15][16]);
void print_first_word(int, int, char [15][16], char [20][16]);
int place_words(int, int, char [15][16], char [20][16], int, int, int);
int can_place_down(int, int, char [15][16], char [20][16], int, int);
int can_place_across(int, int, char [15][16], char [20][16], int, int);

void print_cstring_array(char **array, size_t len) ;

int main(void){
   int row = 20;
   int col = 16;
   int wcount;
   int i, j;
   char words[row][col];
   char clues[row][col];
   char board[15][16];

// Generate List of words and clues
   printf("What words would you like to add?\n");
   wcount = enter_words(row, col, words);
   swap(row, col, words, wcount);
   
   initialize_solution(15, 15, board, '.');
   
// Create the solution board
   printf("\nSolution:\n\n");   
   print_first_word(15, 15, board, words);
   
   for(i = 1; i < wcount; i++){
      if(!place_words(15, 15, board, words, i, 0, wcount)){
         printf("\n\n *****CANNOT PLACE WORDS*****\n\n");
         return 0;
      }
   }

   print_board(board);
   
// Create blank board
   printf("\nCrossword Puzzle:\n\n");
   create_board(15, 15, board, '.', '#');
   print_board(board);
   
// Print out clues
   printf("\nClues:\n");
   create_clues(row, col, words, clues, wcount);
   print_words(clues, wcount);

   return 0;
}

//**************************************************************
//*************************FUNCTIONS****************************
//**************************************************************

int enter_words(int row, int col, char words[20][16]){
   int i,j;
   
   for(i = 0; i < row; i){
      fgets(words[i], col, stdin);
      for(j = 0; j < col; j++){
         if(words[i][j] >= 'a' && words[i][j] <= 'z')
            words[i][j] = words[i][j] - ('a'-'A');
         else if(words[i][j] >= 'A' && words[i][j] <= 'Z')
            continue;
         else if(words[i][j] == '\n' || words[i][j] == ' ')
            words[i][j] = '\0';
      }
      if(words[i][0] == '.')
         break;
      else
         i++;
   }
   return i;
}
//==============================================================

void swap(int row, int col, char words[20][16], int wcount){
   int i, j, k;
   int sorted = 0;
   int length1, length2;
   char temp1[col];
   char temp2[col];
   
   while(!sorted){
      sorted = 1;
      for(i = 0; i < wcount; i++){
         if(strlen(words[i]) < strlen(words[i+1])){
            sorted = 0;
            for(j = 0; j < col; j++){
               temp1[j] = '\0';
               temp2[j] = '\0';
               temp1[j] = words[i][j];
               temp2[j] = words[i+1][j];
            }
            for(j = 0; j < col; j++){
               words[i][j] = '\0';
               words[i+1][j] = '\0';
               words[i][j] = temp2[j];
               words[i+1][j] = temp1[j];
            }
         }
      }
   }
}
//==============================================================

void print_words(char words[20][16], int count){
   int i;
   
   for(i = 0; i < count; i++)
      printf("    %s\n", words[i]);
}
//==============================================================

void create_clues(int row, int col, char words[20][16], char clues[20][16], int wcount){
   int i;
   
   for(i = 0; i < wcount; i++){
      strcpy(clues[i], words[i]);
      strfry(clues[i]);   
   }
}
//==============================================================

void initialize_solution(int row, int col, char board[15][16], char symb){
   int i, j;
   
   for(i = 0; i < row; i++){
      for(j = 0; j < col; j++){
         board[i][j] = symb;
      }
      board[i][15] = '\n';
   }
}
//==============================================================

void create_board(int row, int col, char board[15][16], char symb1, char symb2){
   int i, j;
   
   for(i = 0; i < row; i++){
      for(j = 0; j < col; j++){
         if(board[i][j] == symb1)
            board[i][j] = symb2;
         else
            board[i][j] = ' ';
      }
   }
}
//==============================================================

void print_board(char board[15][16]){
   int i, j;
   
   for(i = 0; i < 15; i++){
      for(j = 0; j < 16; j++)
         printf("%c", board[i][j]);
   }  
}
//==============================================================

void print_first_word(int row, int col, char board[15][16], char words[20][16]){
   int i;
   int xstart;
   
   xstart = (15 - strlen(words[0])) / 2;
   for(i = xstart; i < (xstart + strlen(words[0])); i++)
      board[7][i] = words[0][i - xstart];
}
//==============================================================

int place_words(int row, int col, char board[15][16], char words[20][16], int y, int x, int wcount){
   int i, j, k;
   
   for(i = 0; i < row; i++){
      for(j = 0; j < col; j++){
         if(can_place_down(i, j, board, words, y, x)){
            for(k = i; k < (strlen(words[y])+i); k++)
               board[k][j] = words[y][x++];
            return 1;
         }
        else if(can_place_across(i, j, board, words, y, x)){
            for(k = j; k < (strlen(words[y])+j); k++)
               board[i][k] = words[y][x++];
            return 1;
         }
      }
   }
   return 0;
}
//==============================================================

int can_place_down(int row, int col, char board[15][16], char words[20][16], int y, int x){
   int i;
   int connection = 0;

   for(i = row; i < (row + strlen(words[y])); i++){
      if(board[i][col] == words[y][i-row])
         connection = 1;
      else if(col != 0 && (board[i][col-1] >= 'A' && board[i][col-1] <= 'z'))
         return 0;
      else if(col != 14 && (board[i][col+1] >= 'A' && board[i][col+1] <= 'z'))
         return 0;
      else if((board[i][col] >= 'A' && board[i][col] <= 'Z') && board[i][col] != words[y][i-row])
         return 0;
   }
   if(connection==1)
      return 1;
   else
      return 0;
}
//==============================================================

int can_place_across(int row, int col, char board[15][16], char words[20][16], int y, int x){
   int i;
   int connection = 0;

   for(i = col; i < (col + strlen(words[y])); i++){
      if(board[row][i] == words[y][i-col])
         connection = 1;
      else if(row != 0 && (board[row-1][i] >= 'A' && board[row-1][i] <= 'z'))
         return 0;
      else if(col != 14 && (board[row+1][i] >= 'A' && board[row+1][i] <= 'z'))
         return 0;
      else if((board[row][i] >= 'A' && board[row][i] <= 'Z') && board[row][i] != words[y][i-col])
         return 0;
   }
   if(connection==1)
      return 1;
   else
      return 0;
}




















   
