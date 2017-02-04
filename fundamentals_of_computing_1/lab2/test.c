#include <stdio.h>

int main(void) {
   int X;
   int i;
   
   X = 4;
   int n[X];
   for(i = 1; i <= 4; i++) {
      n[i] = i;
   }
   printf("%d", n);
   return 0;
}
