/* Authors: Nick Palutsis
				Henry Long
	Date: February 9, 2016
	CSE 20212
	Lab 3 */

#include <iostream>
#include "TwoDayPackage.h"
#include "OvernightPackage.h"

using namespace std;

int main(){
	string name;
	int zip;
	double weight, costPerOunce;
	TwoDayPackage p1("Henry", 50312, 4, 3, 4.75), p2("Nick", 46556, 6, 5, 3.75), p3("Jake", 67584, 12, .1, 2.75);
	OvernightPackage op1("Colin", 40392, 16, .4, .33), op2("John", 86754, 40, .05, 1.00), op3("Bill", 00030, 20, .4, .3);

	Package *todaysPackage[] = {&p1, &p2, &p3, &op1, &op2, &op3};
	double sum=0.0;
	for (int i=0; i<6;i++){
		sum+= todaysPackage[i]->CalculateCost();
	}
	cout<<"The total cost to ship today's orders is: $"<<sum<<endl; //print result
}
