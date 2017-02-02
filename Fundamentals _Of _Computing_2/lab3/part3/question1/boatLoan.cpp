#include <iostream>
#include <string>
#include "bankAccount.h"
#include "boatLoan.h"

using namespace std;

BoatLoan::BoatLoan(string name2, int acctNum2, int age2, int x, int y, int z){
	BankAccount account(name2, acctNum2, age2);
	maxLootStorage = x;
	numCannons = y;
	monthsLeft = z;
}

void BoatLoan::print(){
	
	cout << endl << "You only have " << monthsLeft << " until this brigantine is yours!" << endl;
	cout << "You only have " << numCannons << ", don't stop arming your ship!" << endl;
	cout << "You have " << maxLootStorage << "sqft in the hull to fill up." << endl;
}
