/* Authors: Nick Palutsis
				Henry Long
	Date: February 9, 2016
	CSE 20212
	Lab 3 */

#include <iostream>
#include <string>
#include "package.h"

using namespace std;
// Overloaded constructor
Package::Package(string n, int z, double w, double c){//package constructor
	name = n;//name
	zip = z;//zip
	weight = w;//weight of package
	cpo = c;//cost per ounce
}
// Calculate generic shipping cost
double Package::CalculateCost(){//calculates standard cost of shipping
	double cost;
	makePositive();//makes weight and cpo positive if they're negative
	cost = weight * cpo;//calculation of cost
	return cost;//returns the cost
}
// Ensure weight and cost per ounce are positive values
void Package::makePositive(){//makes values positive
	if(weight < 0)//if weight is less than zero
		weight = 0 - weight;//make weight same abs value, but positive
	if(cpo < 0)//if cost per ounce is negative
		cpo = 0 - cpo;//make same abs value, but positive
}

string Package::getName(){
	return name;//returns name
}
