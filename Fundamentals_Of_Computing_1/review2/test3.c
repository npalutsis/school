#include <stdio.h>
void func(int *, int **);
void disp(int [], int);
int main()
{
int arr[4] = {5,6,7,8};
int *p1 = arr, **p2;
p2 = &p1;
func(p1, p2);
**p2 = 10;
disp(arr, 4);
}
void func(int *p, int **q)
{ *p = 2; (*q)++;
}
void disp(int a[], int size)
{ int i;
for (i=0; i<size; i++)
printf("%d\n", a[i]);
}