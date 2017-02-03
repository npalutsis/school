#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>

using namespace std;

class BankAccount {

	public:
		
		BankAccount();
		BankAccount(string, int, int);
		string getName();
		int getAcctNum();
		void closeAcct();		

	protected:

		string name;
		int acctNum;
		int age;
		
};
  
#endif
