/************************
Erich Choudhury
Thomas Daughtridge
Grant Caskey
ECGR 2104
April 30, 2018
GinRummy.cpp
************************/

#include "Card.h"
#include "Dealing.h"
#include "Gameplay.h"
#include "ScoreKeeper.h"
#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int main() {

//** Initial Game Setup *********************************************************************

	system("clear");

	//random seed
	srand(time(0));

	//create deck in order to shuffle
	vector<Card> deck;

	//create four card locations
	stack<Card> draw;
	stack<Card> discard;
	vector<Card> playerHand;
	vector<Card> compHand;

	//create and shuffle a new deck of cards
	createDeck(draw, deck);

	//deal cards
	dealToHands(10, playerHand, draw);
	dealToHands(10, compHand, draw);
	dealToDiscard(1, discard, draw);
	
//** Establish Variables *********************************************************************
	
	//create two score-keepers
	ScoreKeeper pScore;
	ScoreKeeper cScore;

	//has the game ended?
	bool end = false;

	//is the input valid?
	bool valid = false;

	//store turn and round number
	int turn = 1;
	int round = 1;

	//store type of win (6-Knock,5-Gin,10-NoWin,7-BigGin)
	int winType;

	//used to start game after instructions
	int begin;

	//store bonus values after game
	int playerBonusPoints;
	int compBonusPoints;

//** Intro Screen ****************************************************************************

cout << "Welcome to" << endl << endl;                                                                                                      
cout << "  ,ad8888ba,  88                88888888ba                                                               " << endl;
cout << " d8''    `'8b ''                88      '8b                                                              " << endl;
cout << "d8'                             88      ,8P                                                              " << endl;
cout << "88            88 8b,dPPYba,     88aaaaaa8P' 88       88 88,dPYba,,adPYba,  88,dPYba,,adPYba,  8b       d8" << endl;
cout << "88      88888 88 88P'   `'8a    88''''88'   88       88 88P'   '88'    '8a 88P'   '88'    '8a `8b     d8'" << endl;
cout << "Y8,        88 88 88       88    88    `8b   88       88 88      88      88 88      88      88  `8b   d8' " << endl;
cout << " Y8a.    .a88 88 88       88    88     `8b  '8a,   ,a88 88      88      88 88      88      88   `8b,d8'  " << endl;
cout << "  `'Y88888P'  88 88       88    88      `8b  `'YbbdP'Y8 88      88      88 88      88      88     Y88'   " << endl;
cout << "                                                                                                  d8'    " << endl;
cout << "   Erich, Thomas, and Grant                                                                      d8'     " << endl;	
         
        sleep(3);
	cout << endl << "Press ENTER to continue..." << endl;

	getchar(); 
	system("clear");

	string title ="Hello! Welcome to Gin Rummy! To play, please select (1), to read the instructions, please type (2)! (1/2):\n>";
	begin = input(valid,title,2,1);

	if (begin == 2) {  
		system("clear");
		//display rules
		howToPlay();
		cout << "Press ENTER to play!" << endl;
		cin.clear();
		cin.ignore();
		getchar();
		cout << "Ok! Lets play!" << endl;
		sleep(1);
	}                                      
	
	system("clear");

//** Playing the Game **********************************************************************

	while (pScore.getScore() < 100 && cScore.getScore() < 100) {
		
		winType = 0;

		cout << "ROUND " << round << endl;

		//end is not returned and draw piles still has cards
		while (end == false && draw.size() != 0) {

			cout << "Turn: " << turn << endl << endl;		

			if (turn == 1) {
				roundStart(compHand, playerHand, discard);
				system("clear");
				turn++;
			}
		
			else {
				playerTurn(playerHand, draw, discard, end, pScore);
				system("clear");
				compTurn(compHand, draw, discard, end, cScore);
				sleep(3);
				system("clear");
				turn++;
			}

		}
			
		if (cScore.checkWin() < 10 || pScore.checkWin() < 10) {
			
			//Computer Win
			if (cScore.checkWin() != 10) {
				cout << "COMPUTER WINS ROUND " << round	<< endl;			
				winType = cScore.checkWin();
				roundScoring(cScore, pScore, winType);
				cScore.updateWins();
			}

			//Player Win
			else if (pScore.checkWin() != 10) {
				cout << "PLAYER WINS ROUND " << round	<< endl;
				winType = pScore.checkWin();
				roundScoring(pScore, cScore, winType);
				pScore.updateWins();
			}	

		}

		else {
						
			cout << "Draw Pile is Empty! It's a tie!" << endl;
			//Computer Win
			/*if (cScore.getDeadwood() < pScore.getDeadwood()) {
				cout << "COMPUTER WINS ROUND " << round	<< endl;			
				cScore.updateScore(pScore.getDeadwood() - cScore.getDeadwood());
				cScore.updateWins();
			}

			//Player Win
			else {
				cout << "PLAYER WINS ROUND " << round << endl;
				pScore.updateScore(cScore.getDeadwood() - pScore.getDeadwood());
				pScore.updateWins();
			}*/

		}

		//End of round stats
		cout << "Player Deadwood: " << pScore.getDeadwood() << " Computer Deadwood: " << cScore.getDeadwood() 				<< endl;
		cout << "Total Scores:" << " Player - " <<pScore.getScore() << ", Computer - " << cScore.getScore() << endl;
		cout << "Number of Wins:" << "Player - " << pScore.getWins() << ", Computer - " << cScore.getWins() << endl;

		cout << "Press ENTER to continue!" << endl;
		cin.clear();
		cin.ignore();
		getchar();
		cout << "Starting Round " << round+1 << endl;
		sleep(3);
		
		system("clear");

		//reset decks and redeal cards for the next round
		reset(deck, draw, discard, playerHand, compHand);
		dealToHands(10, playerHand, draw);
		dealToHands(10, compHand, draw);
		dealToDiscard(1, discard, draw);
		end = false;
		turn = 1;
		round++;
	}

	cout << "Game Over!" << endl;

//** Win Bonus Points ***********************************************************************
	
	//give 100 points to the winner
	if (pScore.getScore() > cScore.getScore()) {
		cout << "Player WON! +100" << endl;
		pScore.updateScore(100);
	}
	else if (cScore.getScore() > cScore.getScore()) {
		cout << "Computer WON! +100" << endl;
		cScore.updateScore(100);
	}
	else {
		cout << "It is a TIE!" << endl;
	}
	
//** No Wins Bonus Points *******************************************************************

	//Double computer's score if player had no wins
	if (pScore.getWins() == 0) {
		cout << "Player got ZERO wins, Computer's points DOUBLED!" << endl;
		cScore.updateScore(cScore.getScore());
	}

	//Double player's score if computer had now wins
	if (cScore.getWins() == 0) {
		cout << "Computer got ZERO wins, Player's points DOUBLED!" << endl;
		pScore.updateScore(pScore.getScore());
	}

//** Hand Wins Bonus Points *****************************************************************

	//Give 25 points extra for each hand won
	cout << "+25 points to each player per hand won!" << endl;
	
	playerBonusPoints = 25 * pScore.getWins();
	cout << "Player won " << pScore.getWins() << " rounds! +" << playerBonusPoints << " points!" << endl;
	pScore.updateScore(playerBonusPoints);

	compBonusPoints = 25 * cScore.getWins();
	cout << "Computer won " << cScore.getWins() << " rounds! +" << compBonusPoints << " points!" << endl;
	cScore.updateScore(compBonusPoints);
	
//** Display Winner ************************************************************************

	//display winner and total points
	if (pScore.getScore() > cScore.getScore()) {
		cout << "Player WON the game with " << pScore.getScore() << " points!" << endl;
	}

	if (cScore.getScore() < cScore.getScore()) {
		cout << "Computer WON the game!"  << cScore.getScore() << " points!" << endl;
	}
	

return 0;
}
