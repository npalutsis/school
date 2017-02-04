/* Authors: Nick Palutsis
				Henry Long
	Date: February 9, 2016
	CSE 20212
	Lab 3 */

#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>

using std::string;

class Package {

	public:
		Package(string, int, double, double);//constructor with inputs for weight and cost per ounce and name and zip
		virtual double CalculateCost();//function that calculates base cost of shipping
		void makePositive();//makes any negative value positive
		string getName();//returns name

	private:
		string name;
		int zip;

	protected:
		double weight;
		double cpo; 	// cost per ounce
};

#endif
