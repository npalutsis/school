#include <iostream>
#include <string>
#include "bankAccount.h"
#include "checking.h"

using namespace std;

Checking::Checking(string name1, int acctNum1, int age1, int x, int y, int z):BankAccount(name1, acctNum1, age1){//constuctor including info from its parent class
	gold = x;//set variables to values
	silver = y;
	gems = z;
	acctBalance = gold * 10 + silver * 5 + gems * 1;//calculation of total balance
}

void Checking::print(){//print function that prints checking acct info

	cout << endl << "You have $" << acctBalance << " total loot between:" << endl;
	cout << "   " << gold << " gold pieces" << endl;
	cout << "   " << silver << " silver pieces" << endl;
	cout << "   " << gems << " gems pieces" << endl;
	cout << "Go out and keep plundering!" << endl;
}
