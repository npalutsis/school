#include <stdio.h> 

int main(void){
   int x[4];
   int i;
   
   for(i = 0; i < 4; i++){
      x[i] = i;
      printf("%d\n", x[i]);
   }
   
   return 0;
}
