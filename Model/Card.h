//
//  Created by Chris Arsenault on 2016-05-13.
//  Copyright © 2016 Chris Arsenault. All rights reserved.
//

#pragma once
#include<string>
#include <map>
#include <iostream>
#include <set>
enum class Suit { CLUB, DIAMOND, HEART, SPADE };
enum class Face { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };



struct Card
{
	Card() : face(Face::ACE), suit(Suit::CLUB) {} //dummy card
	Card(Face f, Suit s) : face(f), suit(s) {}
	Suit suit;
	Face face;
	static const std::set<Suit> suits;
	static const std::set<Face> faces;
std::string Card::toString() const;
	static const std::map<Face, std::string> faceNames;
	static const std::map<Suit, std::string> SuitNames;
	Card& operator=(const Card& rhs) //assignment operator
	{
		
			Card tmp(Face::ACE, Suit::CLUB);
			tmp.face = rhs.face;
			tmp.suit = rhs.suit;
			
			return tmp;
	} 
	inline friend std::ostream& operator<<(std::ostream& os, const Card& c) //cout overload to print cards
	{
		std::cout << faceNames.at(c.face) + " of " + Card::SuitNames.at(c.suit);
		return os;
	}

	friend bool operator==(const Card& l, const Card&r) //equals operator
	{
		if (l.face == r.face)
			return true;
		else
			return false;
	};

	friend bool operator!=(const Card& l, const Card& r) //does not equal operator
	{
		if (l.face == r.face && l.suit == r.suit)
			return true;
		else
			return false;
	};

};

bool operator<(const Card& l, const Card& r); //less than


