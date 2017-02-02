#include <iostream>
#include <string>
#include "bankAccount.h"
#include "boatLoan.h"

using namespace std;

BoatLoan::BoatLoan(){
	
}

void BoatLoan::printf(){
	
	cout << "You only have " << monthsLeft << " until this brigantine is yours!" << endl;
	cout << "You only have " << numCannons << ", don't stop arming your ship!" << endl;
	cout << "You have " << maxLootStorage << "sqft in the hull to fill up." << endl;
}
