#include <iostream>
#include <string>
#include "bankAccount.h"
#include "checking.h"

using namespace std;

Checking::Checking(){
	
}

void Checking::printf(){
	
	cout << "You have $" << acctBalance << " total loot between:" << endl;
	cout << gold << " gold pieces" << endl;
	cout << silver << " silver pieces" << endl;
	cout << gems << " gems pieces" << endl;
	cout << "Go out and keep plundering!" << endl;
}
