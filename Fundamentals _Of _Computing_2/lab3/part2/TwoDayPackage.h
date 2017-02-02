/* Authors: Nick Palutsis
				Henry Long
	Date: February 9, 2016
	CSE 20212
	Lab 3 */

#ifndef TWO_DAY_PACKAGE_H
#define TWO_DAY_PACKAGE_H

#include <string>
#include "package.h"   // include header of base class

using namespace std;

class TwoDayPackage : public Package {//class inherits Package, a parent package

	public:
		TwoDayPackage(string, int, double, double, double);//constructor with inputs (name, zip, weight, cost per ounce, fixed cost)
		double CalculateCost();//takes virtual function from parent class
		virtual void print();

	private:
		double cost;//new cost variable for this class
};

#endif
