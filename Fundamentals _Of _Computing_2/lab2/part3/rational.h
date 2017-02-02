/* Author: Nick Palutsis
	Date: February 2, 2016
	CSE20212
	Lab2 */

#include <iostream>
#ifndef RATIONAL_H
#define RATIONAL_H
using namespace std;

class Rational{
   
   friend ostream &operator<<(ostream &, Rational &);
   
   public:
      Rational();
      Rational(int, int);
      Rational operator + (Rational &);
      Rational operator - (Rational &);
      Rational operator * (Rational &);
      Rational operator ! ();
      void userInteraction();
   
   private:
      int gcd(int, int);
      int num;
      int denom;
};
#endif
