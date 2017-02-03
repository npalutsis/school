#include <iostream>
#include <string>
#include "bankAccount.h"
#include "checking.h"

using namespace std;

Checking::Checking(string name1, int acctNum1, int age1, int x, int y, int z){
	BankAccount account(name1, acctNum1, age1);
	gold = x;
	silver = y;
	gems = z;
	acctBalance = gold * 10 + silver * 5 + gems * 1;
}

void Checking::print(){
	
	cout << endl << "You have $" << acctBalance << " total loot between:" << endl;
	cout << "   " << gold << " gold pieces" << endl;
	cout << "   " << silver << " silver pieces" << endl;
	cout << "   " << gems << " gems pieces" << endl;
	cout << "Go out and keep plundering!" << endl;
}
