#include <iostream>
#include "checking.h"
#include "boatLoan.h"

using namespace std;

int main(){
	BoatLoan boat1("john doe", 123456789, 50, 1000, 20, 24);//all info need for initialization of an object in the class
	Checking checking1("john doe", 123456789, 50, 25, 37, 17);//all info needed for initialization of an object in the class
	boat1.print();//prints output of object 1
	checking1.print();//prints output of object2
}
