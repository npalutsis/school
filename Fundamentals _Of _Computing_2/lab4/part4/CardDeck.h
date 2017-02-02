/* Author: Nick Palutsis
	Date: February 16, 2016
	CSE 20212
	Lab 4 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

class CardDeck{
	
	friend ostream &operator<<(ostream &, CardDeck &);
	
	public:
		CardDeck(int);
		~CardDeck();
		int getSize();
		void shuffle();
		int inOrder();
		void printReverse();
		void printOrder();
		int monkeySort();
		int deal(int, int, string);
		void display(int, string);
	private:
		int num;
		deque<int> deck;
};
