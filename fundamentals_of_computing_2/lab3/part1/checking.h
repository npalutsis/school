#ifndef CHECKING_H
#define CHECKING_H

#include <string>
#include "bankAccount.h"   // include header of base class

using namespace std;

class Checking : public BankAccount {//class that inherits class BankAccount

	public:

		Checking(string, int, int, int, int, int);//constructor
		virtual void print();//print function

	private:

	  double acctBalance;//private variables with acct information
	  int gold;
	  int silver;
	  int gems;
};

#endif
