all: bank_account

bank_account: main.o checking.o boatLoan.o bankAccount.o
	g++ -o bank_account main.o checking.o boatLoan.o bankAccount.o

main.o: main.cpp
	g++ -c main.cpp

bankAccount.o: bankAccount.cpp bankAccount.h
	g++ -c bankAccount.cpp

checking.o: checking.cpp checking.h
	g++ -c checking.cpp
	
boatLoan.o: boatLoan.cpp boatLoan.h
	g++ -c boatLoan.cpp

clean:
	rm -f *.o *~ bank_account
