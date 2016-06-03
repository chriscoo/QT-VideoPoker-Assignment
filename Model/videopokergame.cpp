//
//  Created by Chris Arsenault on 2016-05-13.
//  Copyright © 2016 Chris Arsenault. All rights reserved.
//


#include "VideoPokerGame.h"
#include "Deck.h"
#include "Hand.h"
#include <string>
VideoPokerGame::VideoPokerGame()
{
    initPayouts();
    deck.shuffle();
    while (_videoPokerHand._hand.size() != 5) //makes the hand
    {
        _videoPokerHand.addCard(deck.draw());
    }
}
VideoPokerGame::~VideoPokerGame()
{
}
void VideoPokerGame::dealNewHand()
{
    _videoPokerHand.clear();
    deck.shuffle();
    while (_videoPokerHand._hand.size() != 5) //makes a new hand and reshuffles the deck
    {
        _videoPokerHand.addCard(deck.draw());
    }
}
std::string VideoPokerGame::drawHand(int i)
{
    std::string card = _videoPokerHand.handToString(i); //converts a card into a string and return it
    return card;
}
std::string VideoPokerGame::checkForWin()
{
    _videoPokerHand.checkHand(); //checks to see if the player won anything
    std::string result = outcome(_videoPokerHand); //pays out the money if they did win
    return result;
}

void VideoPokerGame::initPayouts() // fills the payout map with payouts and amount won
{
    std::pair<payOuts, int> pair(payOuts::PAIR, 1);
    std::pair<payOuts, int> twoPair(payOuts::TWOPAIR, 2);
    std::pair<payOuts, int> threeOfAKind(payOuts::THREEOAKIND, 3);
    std::pair<payOuts, int> straight(payOuts::STRAIGHT, 4);
    std::pair<payOuts, int> flush(payOuts::FLUSH, 6);
    std::pair<payOuts, int> fullHouse(payOuts::FULLHOUSE, 9);
    std::pair<payOuts, int> fourOfAKind(payOuts::FOUROFAKIND, 25);
    std::pair<payOuts, int> straightFlush(payOuts::STRAIGHTFLUSH, 50);
    std::pair<payOuts, int> royalFlush(payOuts::ROYALFLUSH, 250);
    _payout.insert(pair);
    _payout.insert(twoPair);
    _payout.insert(threeOfAKind);
    _payout.insert(straight);
    _payout.insert(flush);
    _payout.insert(fullHouse);
    _payout.insert(fourOfAKind);
    _payout.insert(straightFlush);
    _payout.insert(royalFlush);
}
void VideoPokerGame::drawNewCards(int i) //replace the cards that the player wanted
{
    _videoPokerHand.redraw(i, deck.draw()); //redraws any cards the player wanted by checking the bool
}
std::string VideoPokerGame::outcome(Hand hand)
{
    std::string outcome;
    auto end = hand._payoutHands.end();
    end--;
    for (auto h : hand._payoutHands) //checks the hands for a win
    {
        auto p = _payout.begin();
        if (h.second == true)
        {
            while (p->first != h.first) // prints out how many credits you won
            p++;
            outcome.append(" You won ");
            outcome.append(std::to_string(p->second));
            outcome.append(" credits!\n");
            credits = credits + p->second;
            break;
        }
        else if (h.first == end->first) // if there is no matches
        {
            outcome.append("I'm sorry you lost, please try again!\n");
        }
    }
    return outcome;
}
