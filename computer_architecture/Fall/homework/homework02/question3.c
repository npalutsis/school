#include <stdio.h>

int logicfcn( int i ) {
	int j = i >> 4;
	unsigned int u = j & 255;
	printf("%hhx\n", u);
	printf("%hhu\n", u);
}

int main() {
	int i = 43981;
	logicfcn(i);
}