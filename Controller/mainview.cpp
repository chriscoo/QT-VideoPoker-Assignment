//
//  MAINVIEW.cpp
//
//
//  Created by Chris Arsenault on 2016-06-03.
//  Copyright © 2016 Chris Arsenault. All rights reserved.
//

#include "mainview.h"
#include "ui_mainview.h"
#include "../Model/videopokergame.h"
#include "../Model/Hand.h"

#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QString>
#include <Qspaceritem>
#include <QLabel>
#include <memory>
#include <QSignalMapper>



MainView::MainView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainView)
{

        ui->setupUi(this);
    ui->setupUi(this);
    this->setStyleSheet("background-color:rgb(0, 85, 0);");


     game = std::unique_ptr<VideoPokerGame>(new VideoPokerGame());

    auto vlMain = new QVBoxLayout(ui->centralWidget);
    auto hlMain = new QHBoxLayout();
    auto hlLogo = new QHBoxLayout();
    auto glCards = new QGridLayout();
    auto hlHand = new QHBoxLayout();

    _lblJackLogo = new QLabel();
    _lblJackLogo->setMinimumSize(600,100);
    _lblJackLogo->setMaximumSize(600,100);
    _lblJackLogo->setStyleSheet("border-image: url(:/photo/Media/banner.png);");


    QSpacerItem *spacer1 = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Fixed);
    QSpacerItem *spacer2 = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Fixed);
    hlLogo->addSpacerItem(spacer1);
    hlLogo->addWidget(_lblJackLogo); // <-spacer--logo--spacer->
    hlLogo->addSpacerItem(spacer2);
    vlMain->addLayout(hlLogo);
    _lblpayouts = new QLabel();
    _lblpayouts->setMaximumSize(400,350);
    _lblpayouts->setMinimumSize(400,350);
    _lblpayouts->setStyleSheet("border-image: url(:/photo/Media/paysheet1.png)"); // adds payout image to payput table label
    QSpacerItem *spacer3 = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Fixed);
    QSpacerItem *spacer4 = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Fixed);
    hlMain->addSpacerItem(spacer3);
    hlMain->addWidget(_lblpayouts); // <-spacer--payoutTable--spacer->
    hlMain->addSpacerItem(spacer4);
    vlMain->addLayout(hlMain); // adds score layout to the main layout
    QSignalMapper * signalMapper = new QSignalMapper(this); // creates a Qsignal Mapper to the cards
    auto mapSignal = static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map);
    QFont font;
    font.setBold(true);
    font.setPixelSize(10);
    for(int i = 0; i < 5; i++)
    {
        auto btn = new QPushButton();
        btn->setFont(font);
        btn->setMaximumSize(80,160);
        btn->setMinimumSize(80,160);
        btn->setEnabled(false);
        btn->setStyleSheet("border-image: url(:/photo/Media/cardback.png)"); // sets nbcc cardback image;
        glCards->addWidget(btn, 0, i);
        connect(btn, &QPushButton::clicked, signalMapper, mapSignal);
        signalMapper->setMapping(btn, i);
        _hand.push_back(btn);
    }

    vlMain->addLayout(glCards);// adds the card layout to the main layout


    //connects signal mapper to on card click
    connect(signalMapper,
            static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped),
            this, &MainView::toggleCard);
    _btnDraw = new QPushButton();
    _btnDraw->setText(QString("Draw"));
    _btnDraw->setMaximumSize(80,50);
    _btnDraw->setEnabled(false);
    connect(_btnDraw, &QPushButton::clicked, this, &MainView::DrawCards); // connects button to the draw new card
    _btnDraw->setStyleSheet("background-color: red");
    _btnDeal = new QPushButton();
    _btnDeal->setText(QString("Deal"));
    _btnDeal->setMaximumSize(80,50);
    connect(_btnDeal, &QPushButton::clicked, this, &MainView::newHand); // connects button to the deal new hand
    _btnDeal->setStyleSheet("background-color: red");


    // adds buttons to hlbutton layout
    hlHand->addWidget(_btnDraw);
    hlHand->addWidget(_btnDeal);
    QSpacerItem *spacer7 = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Fixed);
    hlHand->addSpacerItem(spacer7);
    vlMain->addLayout(hlHand);
    for(int i = 0; i < 5;i++) // makes the cards
    {
        _selected.push_back(false);
    }

}

MainView::~MainView()
{
    delete ui;
}



void MainView::toggleCard(int i)  //changes from card back to front and front to back
{
    if(_selected.at(i) == false)
    {
         _hand.at(i)->setStyleSheet("border-image: url(:/photo/Media/cardfrontHold.png)");
         _selected.at(i) = true;
    }
    else
    {
        _hand.at(i)->setStyleSheet("border-image: url(:/photo/Media/cardfront.png)");
        _selected.at(i) = false;
    }
}
void MainView::DrawCards() // draws new cards
{
    for(int i = 0; i < 5;i++)
    {
        _hand.at(i)->setEnabled(false);
        if( _selected.at(i) == false)
        {
            game->drawNewCards(i);
        }
    }
    _btnDraw->setEnabled(false);
    _btnDeal->setEnabled(true);
    for(int i = 0; i < 5;i++) // resets selected cards
    {
        _selected.at(i) = false;
    }
    showHand();
    checkHand();
}
void MainView::newHand() // deals a new hand
{
    for(int i = 0; i < 5;i++)
    {
         _hand.at(i)->setEnabled(true);
    }
    game->dealNewHand();
    _btnDraw->setEnabled(true);
    _btnDeal->setEnabled(false);
    showHand();
}
void MainView::showHand() // shows the cards to the viewer
{
    for(int i = 0; i < 5;i++)
    {
        _hand.at(i)->setStyleSheet("border-image: url(:/photo/Media/cardfront.png)");
        QString str = QString::fromStdString(game->drawHand(i));
         _hand.at(i)->setText(str);
    }
}
void MainView::checkHand() // asks the model for a win and print a message
{
    std::string outcome = game->checkForWin(); //gets the string from the model
    QString qOutcome = QString::fromStdString(outcome); //converts it into a qstring
    QMessageBox msgBox;
    msgBox.setText(qOutcome); //puts the Qstring into the message box
    msgBox.exec();
}
