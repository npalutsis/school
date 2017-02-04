// Author: Nick Palutsis
   // Date: January 20, 2015
   // Prelab
   // CSE 20212

#include <iostream>
#include <cmath>
using namespace std;

int main() {

   double pi;
   double fraction;
   int terms;
   int i;

   cout << "Please enter the number of terms in the series: ";
   cin >> terms;

   for( i=1; i<=terms; i++ ) {
      fraction = (4 * pow(-1, i+1)) / (2*i - 1);
      pi = pi + fraction;
      cout << "Estimate after " << i << " term(s): " << pi << endl;
   }

   return 0;
}
