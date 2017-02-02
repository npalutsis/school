/* Author: Nick Palutsis
   Date: September 2, 2016
   Class: CSE 30321
   Homework01 Question02 */

#include <stdio.h>

void printbin(char n);

int main(void) {
	printbin(-128);
	printbin(-65);
	printbin(-5);
	printbin(-1);
	printbin(0);
	printbin(1);
	printbin(5);
	printbin(65);
	printbin(127);
}

void printbin(char n) {
	int c, k;

	for (c = 7; c >= 0; c--) {
		k = n >> c;
		if (k & 1)
			printf("1");
		else
			printf("0");
	}
	printf("\n");
}