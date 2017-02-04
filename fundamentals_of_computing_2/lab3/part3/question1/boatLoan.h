#ifndef BOATLOAN_H
#define BOATLOAN_H

#include <string>
#include "bankAccount.h"   // include header of base class

using namespace std;

class BoatLoan{
	
	public:
		BoatLoan(string, int, int, int, int, int);
		virtual void print();
		
	private:
		double maxLootStorage;
		int numCannons;
		int monthsLeft;
};
  
#endif
