//
//  Created by Chris Arsenault on 2016-05-13.
//  Copyright © 2016 Chris Arsenault. All rights reserved.
//

#pragma once
#include "Deck.h"
#include <unordered_map>

enum class payOuts { //enum of the possible hands to connect the correct hand to the payout
	PAIR,
	TWOPAIR,
	THREEOAKIND,
	STRAIGHT,
	FLUSH,
	FULLHOUSE,
	FOUROFAKIND,
	STRAIGHTFLUSH,
	ROYALFLUSH
};
struct Card;
using Cardptr = std::shared_ptr<Card>;
class Hand
{
public:
	Hand();
	~Hand();
	int sizeofHand() const { return _hand.size(); }
	friend std::ostream& operator<<(std::ostream& os, const Hand& h) //cout of hands
	{
		int i = 1;
		int j = 0;
		while (j < h.sizeofHand())		{
			if (h._draw[j] == true)
				std::cout << i << ") " << *h._hand[j] << " (drawing)" << std::endl;
			else
				std::cout << i << ") " << *h._hand[j] << " (holding)" << std::endl;

			i++;
			j++;
			
		}

		return os;
	}
    void clear();
	void addCard(Cardptr c); //adds a card to your hand (c) is from the deck
	void removeCard(int c); //removes a card form your hand at pos c and removed the sharedpointer form the hand
	void redraw(int i, Cardptr c); //replace card I with card C (from deck)

	void checkHand(); //checks each of the possible wins and turns it to true if it's found (indexed by key)
        std::string handToString(int i);
    //const char* getPokerHandName(payOuts type);
	std::unordered_map<payOuts, bool> _payoutHands;
	bool isDraw(int idx); // do I draw card at idx
	void toggleDraw(int idx);  //
    std::vector<Cardptr> _hand; //holds the hand
private:
	void loadPayoutHands();
	//possible hands
	bool findPair();
	bool findThreeOfAKind();
	bool findFourOfAKind();
	bool findFullHouse();
	bool findTwoPair();
	bool findFlush();
	bool findStraight();
	bool findStraightFlush();
	bool findRoyalFlush();

    std::vector<bool> _draw; // true if card is to be drawn
	
	
};

