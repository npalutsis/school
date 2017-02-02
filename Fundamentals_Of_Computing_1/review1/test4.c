#include <stdio.h> 
#define SIZE 5  
void disp(int[], int); 
int ok(int[], int); 
void fn(int[], int);  

int main() {   

   int i, a[SIZE];  
   
   for (i = 0; i < SIZE; i++)    
      a[i] = i*i+1;   
   disp(a, SIZE);   
   printf("%d\n", ok(a, SIZE));   
   fn(a, SIZE);   
   disp(a, SIZE);   
   fn(a, SIZE);   
   disp(a, SIZE); 
}  

void disp(int a[], int s) {   int i;   for (i = 0; i < s; i++)     printf("%i ", a[i]);   printf("\n"); }  

int ok(int a[], int s) {   int i, m = 0;   for (i = 0; i < s; i++)     m += a[i];   return m; }  

void fn(int a[], int s) {   int i, z = a[0];   for (i = 0; i < s-1; i++)     a[i] = a[i+1];   a[s-1] = z; } 
 
