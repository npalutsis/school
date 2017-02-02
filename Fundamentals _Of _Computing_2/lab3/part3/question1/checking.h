#ifndef CHECKING_H
#define CHECKING_H

#include <string>
#include "bankAccount.h"   // include header of base class

using namespace std;

class Checking{

	public:
		Checking(string, int, int, int, int, int);
		virtual void print();
		
	private:
	  double acctBalance;
	  int gold;
	  int silver;
	  int gems;
};
  
#endif
