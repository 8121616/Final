/************************
Erich Choudhury
Thomas Daughtridge
Grant Caskey
ECGR 2104
April 30, 2018
Dealing.cpp
************************/

#include "Dealing.h"
#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

//Create the deck of 52 cards, 4 suits, 13 different types of cards
void createDeck(stack<Card>& s, vector<Card>& d) {
	for (int x = 1; x <= 4; x++) {
		for (int i = 1; i <= 13; i++) {
			Card card(i,x);
			d.push_back(card);
		}
	}
	
	random_shuffle( d.begin(), d.end() );

	for (int j = 0; j < d.size(); j++) {
		s.push(d[j]);
	}
}

//Move specific number of cards from stack to vector
void dealToHands(int num, vector<Card>& target, stack<Card>& sender) {
	if (sender.size() == 0) {
		cout << "Error" << endl;
	}
	else {
		for (int i = 1; i <= num; i++) {
			Card x = sender.top();
			sender.pop();
			target.push_back(x);
		}
	}

}

//Move specific number of cards from vector to stack
void sendToDraw(stack<Card>& target, vector<Card>& sender) {
	if (sender.size() == 0) {
		cout << "Error" << endl;
	}
	else {
		for (int i = sender.size(); i >= 1; i--) {
			Card x = sender[i];
			sender.pop_back();
			target.push(x);
		}
	}

}


//Move specific number of cards from stack <---> stack
void dealToDiscard(int num, stack<Card>& target, stack<Card>& sender) {
	if (sender.size() == 0) {
		cout << "Error" << endl;
	}
	else {
		for (int i = 1; i <= num; i++) {
			Card x = sender.top();
			sender.pop();
			target.push(x);
		}
	}
}

//Move all cards back to the draw pile
void reset(vector<Card>& deck, stack<Card>& draw, stack<Card>& discard, vector<Card>& player, vector<Card>& computer) {
	
	int discardSize = discard.size();
	
	sendToDraw(draw, player);
	sendToDraw(draw, computer);
	dealToDiscard(discardSize, draw, discard);

}

