#include <stdio.h>
#include <stdlib.h>

int A;
int B = 0;
int array1[1024];

void func1() {
	int func1_0, func1_1, func1_2;
	printf("&func1_0          %018p\n", &func1_0);
	printf("&func1_1          %018p\n", &func1_1);
	printf("&func1_2          %018p\n", &func1_2);
}

void func2(int func2_0, int func2_1, int func2_2) {
	printf("&func2_0          %018p\n", &func2_0);
	printf("&func2_1          %018p\n", &func2_1);
	printf("&func2_2          %018p\n", &func2_2);
}

int main() {
	char C;
	int D = 0;
	char array2[1024];
	long array3[1024];
	short array4[1024];
	func1();
	int E, F, G;
	func2(E, F, G);
	char *allocated = (char *)malloc(1024);
	// Print addresses of global variables
	printf("&A                %018p\n", &A);
	printf("&B                %018p\n", &B);
	printf("array1            %018p\n", array1);
	printf("array1            %lu\n", sizeof(array1));
	// Print addresses of local variables
	printf("&C                %018p\n", &C);
	printf("&D                %018p\n", &D);
	printf("array2            %018p\n", array2);
	printf("array2            %lu\n", sizeof(array2));
	printf("array3            %018p\n", array3);
	printf("array3            %lu\n", sizeof(array3));
	printf("array4            %018p\n", array4);
	printf("array4            %lu\n", sizeof(array4));
	printf("&E                %018p\n", &E);
	printf("&F                %018p\n", &F);
	printf("&G                %018p\n", &G);
	// Print addresses of dynamically allocated memory blocks
	printf("allocated         %018p\n", allocated);
	// Print addresses of functions (function pointers)
	printf("func1             %018p\n", func1);
	printf("func2             %018p\n", func2);
	printf("main              %018p\n", main);
}