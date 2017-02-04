
/* Author: Nick Palutsis
   Class: CSE 20211
   Lab 6
   Date: October 15, 2015 */
// Asks user for a startup file and then gives options to display the strings from that file

#include <stdio.h>
#include <string.h>

void print_all(char sayings[100][80], int count);
int enter_new_saying(char sayings[100][80], int count);
void find_word(char sayings[100][80], int count);
void save_saying(char sayings[100][80], int count);

int main(void){
   int i;
   int count = 0;
   int choice;
   char word[80];
   char sayings[100][80];
   char filename[50];
   FILE *txtfile;

   printf("Enter the name of the startup file: ");
   scanf("%s", filename);
   txtfile = fopen (filename, "r");
   if(!txtfile){  //checks to see if file exists
      printf("Error opening the file %s.\n", filename);
      return 1;
   }
   
   //puts sayings from file in array of strings
   for(i = 0; i < 100; i++){
      fgets(sayings[i], 80, txtfile);
      if(strlen(sayings[i]) <= 0)
         break;
      else
         count++;
   }
   
   while(choice != 5){
      printf("What would you like to do?\n"
         "   1: Display all strings in database\n"
         "   2: Add a new string to the database\n"
         "   3: List sayings containing a specific word\n"
         "   4: Save all sayings to a new text file\n"
         "   5: Quit\n"
         "Enter your choice: ");
      scanf("%d", &choice);
   
      switch(choice){
         case 1: //prints all strings
            print_all(sayings, count);
            break;
         case 2: //adds a new saying to end of the list
            count = enter_new_saying(sayings, count);
            break;
         case 3: //searches for sayings with exact words entered
            find_word(sayings, count);
            break;
         case 4: //saves the array of strings in a new file
            save_saying(sayings, count);
            break;
         case 5: //quits
            break;
         default:
            printf("Your choice is invalid. Please enter the number of a valid option.\n");
            break;
      }
   }
   
   return 0;
}


//prints all strings
void print_all(char sayings[100][80], int count){
   int i;
   for(i = 0; i < count; i++)
      printf("%3d -> %s", i + 1, sayings[i]);
}

//adds a new saying to the end of the list
int enter_new_saying(char sayings[100][80], int count){
   printf("What saying would you like to add?\n");
   getchar();
   fgets(sayings[count], 80, stdin);
   count++;
   return count;
}

//searches array for saying with exact words
   //strcasestr() would result in a "segmentation fault (core dumped)"
   //strstr() was used instead
void find_word(char sayings[100][80], int count){
   int i;
   int found = 0;
   char word[80];
   
   printf("What word would you like to look for?\n");
   getchar();
   fgets(word, 80, stdin);
   strtok(word, "\n"); //removes '\n' from string
   for(i = 0; i < count; i++){
      if(strstr(sayings[i], word) != NULL){
         printf("%3d -> %s", i + 1, strstr(sayings[i], word)); //strcasestr() didn't work
         found = 1;
      }
   }
   if(found == 0)
      printf("Sorry, no sayings contain the word \"%s\".\n", word);
}

//prints the array in a new file and saves it in the current directory
void save_saying(char sayings[100][80], int count){
   int i;
   char newfile[50];
   FILE *fp;
   
   printf("What would you like to name the new file?\n");
   scanf("%s", newfile);
   fp = fopen(newfile, "w+");
   for(i = 0; i < count; i++)
      fprintf(fp, "%3d -> %s", i + 1, sayings[i]);
}
