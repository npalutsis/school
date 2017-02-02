all: package

package: main.o TwoDayPackage.o OvernightPackage.o package.o
	g++ -o package main.o TwoDayPackage.o OvernightPackage.o package.o

main.o: main.cpp
	g++ -c main.cpp

package.o: package.cpp package.h
	g++ -c package.cpp

TwoDayPackage.o: TwoDayPackage.cpp TwoDayPackage.h
	g++ -c TwoDayPackage.cpp
	
OvernightPackage.o: OvernightPackage.cpp OvernightPackage.h
	g++ -c OvernightPackage.cpp

clean:
	rm -f *.o *~ package
