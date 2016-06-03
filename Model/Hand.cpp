//
//  Created by Chris Arsenault on 2016-05-13.
//  Copyright © 2016 Chris Arsenault. All rights reserved.
//

#include "Hand.h"
#include <algorithm>


Hand::Hand()
{
	loadPayoutHands();

}

Hand::~Hand()
{
}

std::string Hand::handToString(int i)
{
    return _hand[i]->toString();
}
void Hand::clear() // clears all the cards in hand
{
    _hand.clear();
}

/*const char* getPokerHandName(payOuts type)
{
   switch (type)
   {
   case payOuts::PAIR: return "Pair";
   case payOuts::TWOPAIR: return "Two Pair";
   case payOuts::FOUROFAKIND: return "Four of a kind";
   case payOuts::THREEOAKIND: return "Three of a kind";
   case payOuts::FULLHOUSE: return "Full House";
   case payOuts::STRAIGHT: return "Straight";
   case payOuts::FLUSH: return "Flush";
   case payOuts::STRAIGHTFLUSH: return "Straight Flush";
   default : return "Royal Flush";
   }
}*/

void Hand::addCard(Cardptr c)
{
	_hand.push_back(c);
	_draw.push_back(false);
}

void Hand::removeCard(int c)
{
	_hand.erase(_hand.begin() + (c - 1));
}

void Hand::redraw(int i, Cardptr c)
{
	_hand[i - 1] = c; //draws a new card from the deck and places it at the position -1 since vector is 0 based and the player picks between 1-5
}

void Hand::checkHand()  //checks to see if there was a match to one of the hands and sets the value to true
{

	if (findRoyalFlush())
		_payoutHands[payOuts::ROYALFLUSH] = true;
	else if (findStraightFlush())
		_payoutHands[payOuts::STRAIGHTFLUSH] = true;
	else if (findFourOfAKind())
		_payoutHands[payOuts::FOUROFAKIND] = true;
	else if (findFullHouse())
		_payoutHands[payOuts::FULLHOUSE] = true;
	else if (findFlush())
		_payoutHands[payOuts::FLUSH] = true;
	else if (findStraight())
		_payoutHands[payOuts::STRAIGHT] = true;
	else if (findThreeOfAKind())
		_payoutHands[payOuts::THREEOAKIND] = true;
	else if (findTwoPair())
		_payoutHands[payOuts::TWOPAIR] = true;
	else if (findPair())
		_payoutHands[payOuts::PAIR] = true;

}

void Hand::loadPayoutHands() //prepares the payout hands to be compared in the outcome method in videoPoker
{
	std::pair<payOuts, bool> pair(payOuts::PAIR, false);
	std::pair<payOuts, bool> TwoPair(payOuts::TWOPAIR, false);
	std::pair<payOuts, bool> threeoak(payOuts::THREEOAKIND, false);
	std::pair<payOuts, bool> Straight(payOuts::STRAIGHT, false);
	std::pair<payOuts, bool> Flush(payOuts::FLUSH, false);
	std::pair<payOuts, bool> FullHouse(payOuts::FULLHOUSE, false);
	std::pair<payOuts, bool> fouroak(payOuts::FOUROFAKIND, false);
	std::pair<payOuts, bool> StraightFlush(payOuts::STRAIGHTFLUSH, false);
	std::pair<payOuts, bool> RoyalFlush(payOuts::ROYALFLUSH, false);

	_payoutHands.insert(pair);
	_payoutHands.insert(TwoPair);
	_payoutHands.insert(threeoak);
	_payoutHands.insert(Straight);
	_payoutHands.insert(Flush);
	_payoutHands.insert(FullHouse);
	_payoutHands.insert(fouroak);
	_payoutHands.insert(StraightFlush);
	_payoutHands.insert(RoyalFlush);
}

bool Hand::findPair()
{
	std::map<Face, int>map;

	for (int i = 0; i != _hand.size(); i++)
	{
		if (_hand[i]->face == Face::KING || _hand[i]->face == Face::QUEEN || _hand[i]->face == Face::JACK || _hand[i]->face == Face::ACE)
			map[_hand[i]->face]++;
	}

	int pairCount = count_if(map.begin(), map.end(), [](std::pair<Face, int> e) {return e.second == 2; });

	if (pairCount == 1)
	{
		return true;
	}
	else
		return false;
}

bool Hand::findThreeOfAKind()
{
	std::map<Face, int>map;

	for (int i = 0; i != _hand.size(); i++)
		map[_hand[i]->face]++;

	int pairCount = count_if(map.begin(), map.end(), [](std::pair<Face, int> e) {return(e.second == 3); });

	if (pairCount == 1)
	{
		//std::cout << "three of a kind found" << std::endl;
		return true;
	}
	else
		return false;
}

bool Hand::findFourOfAKind()
{
	std::map<Face, int>map;

	for (int i = 0; i != _hand.size(); i++)
		map[_hand[i]->face]++;

	int pairCount = count_if(map.begin(), map.end(), [](std::pair<Face, int> e) {return(e.second == 4); });

	if (pairCount == 1)
	{
		//std::cout << "four of a kind found" << std::endl;
		return true;
	}
	else
		return false;
}

bool Hand::findFullHouse()
{
	if (findPair() == true && findThreeOfAKind() == true)
		return true;
	else
		return false;
}

bool Hand::findTwoPair()
{
	std::map<Face, int>map;

	for (int i = 0; i != _hand.size(); i++)
		map[_hand[i]->face]++;

	int pairCount = count_if(map.begin(), map.end(), [](std::pair<Face, int> e) {return(e.second == 2); });

	if (pairCount == 2)
	{

		return true;
	}
	else
		return false;
}

bool Hand::findFlush()
{
	std::set<Suit> hand;
	for (int i = 0; i != _hand.size(); i++)
		hand.insert(_hand[i]->suit);

	if (hand.size() == 1)
		return true;
	else
		return false;
}

bool Hand::findStraight()
{

	std::set<int> hand;



	for (int i = 0; i != _hand.size(); i++)
	{

		hand.insert((int)_hand[i]->face);
	}

	auto start = hand.begin();
	auto last = hand.end();
	last--;
	if (hand.size() == 5) {
		if (*start == *last - (hand.size() - 1))
		{
			return true;
		}
		else if (*start == 0)
		{
			hand.insert(13);
			start++;
			last = hand.end();
			last--;
			if (*start == *last - (_hand.size() - 1))
			{
				return true;
			}
		}
		else
			return false;
	}
	return false;
}

bool Hand::findStraightFlush()
{
	if (findStraight() == true && findFlush() == true)
		return true;
	else
		return false;
}

bool Hand::findRoyalFlush()
{

	std::set<int> hand;



	for (int i = 0; i != _hand.size(); i++)
	{

		hand.insert((int)_hand[i]->face);
	}

	auto start = hand.begin();
	auto last = hand.end();
	last--;
	if (hand.size() == 5) {
		if (*start == 0)
		{
			hand.insert(13);
			start++;
			last = hand.end();
			last--;

			if (*start == *last - (_hand.size() - 1) && findFlush() == true)
			{
				return true;
			}
		}
		else
			return false;
	}
	return false;

}

bool Hand::isDraw(int idx)
{
	if (_draw[idx] == true)  //checks to see if the card need to be drawn
		return true;
	else
		return false;
}

void Hand::toggleDraw(int idx)
{
	_draw[idx - 1] = !_draw[idx - 1]; //toggles the _draw so that the player can take back a choice if they want to
}
