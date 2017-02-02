/* Author: Nick Palutsis
   Date: September 2, 2016
   Class: CSE 30321
   Homework03 Question04 */

#include <stdio.h>

int signext(int n, unsigned s);

int main(void) {
	printf("0x%08x\n", signext(0x8f, 8));
	printf("0x%08x\n", signext(0x18f, 12)); 
	printf("0x%08x\n", signext(0x8f, 9)); 
	printf("0x%08x\n", signext(0xabcd, 16));
	return 0;
}

int signext(int n, unsigned s) {
	if (n >> (s - 1) == 1)
		n = (0xffffffff << s) | n;
	return n;
}