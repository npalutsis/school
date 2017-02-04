#include <stdio.h> 

int func1(int); 
void func2(int *); 
int func3(int[], int); 
const int size = 5; 
int main() {   
   int i, a[size], *p = a;   
   
   printf("\nProblem 2:\n");
   for (i = 0; i < size; i++)  a[i] = i*i;   
   func2(a);
   printf("%d\n", func3(a, size));   
   for (i = 0; i < size; i++)  a[i] = func1(i);   
   func2(a);   
   printf("%d\n", func3(a, size));  
   printf("\n"); 
   return 0; 

} 
int func1(int n) {
   int i, s = 0;   
   for (i = 0; i < n; i++)  s += i;   
   return s; 
} 

void func2(int *p) {
   int *q = p;   
   while (p-q < size) {
     printf("%i ", *p);     
      p++;   
   }   
   printf("\n"); 
} 

int func3(int a[], int s) {
   int i, m = 0;   
   for (i = 0; i < s; i++)  m += a[i];
   return m; 
} 
