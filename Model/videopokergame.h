//
//  VIDEOPOKERGAME.h
//
//
//  Created by Chris Arsenault on 2016-06-03.
//  Copyright © 2016 Chris Arsenault. All rights reserved.
//
#pragma once
#ifndef VIDEOPOKERGAME_H
#define VIDEOPOKERGAME_H

#include <unordered_map>
#include "Hand.h"
#include "Deck.h"
class Hand;
class Deck;
class VideoPokerGame
{
public:
    VideoPokerGame();
    ~VideoPokerGame();
    std::string drawHand(int i);
    void drawNewCards(int i);
    void dealNewHand();
    std::string checkForWin();

private:
    void initPayouts();
    std::string outcome(Hand hand);

private:
    int credits = 0;
    std::unordered_map<payOuts, int> _payout;
    std::vector<int> _choices;
    Deck deck;
    Hand _videoPokerHand;
};

#endif // VIDEOPOKERGAME_H


