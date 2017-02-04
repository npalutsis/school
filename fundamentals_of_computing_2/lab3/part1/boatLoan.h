#ifndef BOATLOAN_H
#define BOATLOAN_H

#include <string>
#include "bankAccount.h"   // include header of base class

using namespace std;

class BoatLoan : public BankAccount {//boatLoan class inherits parent function

	public:

		BoatLoan(string, int, int, int, int, int);//constructor
		virtual void print();//print function

	private:

		double maxLootStorage;//private variables with boatLoan info
		int numCannons;
		int monthsLeft;
};

#endif
