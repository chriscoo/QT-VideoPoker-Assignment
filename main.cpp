//
//  Created by Chris Arsenault on 2016-05-13.
//  Copyright © 2016 Chris Arsenault. All rights reserved.
//

#include "Controller/mainview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainView w;
    w.show();

    return a.exec();
}
