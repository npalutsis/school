/* Author: Nick Palutsis
	Date: February 16, 2016
	CSE 20212
	Lab 4 */

#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include "CardDeck.h"

using namespace std;

int main () {
	srand (time(0));		// randomizes shuffle
	
	int play = 1;
	int player = 0;	// user's total
	int dealer = 0;	// dealer's total
	int i = 0;
	int faceDown;
	char anotherOne = 'n';
	char newGame;
	CardDeck Deck(52);
	Deck.shuffle();
	while(play){
		// Display new game header
		cout << endl << "******************" << endl << "*****New Game*****" << endl << "******************" << endl;
		
		// Shuffle deck if there are 15 cards left
		if(15 >= Deck.getSize() - i){
			i = 0;
			Deck.shuffle();
			cout << "The deck has been reshuffled." << endl;
		}
		
		// Initial deal
		player += Deck.deal(i, 1, "Player 1");
		dealer += Deck.deal(i++, 0, "The Dealer");
		faceDown = i;
		player += Deck.deal(i++, 1, "Player 1");
		dealer += Deck.deal(i++, 1, "The Dealer");
		
		// Ask user to hit
		do{
			cout << endl << "Your total is " << player << "." << endl;
			cout << "Would you like another card? (y/n): ";
			cin >> anotherOne;
			if(anotherOne == 'y')
				player += Deck.deal(i++, 1, "Player 1");
			if(player > 21){
				cout << "You went over. You lose!" << endl;
				break;
			}
		}while(anotherOne == 'y');
		
		// Deal dealer until >= 17
		while(dealer < 17 && player <= 21){
			cout << endl;
			dealer += Deck.deal(i++, 1, "The Dealer");
		}
		
		// Print the winner
		if(dealer > 21 && player <= 21)
			cout << "The Dealer went over. You win!" << endl;
		else if(player >= dealer && player <= 21)
			cout << "You beat the Dealer!" << endl;
		else
			cout << "The dealer won." << endl;
		
		// Ask to play again
		cout << "Would you like to play again? (y/n): ";
		cin >> newGame;
		if(newGame == 'n'){
			play = 0;
			cout << "Thanks for playing!" << endl;
		}
		player = 0;
		dealer = 0;
	}
		
	return 0;
}
