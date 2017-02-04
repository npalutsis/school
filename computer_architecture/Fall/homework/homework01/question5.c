/* Author: Nick Palutsis
   Date: September 2, 2016
   Class: CSE 30321
   Homework01 Question05 */

#include <stdio.h>

int concat(short m, short n);

int main(void) {	
	int num = concat(0x1234, 0x5678);
	printf("concat(0x1234, 0x5678) -> 0x%08x\n", num);
	num = concat(0xabcd, 0x1234);
	printf("concat(0xabcd, 0x1234) -> 0x%08x\n", num);
	num = concat(0x3104, 0x1134);
	printf("concat(0x3104, 0x1134) -> 0x%08x\n", num);
	num = concat(0x3476, 0x5279);
	printf("concat(0x3476, 0x5279) -> 0x%08x\n", num);

	return 0;
}

int concat(short m, short n) {
	int num = (0x00000000 << 16) | m;
	num = (num << 16) | n;
	return num;
}