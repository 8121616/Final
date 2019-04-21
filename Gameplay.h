/************************
Erich Choudhury
Thomas Daughtridge
Grant Caskey
ECGR 2104
April 30, 2018
Gameplay.h
************************/

#ifndef GAMEPLAY_H
#define	GAMEPLAY_H

#include "Card.h"
#include "ScoreKeeper.h"
#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

void displayDeck(stack<Card> d);
void displayBoard(vector<Card>& h);
void playerTurn(vector<Card>& player, stack<Card>& draw, stack<Card>& discard, bool& end, ScoreKeeper& pScore);
int input(bool v, string s, int max, int min);
void compTurn(vector<Card>& comp, stack<Card>& draw, stack<Card>& discard, bool& end, ScoreKeeper& cScore);
void roundStart(vector<Card>& comp, vector<Card>& player, stack<Card>& discard);
void roundScoring(ScoreKeeper& wScore, ScoreKeeper& lScore, int win);
void howToPlay();

#endif
