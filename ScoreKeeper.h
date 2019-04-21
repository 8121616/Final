/************************
Erich Choudhury
Thomas Daughtridge
Grant Caskey
ECGR 2104
April 30, 2018
ScoreKeeper.h
************************/

#ifndef SCOREKEEPER_H
#define SCOREKEEPER_H

#include "Card.h"
#include <iostream>
#include <vector>

using namespace std;

class ScoreKeeper {

private:

int deadwoodSize;
int melds;
int playerscore;
int deadwood;
int totalScore;
int wins;
vector<Card> playerHand;

public:

ScoreKeeper();
int getMelds();
void updateScore(int score);
void updateWins();
int getScore();
int getPlayerScore();
int getDeadwood();
int getWins();
int checkWin();
void getPlayerHand(vector<Card> h);
int scoreHand(vector<Card> h);

};

#endif
