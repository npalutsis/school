#include <iostream>
#include <string>
#include "bankAccount.h"

using namespace std;

BankAccount::BankAccount(){}

int BankAccount::getAcctNum(){
	return acctNum;
}

void BankAccount::closeAcct(){
	cout << "ATTENTION: THIS ACCOUNT HAS BEEN TERMINATED" << endl;
	break;
}
