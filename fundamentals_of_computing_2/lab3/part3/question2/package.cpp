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
Package::Package(string n, int z, double w, double c){
	name = n;
	zip = z;
	weight = w;
	cpo = c;
}
// Calculate generic shipping cost
double Package::CalculateCost(){
	double cost;
	makePositive();
	cost = weight * cpo;
	return cost;
}
// Ensure weight and cost per ounce are positive values
void Package::makePositive(){
	if(weight < 0)
		weight = 0 - weight;
	if(cpo < 0)
		cpo = 0 - cpo;
}

string Package::getName(){
	return name;
}
