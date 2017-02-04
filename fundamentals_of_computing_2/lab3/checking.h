#ifndef CHECKING_H
#define CHECKING_H

#include <string>
#include "BankAccount.h"   // include header of base class

using std::string;

class Checking : public BankAccount {

	public:

		Checking();
		virtual void print();
		
	private:

	  double acctBalance;
	  int gold;
	  int silver;
	  int gems;
};
  
#endif
