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
	double weight, costPerOunce;//initialize variables that user will input
	cout << "Who will the package be delivered to: ";//prompt user
	cin >> name;//record input
	cout << "What zip code is the package being shipped to: ";//prompt user
	cin >> zip;//record input
	cout << "What is the weight of the package: ";//prompt user
	cin >> weight;//record input
	cout << "What is the cost per ounce to ship: ";//prompt user
	cin >> costPerOunce;//record input

	TwoDayPackage package1(name, zip, weight, costPerOunce, 4.75);//initialize object of a class
	package1.print();//print output of object 1
	OvernightPackage package2(name, zip, weight, costPerOunce, .33);//initialize object of another class
	package2.print();//print output of object 2
}
