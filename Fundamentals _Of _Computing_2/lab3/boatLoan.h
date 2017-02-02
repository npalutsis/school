#ifndef BOATLOAN_H
#define BOATLOAN_H

#include <string>
#include "BankAccount.h"   // include header of base class

using std::string;

class BoatLoan : public BankAccount {

	public:

		BoatLoan();
		virtual void print();
		
	private:

		double maxLootStorage;
		int numCannons;
		int monthsLeft;
};
  
#endif
