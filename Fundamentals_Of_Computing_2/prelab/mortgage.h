// Author: Nick Palutsis
   // Date: January 20, 2015
   // Prelab
   // CSE 20212

#ifndef COOKIE_H
#define COOKIE_H

class Mortgage {

   public:
      Mortgage(double, double, double);
      Mortgage();
      void setPrincipal(double);
      void setRate(double);
      void setPayment(double);
      void setInterest(double, double);
      void setMonth(int);
      
      double getPrincipal();
      double getRate();
      double getPayment();
      double getInterest();
      
      void credit(double);
      void amortize();
      
   private:
      double principal;
      double rate;
      double payment;
      double interest;
};

#endif
