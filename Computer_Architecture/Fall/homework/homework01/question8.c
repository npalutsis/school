/* Author: Nick Palutsis
   Date: September 2, 2016
   Class: CSE 30321
   Homework01 Question08 */

#include <stdio.h>

unsigned fib(unsigned n);

int main() {
    // cout << "Fibonacci Number: " << fib(5) << endl;
    printf("Fibonacci Number: %o\n", fib(5));

    return 0;
}

unsigned fib(unsigned n) {
	unsigned *nPtr;
	nPtr = &n;

	printf("Address of %o: %p\n", n, nPtr);

    if (n == 0){
    	return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fib(n - 1) + fib(n - 2);
    }
}