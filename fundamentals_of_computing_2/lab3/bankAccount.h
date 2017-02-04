#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>

using std::string;

class BankAccount {

	public:

		string getName();
		int getAcctNum();
		void closeAcct();		

	private:

		string name;
		int acctNum;
		int age;
		
};
  
#endif
