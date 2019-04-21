/************************
Erich Choudhury
Thomas Daughtridge
Grant Caskey
ECGR 2104
April 30, 2018
Gameplay.cpp
************************/

#include "Gameplay.h"
#include "Dealing.h"
#include "Card.h"
#include "ScoreKeeper.h"
#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

//create arrays for each of the different ways to identify the cards
string names[] = {"Ace", "Two", "Three", "Four", "Five",
 "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

string suits[] = {"Spades", "Hearts", "Clubs", "Diamonds"};

string abrevNames[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
char abrevSuits[] = {'S','H','C','D'};

//Displays Draw and Discard Deck Piles
void displayDeck(stack<Card> d) {

	//get the suit and number from the card on top of the discard stack
	int dnum = d.top().getNumber();
	int dsuit = d.top().getSuit();

	//display draw and discard piles
	cout << "  ?---?\t\t\t\t\t\t\t\t   " << abrevNames[dnum-1] << "---" << abrevSuits[dsuit-1]<< "\t" << endl;
	cout << "  |   |\t\t\t\t\t\t\t\t   |" << "   " << "|" << "\t" << endl;
	cout << "  |   |\t\t\t\t\t\t\t\t   |" << "   " << "|" << "\t" << endl;
	cout << "  |   |\t\t\t\t\t\t\t\t   |" << "   " << "|" << "\t" << endl;
	cout << "  ?---?\t\t\t\t\t\t\t\t   " << abrevSuits[dsuit-1] << "---" << abrevNames[dnum-1] << "\t" << endl;
	cout << "Draw Pile\t\t\t\t\t\t\tDiscard Pile" << endl;
}

//displays the player hand
void displayBoard(vector<Card>& h) {	

	//display cards in this format (S = suit, # = number):
	//  #---S
	//  |   |	
	//  |   |
	//  |   |
	//  S---#


	cout << endl;

	for (int x = 0; x < h.size(); x++) {
		Card c = h[x];		
		int num = c.getNumber();
		int suit = c.getSuit();
		cout << abrevNames[num-1] << "---" << abrevSuits[suit-1]<< "\t";
	}

	cout << endl;

	for (int i = 0; i < h.size(); i++) {
		cout << "|" << "   " << "|" << "\t";
	}

	cout << endl;

	for (int i = 0; i < h.size(); i++) {
		cout << "|" << " " << i + 1 << " " << "|" << "\t";
	}

	cout << endl;
	
	for (int i = 0; i < h.size(); i++) {
		cout << "|" << "   " << "|" << "\t";
	}
	
	cout << endl;

	for (int x = 0; x < h.size(); x++) {
		Card c = h[x];	
		int num = c.getNumber();
		int suit = c.getSuit();	
		cout << abrevSuits[suit-1] << "---" << abrevNames[num-1] << "\t";
	}
	
	cout << endl;

	for (int x = 0; x < h.size(); x++) {	
		Card c = h[x];
		int num = c.getNumber();
		int suit = c.getSuit();
		cout << names[num-1] << "\t";
	}

	cout << endl;

	for (int x = 0; x < h.size(); x++) {	
		Card c = h[x];
		int suit = c.getSuit();
		cout << "of " << abrevSuits[suit-1] << "\t";
	}
	
	cout << endl;
}

//Used for all input (Securely takes in data), returns int value
int input(bool v, string s, int max, int min) {
	
	int choice;

	while (!v) {
		
		v = true;
	
		cout << endl << s;
		cin >> choice;
		
		if (cin.fail() || choice > max || choice < min) {
			cin.clear();
			cin.ignore();
			cout << "Sorry, that response was not understood. Please try again." << endl;
			v = false;	
		}

		cout << "You chose " << choice << endl;
		
	}

	return choice;
}


void playerTurn(vector<Card>& player, stack<Card>& draw, stack<Card>& discard, bool& end, ScoreKeeper& pScore) {
	
	bool valid = false;
	int choice;

	//input prompts
	string selectDrawSort = "Select from the draw pile (1) or discard pile (2)! Press (3) to sort! (1-3)\n>";
	string selectDraw = "Select from the draw pile (1) or discard pile (2)!\n";
	string selectKnock = "Continue to select a card to discard (1) or press (0) to knock! (0/1)\n";
	string selectDiscard = "Select card to discard! (1-11)\n>";
	
	displayDeck(discard);
	displayBoard(player);
	
	//get first input
	choice = input(valid, selectDrawSort, 3, 1);

		//sort the player hand
		while (choice == 3) {
			system("clear");
			sort(player.begin(), player.end());
			displayDeck(discard);
			displayBoard(player);
			choice = input(valid, selectDraw, 2, 1);
		}

		//take a card from draw
		if (choice == 1) {
			system("clear");
			dealToHands(1, player, draw);
			cout << "You took a card from draw! " << choice << endl;
			displayBoard(player);
			pScore.getPlayerHand(player);
			pScore.scoreHand(player);
			cout <<"Your deadwood value is " << pScore.getDeadwood() << " and you have " << pScore.getMelds() << " melds." << endl;
			//check for win
			choice = pScore.checkWin();
			
			//check for knock and end game
			if (choice == 6) {
				choice = input(valid, selectKnock, 1, 0);
				if (choice == 0) {
					end = true;
					goto loc;
				}
			}

			//check for gin or big gin and end game
			if (choice == 5 || choice == 7) {
				end = true;
				goto loc;
			}

			//choose a card to discard
			choice = input(valid, selectDiscard, 11, 1);
	
			//discard chosen card
			choice -= 1;
			Card c = player[choice];
			discard.push(c);
			player.erase(player.begin() + choice);

			displayBoard(player);
		}
		
		//take a card from discard
		else {
			system("clear");
			dealToHands(1, player, discard);
			cout << "You took a card from discard! " << choice << endl;
			displayBoard(player);
			pScore.getPlayerHand(player);
			pScore.scoreHand(player);
			cout <<"Your deadwood value is " << pScore.getDeadwood() << " and you have " << 					pScore.getMelds() << " melds." << endl;

			//Check win
			choice = pScore.checkWin();
		
			//If returns knock
			if (choice == 6) {
				choice = input(valid, selectKnock, 1, 0);
				if (choice == 0) {
					end = true;
					goto loc;
				}
			}

			//If returns Gin or Big Gin
			if (choice == 5 || choice == 7) {
				end = true;				
				goto loc;
			}

			//choose a card to discard
			choice = input(valid, selectDiscard, 11, 1);

			choice -= 1;
			Card c = player[choice];
			discard.push(c);
			player.erase(player.begin() + choice);
			displayDeck(discard);
			displayBoard(player);
		}

	loc:
	cout << endl;
}

//Computer turn
void compTurn(vector<Card>& comp, stack<Card>& draw, stack<Card>& discard, bool& end, ScoreKeeper& cScore) {

	int choice;
	
	//always choses 1 (Really Dumb)
	choice = 1;

	if (draw.size() == 0) {
		choice = 2;
	}

	cout << "Computer's Turn!" << endl;

		if (choice == 1) {
			dealToHands(1, comp, draw);
			cScore.getPlayerHand(comp);
			cScore.scoreHand(comp);

			choice = cScore.checkWin();
			
			//if knocks end game
			if (choice == 6) {
				end = true;
				goto fin;
			}

			//if gin or big gin end game
			if (choice == 5 || choice == 7) {
				end = true;
				goto fin;
			}

			//discard last card
			choice = 11;
	
			choice -= 1;
			Card c = comp[choice];
			discard.push(c);
			comp.erase(comp.begin() + choice);
		}
		
		else {
			//gives alternative if we would like to add in probability later
			dealToHands(1, comp, discard);
			cScore.getPlayerHand(comp);
			cScore.scoreHand(comp);

			choice = cScore.checkWin();

			if (choice == 6) {
				end = true;
				goto fin;
			}

			if (choice == 5 || choice == 7) {
				end = true;				
				goto fin;
			}

			choice = 1;

			choice -= 1;
			Card c = comp[choice];
			discard.push(c);
			comp.erase(comp.begin() + choice);
		}
	fin:	
	cout << "My turn! Thinking..." << endl;	
}

//pass or take from discard on first round
void roundStart(vector<Card>& comp, vector<Card>& player, stack<Card>& discard) {
		
		bool valid = false;

		//string input queries
		string discPass = "Would you like to draw from discard (1) or pass (2)? (1/2)\n>";
		string selectDiscard = "Select card to discard! (1-11)\n>";

		displayDeck(discard);
		displayBoard(player);

		//ask for input
		int choice = input(valid, discPass, 2, 1);
			
			//take card from discard
			if (choice == 1) {
				system("clear");
				dealToHands(1, player, discard);
				displayBoard(player);
				choice = input(valid, selectDiscard, 11, 1);
	
				//discard chosen card
				choice -= 1;
				Card c = player[choice];
				discard.push(c);
				player.erase(player.begin() + choice);

				displayDeck(discard);
				displayBoard(player);
				cout << "Computer's turn!" << endl;
			}
			
			else {
				//pass
				cout << "You passed. My turn!" << endl;
				
			}
		
		//computer takes diiscard and discards first card
		dealToHands(1, comp, discard);
		choice = 1;

		choice -= 1;
		Card c = comp[choice];
		discard.push(c);
		comp.erase(comp.begin() + choice);
}

void roundScoring(ScoreKeeper& wScore, ScoreKeeper& lScore, int win) {
	
	//gin: 
	if (win == 5) {
		//add 25 + losing players deadwood
		cout << "GOING GIN! +25!" << endl;
		wScore.updateScore( lScore.getDeadwood() + 25);
	}

	//knock:
	else if (win == 6) {
		//get difference in score
		if (wScore.getDeadwood() < lScore.getDeadwood()) {
			cout << "Knocked!" << endl;
			wScore.updateScore((lScore.getDeadwood() - wScore.getDeadwood()));
		}
		//undercut, get differencec and add 25 to winner
		else if (wScore.getDeadwood() >= lScore.getDeadwood()) {
			cout << "UNDERCUT! Opponent gets 25 points!" << endl;
			lScore.updateScore(wScore.getDeadwood() - lScore.getDeadwood() + 25);
		}
	}

	//big gin
	else if (win == 7) {
		//add 31 plus loser's score
		cout << "BIG GIN! +31!" << endl;
		wScore.updateScore( lScore.getDeadwood() + 31);
	}
}

//display instructions
void howToPlay() {

cout << "How to play:" << endl << endl;

cout << "Melds- A meld is a combination of three cards.  Those three cards can either be cards of the same face value or cards that make a run in the same suit.  For example, a three of hearts followed by a four and five of hearts is a meld, but if one of those cards were a different suit it would not count.  Additionally, an ace takes a value of one, so an ace two and three of the same suit is a run but a queen king ace of the same suit is not." << endl << endl;

cout << "Gameplay- Gin Rummy is played with two players.  The game is played with one deck of cards and there is a draw and discard pile, the draw pile being face down and the discard being face up.  Each player begins the game with 10 cards.  For the first turn, the first player can either take the first card from the discard pile or pass.  Every other turn after the first includes the player choosing to draw from either the draw or discard pile. That player must then discard a card into the discard pile.  The round ends either when the deck is out of cards (a tie) or if a player knocks.  A knock is when a player has at least three melds.  Any card that is not included in the melds is considered deadwood, and the players deadwood value is a total of all the face values of any card not in a meld." << endl << endl;

cout << "Scoring- When a player knocks, the deadwood value for each player is calculated and if the knocking player has less he receives the difference in deadwood as points.  If the other player has less they receive the difference in deadwood value in points, but also an undercut bonus of 25 points.  If a player knocks with 0 deadwood, that is a gin and they get 25 bonus points on top of the regular scoring.  If a player is able to include all 11 cards, that is a big gin and they receive 31 bonus points on top of the regular scoring.  The game continues until a player reaches 100 points." << endl << endl;

}

