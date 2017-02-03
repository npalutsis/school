/* Authors: Nick Palutsis
				Henry Long
	Date: February 9, 2016
	CSE 20212
	Lab 3 */

#ifndef OVERNIGHT_PACKAGE_H
#define OVERNIGHT_PACKAGE_H

#include <string>
#include "package.h"   // include header of base class

using namespace std;

class OvernightPackage : public Package {//include parent class Package in new class OvernightPackage

	public:
		OvernightPackage(string, int, double, double, double);//constructor with three inputs (weight, cost per ounce, extra cost per ounce)
		double CalculateCost();//uses virtual function from parent class
		virtual void print();//print statement function

	private:
		double cost;//new cost
		double extraCostPerOunce;//variable that adds to the new cost
};

#endif
