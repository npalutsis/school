/*Author: Nick Palutsis*/

#include <stdio.h>
/*Calculate the monthly mortgage payments for a user*/

int main(void)
{
   double balance;
   double rate;
   double interest;
   int month;
   double total;
   int totaly;
   int totalm;
   double payment;
   
   printf("How much is your mortgage in dollars?\n");
   scanf("%lf", &balance);
   if(balance < 0){
   printf("You can't have a negative mortgage. Please enter a valid mortgage value:\n");
   scanf("%lf", &balance);
   }
   
   printf("What is your monthly payment in dollars?\n");
   scanf("%lf", &payment);
   if(payment < 0){
   printf("You can't have a negative payment. Please enter a valid payment value:\n");
   scanf("%lf", &payment);
   }
   
   printf("What is the percent of your interest rate?\n");
   scanf("%lf", &rate);
   if(rate < 0){
   printf("You can't have a negative interest rate. Please enter a valid interest rate:\n");
   scanf("%lf", &rate);
   }
   
   rate = rate / 100;
   month = 1;
   
   printf("Month   Payment    Interest   Balance\n");
   
   while(balance > 0){
     interest = balance * rate / 12;
     balance = balance + interest;
     
     if(balance <= payment){
     payment = balance;
     }
     
     balance = balance - payment;
     total = total + payment;
     
     printf("%5d   $%7.2lf   $%7.2lf   $%9.2lf\n", month, payment, interest, balance);
     month = month + 1;
   }
   month = month - 1;
   totaly = month / 12;
   totalm = month % 12;
   
   printf("\nYou paid a total of $%.2lf over %d years and %d months\n\n", total, totaly, totalm);
   
   return 0;
}
