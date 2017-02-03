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

class OvernightPackage : public Package {

	public:
		OvernightPackage(string, int, double, double, double);
		virtual double CalculateCost();
		virtual void print();
		
	private:
		double cost;
		double extraCostPerOunce;
};
  
#endif
