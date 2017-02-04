#include <iostream>
#include <string>
#include "bankAccount.h"

using namespace std;

BankAccount::BankAccount(){}

BankAccount::BankAccount(string x, int y, int z){
	name = x;
	acctNum = y;
	age = z;
}

int BankAccount::getAcctNum(){
	return acctNum;
}

string BankAccount::getName(){
	return name;
}

void BankAccount::closeAcct(){
	cout << "ATTENTION: THIS ACCOUNT HAS BEEN TERMINATED" << endl;
	//break;
}
