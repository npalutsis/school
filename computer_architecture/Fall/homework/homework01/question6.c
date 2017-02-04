/* Author: Nick Palutsis
   Date: September 2, 2016
   Class: CSE 30321
   Homework01 Question06 */

#include <stdio.h>

void sumElements(int array[], int n, int *sumPtr);

int main(void){
	int myArray[] = {17, -3, 8, 49, -5, 56, 100, -22};
	int sum = 0;
	int *sumPtr = &sum;

	sumElements(myArray, 4, sumPtr);
	// cout << "The sum of the first 4 elements is: " << *sumPtr << endl;
	printf("The sum of the first 4 elements is: %d\n", *sumPtr);

	*sumPtr = 0;

	sumElements(myArray, 6, sumPtr);
	// cout << "The sum of the first 6 elements is: " << *sumPtr << endl;
	printf("The sum of the first 6 elements is: %d\n", *sumPtr);

	return 0;
}

void sumElements(int array[], int n, int *sumPtr){
	for(int i = 0; i < n; i++){
		*sumPtr += array[i];
	}
}