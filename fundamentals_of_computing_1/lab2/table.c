 /*Author: Nick Palutsis*/

#include <stdio.h>

int main(void) {

   int X;
   int Y;
   int i;
   int ix;
   int iy;
   int n;
   
   printf("How wide would you like the table?: \n"); /* prompt user for input */
   scanf("%d", &X); /*read value for width of table*/

   printf("How tall would you like the table?: \n"); /* prompt user for input */
   scanf("%d", &Y); /*read value for height of table*/
   
   int x[X]; /* array of numbers to multiply by on top */
   int y[Y]; /* array of numbers to multiply by along side */
   
   printf("     *"); /* signify a blank space in corner of table */
   
   for(i = 1; i <= X; i++) { /* prints first row of numbers to multiply by on top */
      x[i] = i;
      printf("%6d", x[i]);
   }
   printf("\n");
   
   for(iy = 1; iy <= Y; iy++) {
      y[iy] = iy;
      printf("%6d", y[iy]); /* prints numbers along side of table to multiply by */
      for(ix = 1; ix <= X; ix++) {
         n = y[iy] * x[ix]; /* multiplies top and side numbers together */
         printf("%6d", n); /* prints output of multiplication */
      }
      printf("\n"); /* goes to next row */
   }
   
   return 0; /* signifies end of successful run */
}
