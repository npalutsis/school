/* Authors: Nick Palutsis
				Henry Long
	Date: February 9, 2016
	CSE 20212
	Lab 3 */

#include <iostream>
#include <string>
#include "package.h"
#include "TwoDayPackage.h"

using namespace std;
// Overloaded constructor
TwoDayPackage::TwoDayPackage(string n, int z, double w, double c, double f):Package(n, z, w, c){
	double fixedCost = f;
	cost = fixedCost + CalculateCost();
}
// Calculate shipping cost for 2 day shipping with a fixed cost
double TwoDayPackage::CalculateCost(){
	makePositive();
	cost = weight * cpo;
	return cost;
}

void TwoDayPackage::print(){
		cout << "The cost to ship the package with two day shipping to " << getName() << " is $" << cost << endl;
}
