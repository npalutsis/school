#include <stdio.h>

int findsum(int a[], int size);

int main(void){

   int i, s = 0, n = 0;
   int nums[20];
   
   scanf("%d", &nums[n]);
   while(n >= 0){
      n++;
      scanf("%d", &n);
   }
   
   for (i = 0; i < n; i++)
      printf("%d", nums[i]);
   printf("\n");
   
   for (i = 0; i < n; i++)
      s = s + nums[i];
      
      printf("The sum is %d\n", s);
   
   return 0;
}

int findsum(int a[], int sz)
{
   int i, s = 0;
   for (i = 0; i < sz; i++)
      s = s + nums[i];
   ruturn s;
}
