#include <iostream>
#include <string>
#include "bankAccount.h"

using namespace std;

BankAccount::BankAccount(string x, int y, int z){//constructor
	name = x;//setting inputs equal to variable names
	acctNum = y;
	age = z;
}

int BankAccount::getAcctNum(){//returns acct number
	return acctNum;
}

string BankAccount::getName(){//returns name
	return name;
}

void BankAccount::closeAcct(){
	cout << "ATTENTION: THIS ACCOUNT HAS BEEN TERMINATED" << endl;
	//break;
}
