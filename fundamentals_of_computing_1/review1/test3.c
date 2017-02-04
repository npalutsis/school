#include <stdio.h>

int fun(int, int); //prototype int main() { 

int main(){
   int i, j, n;

   printf("Part A:\n");
   
   for(i=0; i<5; i++) {   
      printf(">");     
      for(j=0; j<i; j++)       
      printf("*");   
      printf("\n"); } 
   
   printf("\nPart B:\n");
   
   for(i=20; i<100; i++) {   
      if(i<50) continue;   
      if(i%9==0) break;   
      printf("%d\n", i); } 
   
   printf("\nPart C:\n");
   
   n = 21; 
   
   do {   
      switch(n%10) {     
         case 1:     
         case 2:     
         case 3:     
            printf("up\n");     
            n++;   
         case 4:     
            printf("jump\n");     
            n *= 2;     
            break;   
         default:     
            printf("down\n");     
            n--;     
            break;   }   
      printf("%d\n", n); 
   } while( n%3 != 0 );
   
   printf("\nPart D:\n");
   
   int a=5, b=6;   
   n = fun(a, b);   
   printf("%d %d %d\n", a, b, n);   
   n = fun(8, 9);   
   printf("%d %d %d\n", a, b, n); }  
   
   int fun(int a, int b) {   
   int n = 7;   
   return (a+b); 
}
