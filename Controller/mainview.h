//
//  MAINVIEW.h
//
//
//  Created by Chris Arsenault on 2016-06-03.
//  Copyright © 2016 Chris Arsenault. All rights reserved.
//


#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include <memory>
#include <QPushButton>
#include <Qlabel>
#include <vector>

class VideoPokerGame;

struct Card;
using cardptr = std::shared_ptr<Card>;

namespace Ui {
    class MainView;
}

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = 0);
    ~MainView();
    void showHand();
    void checkHand();

private slots:
    void DrawCards();
    void newHand();
    void MainView::toggleCard(int i);
private:

    std::unique_ptr<VideoPokerGame> game;

    std::vector<QPushButton*> _hand;
    std::vector<bool> _selected;

    QPushButton* _btnDraw;
    QPushButton* _btnDeal;

    QLabel* _lblJackLogo;
    QLabel* _lblpayouts;

private:
    Ui::MainView *ui;
};

#endif // MAINVIEW_H
