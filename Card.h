/************************
Erich Choudhury
Thomas Daughtridge
Grant Caskey
ECGR 2104
April 30, 2018
Card.cpp
************************/

#ifndef CARD_H
#define CARD_H

class Card {

public:
	Card(int num, int su);
	int getSuit();
	int getNumber();
	void cardDisplay();
	bool operator<(Card a); //overload to sort
	~Card();
private:
	int suit;
	int number;

	
};

#endif
