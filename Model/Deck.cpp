//
//  Created by Chris Arsenault on 2016-05-13.
//  Copyright © 2016 Chris Arsenault. All rights reserved.
//

#include "Deck.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>

Deck::Deck() //loads the deck with cards
{
	srand(static_cast<unsigned int>(time(0)));
	for (auto f : Card::suits)
		for (auto s : Card::faces)
			_deck.push_back(std::make_shared<Card>(Card(s, f)));

	_topOfDeck = _deck.size() - 1;
}


Deck::~Deck()
{
}



const bool Deck::isEmpty() //check to see if the deck is empty
{
	if (_topOfDeck < 0)
		return true;
	else
		return false;
}

Cardptr Deck::draw()
{
	//
	return _deck.at(_topOfDeck--); //takes the card at the top of the deck
}

void Deck::shuffle() //shuffles the cards in a random order
{
	for (int i = 0; i < _deck.size(); ++i)
	{
		swap(_deck[i], _deck[i + (rand() % (_deck.size() - i))]);
	}
	_topOfDeck = _deck.size() - 1;
}
