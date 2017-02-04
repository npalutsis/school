// Author: Nick Palutsis
   // Date: January 20, 2015
   // Prelab
   // CSE 20212
   
#include <iostream>
#include "mortgage.h" // Declare mortgage class

 using namespace std;
 
int main () {
   
   double principal, rate, payment;

   // Retrieve inputs from user; Errors for invalid inputs
   cout << "What is the amount of the mortgage: ";
   cin >> principal;
   if(principal <= 0){
      cout << "Error: Invalid mortgage amount" << endl;
      return 0;
   }
   cout << "What is the rate: ";
   cin >> rate;
   if(rate <= 0){
      cout << "Error: Invalid rate value" << endl;
      return 0;
   }
   cout << "What is the size of each monthly payment: ";
   cin >> payment;
   if(payment <= rate * principal / 12 / 100){
      cout << "Error: Invalid payment amount" << endl;
      return 0;
   }

   Mortgage first (principal, rate, payment); // uses non-default initialization
   Mortgage second; // uses default constructor

   second.credit(10000);
   
   cout << "Current balance after crediting second mortgage 10K: " <<
   second.getPrincipal() << endl;
   cout << "Amortization schedule for first mortgage:" << endl;   // Print amortization table
   first.amortize();

}
