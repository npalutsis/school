#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

class CardDeck{
	
	friend ostream &operator<<(ostream &, CardDeck &);
	
	public:
		CardDeck(int = 52);
		int getSize();
		void shuffle();
		int inOrder();
		void printReverse();
		void printOrder();
	private:
		int num;
		deque<int> deck;
};
