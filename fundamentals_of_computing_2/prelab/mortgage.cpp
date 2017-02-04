// Author: Nick Palutsis
   // Date: January 20, 2015
   // Prelab
   // CSE 20212
   
#include <iostream>
#include <iomanip> // for setw() and setprecision()
#include "mortgage.h"

using namespace std;

Mortgage::Mortgage(double x, double y, double z){     // Constructor
   setPrincipal(x);
   setRate(y);
   setPayment(z);
}
Mortgage::Mortgage(){      // Default Constructor
   setPrincipal(100000);
   setRate(5.0);
   setPayment(500.00);
}

// Set Functions
void Mortgage::setPrincipal(double x){
   principal = x;
}
void Mortgage::setRate(double x){
   rate = x / 100;
}
void Mortgage::setPayment(double x){
   payment = x;
}
void Mortgage::setInterest(double rate, double balance){
   interest = rate * balance / 12;
}

// Get Functions
double Mortgage::getPrincipal(){
   return principal;
}
double Mortgage::getRate(){
   return rate;
}
double Mortgage::getPayment(){
   return payment;
}
double Mortgage::getInterest(){
   return interest;
}

void Mortgage::amortize(){
   int month = 0;
   cout << "Month    Payment    Interest    Balance" << endl;
   while(getPrincipal() > 0){
     setInterest(getRate(), getPrincipal());
     setPrincipal(getPrincipal() + getInterest());
     
     if(getPrincipal() <= getPayment()){
     setPayment(getPrincipal());
     }
     
     setPrincipal(getPrincipal() - getPayment());
     month++;
   
   cout << setprecision(2) << fixed;
   cout << left << setw(9) << month 
      << setw(11) << getPayment()
      << setw(12) << getInterest()
      << getPrincipal()
      << endl;
   }
}
void Mortgage::credit(double x){
   setPrincipal(getPrincipal() - x);
}

