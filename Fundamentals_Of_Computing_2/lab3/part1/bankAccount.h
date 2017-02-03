#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>

using namespace std;

class BankAccount {//parent class

	public:

		BankAccount();//constructor
		BankAccount(string name = "john doe", int acctNum = 123456789, int age = 50);//constructor
		string getName();//gets name
		int getAcctNum();//gets acct number
		void closeAcct();	//closes the account

	private:

		string name;//private information of account holders
		int acctNum;
		int age;

};

#endif
