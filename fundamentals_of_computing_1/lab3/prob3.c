/* Author: Nick Palutsis */

#include <stdio.h>

int main(void)
{
   int op; /* to choose mathematical operator */
   double x; /* first number */
   double y; /* second number */
   double answer; /* answer after computation */
   int div; /* to choose type of division */
   int r; /* remainder */
   int xint; /* for remainder division */
   int yint; /* for remainder division */
   
   do{
      printf("\nWhat would you like to do?\n" /* prompts user for mathematical operator */
         "   1 for addition\n"
         "   2 for subtraction\n"
         "   3 for multiplication\n"
         "   4 for division\n"
         "   5 to exit\n"
         "What is your choice: ");
      scanf("%d", &op); /* reads user input */
      
      if(op == 1 || op == 2 || op == 3 || op == 4) /* if valid input */
      {
         printf("\nEnter the first number: "); 
         scanf("%lf", &x); /* reads first number input from user */
         printf("Enter the second number: ");
         scanf("%lf", &y); /* reads second number input from user */
      
         switch(op){ /* chooses mathematical sequence */
            case 1: /* if addition */
               answer = x + y; /* calculates answer */
               printf("\n(%.2lf) + (%.2lf) = %.2lf\n", x, y, answer);
               break; /* breaks from switch structure */
            case 2: /* if subtraction */
               answer = x - y; /* calculates answer */
               printf("\n(%.2lf) - (%.2lf) = %.2lf\n", x, y, answer);
               break; /* breaks from switch structure */
            case 3: /* if multiplication */
               answer = x * y; /* calculates answer */
               printf("\n(%.2lf) * (%.2lf) = %.2lf\n", x, y, answer);
               break; /* breaks from case structure */
            case 4: /* if division */
               printf("\nWhat would you like to do?\n" /* prompts user for if they would like a remainder */
                  "   1 show the remainder\n"
                  "   2 calculate the exact value\n"
                  "What is your choice: ");
               scanf("%d", &div); /* reads user input */
               
               switch(div){
                  case 1: /* if remainder */
                     xint = x; /* converts x from a double to an int value */
                     yint = y; /* converts y from a double to an int value */
                     answer = x / y; /* calculates exact answer */
                     r = xint % yint; /* calculates remainder */
                     printf("\n(%.2lf) / (%.2lf) = %.0lf with a remainder of %d\n", x, y, answer, r); /* converts answer to whole number and displays calculations */
                     break; /* breaks from case structure */
                  case 2: /* if exact solution */
                     answer = x / y; /* calculates answer */
                     printf("\n(%.2lf) / (%.2lf) = %.2lf\n", x, y, answer);
                     break; /* breaks from case structure */
                  default: /* displays if the user inputed a value other than 1 or 2 */
                     printf("\nInvalid menu input.\n");
                     break; /* breaks from case structure */
                  }
                  break; /* breaks from case structure */
               default:
                  printf("\nInvalid menu input.\n");
                  break;
         }
      }
      else if(op != 5) /* displays if user enters value other than the desired inputs */
      {
         printf("\nInvalid menu input.\n");
      }
   }while(op != 5); /* exits while loop if op = 5; otherwise repeats */
   
   printf("\nThank you!\n\n");
   
   return 0; /* signifies end of successful program run */
}
