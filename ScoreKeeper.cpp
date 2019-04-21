/************************
Erich Choudhury
Thomas Daughtridge
Grant Caskey
ECGR 2104
April 30, 2018
ScoreKeeper.cpp
************************/

#include "Card.h"
#include "ScoreKeeper.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

ScoreKeeper::ScoreKeeper() { melds = 0; totalScore = 0; deadwood = 0; playerscore = 0; wins = 0; }

int ScoreKeeper::getMelds() { return melds; }

int ScoreKeeper::getPlayerScore() { return playerscore; }

int ScoreKeeper::getDeadwood() { return deadwood; }

void ScoreKeeper::getPlayerHand(vector<Card> h) { playerHand = h; } //takes in a vector

int ScoreKeeper::getWins() { return wins; }

void ScoreKeeper::updateScore(int score) { totalScore += score; }

void ScoreKeeper::updateWins() { wins++; }

int ScoreKeeper::getScore() { return totalScore; } 

int ScoreKeeper::checkWin() {
	
	//gin
	if (deadwoodSize == 1) {
		return 5;
	}
	
	//knock
	else if (melds == 3) {
		return 6;
	}	

	//big gin
	else if (deadwoodSize == 0) {
		return 7;
	}

	else { 
		return 10; 
	}
}
//calculates best melds and deadwood
int ScoreKeeper::scoreHand(vector<Card> h) {

	int deadwoodOne = 0;
	int meldsOne = 0;
	int deadwoodTwo = 0;
	int meldsTwo = 0;
	vector<Card> d;
	d = h;
	vector<int> vals;
	int deadwoodSizeOne;
	int deadwoodSizeTwo;

	sort(h.begin(), h.end());
	sort(d.begin(), d.end());	

	//pairs
	for( int i = 0; i < h.size(); i++) {
		
		int num = 0;

		for(int j = 0; j < h.size(); j++) {
			if (h[i].getNumber() == h[j].getNumber()) {
				vals.push_back(j);
			}
		}

		if (vals.size() > 2) {
			meldsOne++;
			for(int x = 0; x < vals.size(); x++) {				
				h.erase(h.begin() + (vals[x - num]));
				num++;
			}
	
		}

		vals.clear();	
	}

	//runs
	int num;	

	for( int i = 0; i < h.size(); i++) {
		
		num = 1;

		vals.push_back(i);	
	
		for(int j = 0; j < h.size(); j++) {
			if ((h[i].getNumber() + num) == h[j].getNumber()) {
				if(h[i].getSuit() == h[j].getSuit()) {				
					vals.push_back(j);
					num++;
				}
			}

		}	

		if (vals.size() > 2) {
			meldsOne++;
			
			for(int e = 0; e < vals.size(); e++) {	
				Card c = h[vals[e]];			
				h.erase(h.begin() + (vals[e]));
				h.insert(h.begin(), c);
			}
		
			h.erase(h.begin(), h.begin() + vals.size());

		}

		vals.clear();	
	}

	deadwoodSizeOne = h.size();

	for(int y = 0; y < h.size(); y++) {
		if (h[y].getNumber() > 10) {
			deadwoodOne = deadwoodOne + 10;
		}
		else {
			deadwoodOne = deadwoodOne + h[y].getNumber();
		}
	}
	
	
	
	//************************************************************************

	//runs
	for( int i = 0; i < d.size(); i++) {
		
		num = 1;

		vals.push_back(i);	
	
		for(int j = 0; j < d.size(); j++) {
			if ((d[i].getNumber() + num) == d[j].getNumber()) {
				if(d[i].getSuit() == d[j].getSuit()) {				
					vals.push_back(j);
					num++;
				}
			}

		}	

		if (vals.size() > 2) {
			meldsTwo++;
			
			for(int e = 0; e < vals.size(); e++) {	
				Card c = d[vals[e]];			
				d.erase(d.begin() + (vals[e]));
				d.insert(d.begin(), c);
			}
		
			d.erase(d.begin(), d.begin() + vals.size());

		}

		vals.clear();	
	}

	//pairs
	for( int i = 0; i < d.size(); i++) {
		
		int num = 0;

		for(int j = 0; j < d.size(); j++) {
			if (d[i].getNumber() == d[j].getNumber()) {
				vals.push_back(j);
			}
		}

		if (vals.size() > 2) {
			meldsTwo++;
			for(int x = 0; x < vals.size(); x++) {				
				d.erase(d.begin() + (vals[x - num]));
				num++;
			}
	
		}

		vals.clear();	
	}
	
	deadwoodSizeTwo = h.size();

	for(int y = 0; y < h.size(); y++) {
		if (h[y].getNumber() > 10) {
			deadwoodTwo = deadwoodTwo + 10;
		}
		else {
			deadwoodTwo = deadwoodTwo + h[y].getNumber();
		}
		
	}

	if (deadwoodOne > deadwoodTwo) { deadwood = deadwoodOne; melds = meldsOne; deadwoodSize = deadwoodSizeOne;}
	else if (deadwoodOne < deadwoodTwo) { deadwood = deadwoodTwo; melds = meldsTwo;deadwoodSize = deadwoodSizeTwo;}
	else { deadwood = deadwoodOne; melds = meldsOne;deadwoodSize = deadwoodSizeOne;}

}

