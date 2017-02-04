all: bank_account

bank_account: checking.o boatLoan.o bankAccount.o
	g++ -o checking.o boatLoan.o bankAccount.o
 
checking.o: checking.cpp bankAccount.o
	g++ -c checking.cpp
	
boatLoan.o: boatLoan.cpp bankAccount.o
	g++ -c boatLoan.cpp

bankAccount.o: bankAccount.cpp
	g++ -c bankAccount.cpp

clean:
	rm -f *.o *~ bank_account
