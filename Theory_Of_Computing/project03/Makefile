CXX=		g++
CXXFLAGS=	-g -Wall -std=gnu++11
SHELL=		bash

all:		tm

solution:	tm.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ -static-libstdc++.so6

clean:
	rm -f tm *.exe *~