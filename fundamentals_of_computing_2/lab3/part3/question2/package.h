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
		Package(string, int, double, double);
		virtual double CalculateCost();
		void makePositive();
		string getName();

	private:
		string name;
		int zip;
		
	protected:
		double weight;
		double cpo; 	// cost per ounce	
};
  
#endif
