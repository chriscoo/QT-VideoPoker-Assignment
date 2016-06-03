//
//  Created by Chris Arsenault on 2016-05-13.
//  Copyright © 2016 Chris Arsenault. All rights reserved.
//

#pragma once
#include "Card.h"
#include <string>
#include <vector>
#include <memory>

struct Card;
using Cardptr = std::shared_ptr<Card>;

class Deck
{
public:
	Deck();
	~Deck();
	const bool isEmpty();
	Cardptr draw();
	void shuffle();

private:
	std::vector<Cardptr> _deck;
	int _topOfDeck;
	
};

