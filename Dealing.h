/************************
Erich Choudhury
Thomas Daughtridge
Grant Caskey
ECGR 2104
April 30, 2018
Dealing.h
************************/

#ifndef DEALING_H
#define DEALING_H

#include "Card.h"
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

void createDeck(stack<Card>& s, vector<Card>& d);
void dealToHands(int num, vector<Card>& target, stack<Card>& sender);
void dealToDiscard(int num, stack<Card>& target, stack<Card>& sender);
void sendToDraw(stack<Card>& target, vector<Card>& sender);
void reset(vector<Card>& deck, stack<Card>& draw, stack<Card>& discard, vector<Card>& player, vector<Card>& computer);

#endif
