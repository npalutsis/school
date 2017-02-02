/* Author: Nick Palutsis
   Date: September 2, 2016
   Class: CSE 30321
   Homework03 Question03 */

#include <stdio.h>

unsigned bitrange(unsigned inst, unsigned hi, unsigned lo);

int main(void) {
	unsigned inst;
	inst = 0xabcd1234;
	bitrange(inst, 3, 0);
	bitrange(inst, 31, 28);
	bitrange(inst, 27, 4);
	bitrange(0x9eba23cc, 5, 23);
	bitrange(0x216c1e0, 21, 6);

	return 0;
}

unsigned bitrange(unsigned inst, unsigned hi, unsigned lo) {
	unsigned original = inst;

	inst = inst << (31 - hi);
	inst = inst >>(31 - hi + lo);

	printf("bitrange(0x%x, %u, %u)\t==\t0x%x\n", original, hi, lo, inst);
	return 0;
}