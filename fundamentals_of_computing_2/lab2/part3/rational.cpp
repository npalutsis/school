/* Author: Nick Palutsis
	Date: February 2, 2016
	CSE20212
	Lab2 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;
#include "rational.h"

Rational::Rational(){
   num = 1;
   denom = 1;
}

ostream &operator << (ostream &output, Rational &ratNum){
   output << ratNum.num << "/" << ratNum.denom;
   return(output);
}

Rational::Rational(int x, int y){
   int GCD;
   if(y == 0){
      cout << "ERROR: Zero (0) is not a valid denominator, it will be set to one (1)" << endl;
      y = 1;
   }
   GCD = gcd(x, y);
   if(GCD == 1){
      num = x;
      denom = y;
   }
   else{
      num = x / GCD;
      denom = y / GCD;
   }
}

int Rational::gcd(int a, int b){
   int c, d;
   while(b != 0){
      d = b;
      b = a % b;
      a = d;
   }
   c = a;
   return c;
}

Rational Rational:: operator + (Rational &k){
   int newNum, newDenom;
   newDenom = this->denom * k.denom;
   newNum = (this->num * k.denom) + (this->denom * k.num);
   Rational Temp (newNum, newDenom);
   return(Temp);
}

Rational Rational:: operator - (Rational &k){
   int newNum, newDenom;
   newDenom = this->denom * k.denom;
   newNum = (this->num * k.denom) - (this->denom * k.num);
   Rational Temp (newNum, newDenom);
   return(Temp);
}

Rational Rational:: operator * (Rational &k){
   int newNum, newDenom;
   newDenom = this->denom * k.denom;
   newNum = (this->num * k.denom) * (this->denom * k.num);
   Rational Temp (newNum, newDenom);
   return(Temp);
}

Rational Rational:: operator ! (){
   int newNum, newDenom;
   newDenom = this->num;
   newNum = this->denom;
   Rational Temp (newNum, newDenom);
   return(Temp);
}

void Rational::userInteraction(){
   int num1, num2, denom1, denom2;
   cout << "Please enter a numerator and denominator for two rational numbers" << endl;
   cout << "First nuemrator: " << endl;
   cin >> num1;
   cout << "First denominator: " << endl;
   cin >> denom1;
   cout << "Second numerator: " << endl;
   cin >> num2;
   cout << "Second denominator: " << endl;
   cin >> denom2;
   Rational fraction1(num1, denom1);
   Rational fraction2(num2, denom2);
   cout << endl;
   cout << "Fraction 1: " << fraction1 << endl;
   cout << "Fraction 2: " << fraction2 << endl;
   cout << endl;
   Rational x1, x2, x3, x4, x5, x6;
   x1 = fraction1 + fraction2;
   cout << fraction1 << " + " << fraction2 << " = " << x1 << endl;
   x2 = fraction1 - fraction2;
   cout << fraction1 << " - " << fraction2 << " = " << x2 << endl;
   x3 = fraction2 - fraction1;
   cout << fraction2 << " - " << fraction1 << " = " << x3 << endl;
   x4 = fraction1 * fraction2;
   cout << fraction1 << " * " << fraction2 << " = " << x4 << endl;
   x5 = !(fraction1);
   cout << "The reciprocal of the fraction 1 is " << x5 << endl;
   x6 = !(fraction2);
   cout << "The reciprocal of the fraction 2 is " << x6 << endl;
}




























