/* Authors: Nick Palutsis
				Henry Long
	Date: February 9, 2016
	CSE 20212
	Lab 3 */

#include <iostream>
#include <string>
#include "package.h"
#include "OvernightPackage.h"

using namespace std;
// Overloaded constructor
OvernightPackage::OvernightPackage(string n, int z, double w, double c, double e):Package(n, z, w, c){//constructor wit hinputs that includes inputs of parent class constructor to include those values
	extraCostPerOunce = e;//set e to the extra cost
	cost = CalculateCost();
}
// Calculate shipping cost for overnight shipping with an extra cost per ounce
double OvernightPackage::CalculateCost(){
	makePositive();
	cost = weight * (cpo + extraCostPerOunce);//calculates new cost by calling the function with the new cpo
	return cost;//returns cost
}

void OvernightPackage::print(){
		cout << "The cost to ship the package overnight to " << getName() << " is $" << cost << endl;//prints cost
}
