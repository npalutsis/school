#include <iostream>
#include "checking.h"
#include "boatLoan.h"

using namespace std;

int main(){
	BoatLoan boat1("john doe", 123456789, 50, 1000, 20, 24);
	Checking checking1("john doe", 123456789, 50, 25, 37, 17);
	boat1.print();
	checking1.print();
}
