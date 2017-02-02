/* Author: Nick Palutsis 
   Class: CSE 20211
   Lab: 4 */
/* analyzes arrays of the wins and losses for Notre Dame
   football to provide information to the user */

#include <stdio.h>

int wins[] =
   { 6, 8, 6, 8, 5, 5, 6, 6, 8, 7, 4,
     6, 7, 7, 6, 7, 8, 6, 3, 9, 9, 10,
     8, 9, 10, 7, 9, 7, 5, 9, 10, 6, 6,
     3, 6, 7, 6, 6, 8, 7, 7, 8, 7, 9,
     8, 7, 8, 9, 9, 10, 4, 7, 7, 9, 9,
     8, 2, 7, 6, 5, 2, 5, 5, 2, 9, 7,
     9, 8, 7, 8, 10, 8, 8, 11, 10, 8, 9,
     11, 9, 7, 9, 5, 6, 7, 7, 5, 5, 8,
     12, 12, 9, 10, 10, 11, 6, 9, 8, 7, 9,
     5, 9, 5, 10, 5, 6, 9, 10, 3, 7, 6,
     8, 8, 12, 9, 8 };

int losses[] =
   { 3, 1, 2, 0, 3, 4, 1, 0, 1, 0, 1,
     0, 0, 0, 2, 1, 1, 1, 1, 0, 0, 1,
     1, 1, 0, 2, 1, 1, 4, 0, 0, 2, 2,
     5, 3, 1, 2, 2, 1, 2, 2, 0, 2, 1,
     2, 2, 0, 0, 0, 0, 4, 2, 2, 0, 1,
     2, 8, 3, 4, 5, 8, 5, 5, 7, 1, 2,
     0, 2, 2, 2, 1, 2, 3, 0, 2, 3, 3,
     1, 3, 4, 2, 6, 4, 5, 5, 6, 6, 4,
     0, 1, 3, 3, 1, 1, 5, 3, 3, 6, 3,
     7, 3, 6, 3, 7, 6, 3, 3, 9, 6, 6,
     5, 5, 1, 4, 5 };

int main(void){
   int choice;
   int year;
   int numWins;
   int numLosses;
   int i;
   int noyears;
   int years[200];
   
   do{
      noyears = 1;
      /* prompts user for input */
      printf("What would you like to do?\n"
         "   1: Display the record for a given year.\n"
         "   2: Display years with at least \"n\" wins.\n"
         "   3: Display the years with at least \"n\" losses.\n"
         "   4: Exit\n"
         "What is your choice: ");
      scanf("%d", &choice); /* reads input from user */

      switch(choice){
         case 1: /* shows record for given year */
            printf("What year would you like to see the record for: ");
            scanf("%d", &year);
            numWins = wins[year - 1900];
            numLosses = losses[year - 1900];
            printf("The record in %d was %d - %d.\n\n", year, numWins, numLosses);
            break;
         case 2: /* shows the years with 'n' wins */
            printf("Show years with at least how many wins: ");
            scanf("%d", &numWins); /* reads input from user */
            
            printf("Years with at least %d wins:", numWins);
            
            for(i = 0; i < 200; i++){ /* checks wins array for years with 'n' wins */
               if(wins[i] >= numWins){
                  printf(" %d", (i + 1900)); /* add index and 1900 to calculate year */
                  noyears = 0; /* make variable false to show that there is at least one answer */
               }
            }
            
            if(noyears){ /* prints only if no years fit the condition */
               printf(" There are no years with %d wins.", numWins);
            }
            
            printf("\n\n");
            break;
         case 3: /* shows the years with 'n' losses */
            printf("Show years with at least how many losses: ");
            scanf("%d", &numLosses);
            
            printf("Years with at least %d losses:", numLosses);
            
            for(i = 0; i < 200; i++){ /* checks losses array for years with 'n' losses */
               if(losses[i] >= numLosses){
                  printf(" %d", (i + 1900)); /* add index and 1900 to calculate year */
                  noyears = 0; /* make variable false to show that there is at least one answer */
               }
            }
            
            if(noyears){ /* prints only if no years fit  the condition */
               printf(" There are no years with %d losses.", numLosses);
            }
            
            printf("\n\n");
            break;
         case 4:
            break;
         default: /* user did not answer valid input */
            printf("Please enter a valid input.\n\n");
      }
   }while(choice != 4);
   
   printf("Good bye!\n");
   
   return 0;
}
