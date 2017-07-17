#include "mainwindow.h"
#include <QApplication>
#include <challengewindow.h>
#include<aboutwindow.h>
#include<passwindow.h>
#include<gameoverwindow.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PassWindow p;
    ChallengeWindow c;
    MainWindow m;
    AboutWindow ab;
    GameOverWindow gg;
    m.show();
    QObject::connect(&m,SIGNAL(showPassWindow(int,int)),&p,SLOT(receiveAll(int,int)));
    QObject::connect(&m,SIGNAL(showChallengeWindow()),&c,SLOT(receivemain()));
    QObject::connect(&c,SIGNAL(showPassWindow(int,int)),&p,SLOT(receiveAll(int,int)));
    QObject::connect(&c,SIGNAL(showMainWindow()),&m,SLOT(receivelogin()));
    QObject::connect(&p,SIGNAL(showMainWindow()),&m,SLOT(receivelogin()));
    QObject::connect(&m,SIGNAL(showAboutWindow()),&ab,SLOT(receiveMain()));
    QObject::connect(&ab,SIGNAL(ShowMain()),&m,SLOT(receivelogin()));
    QObject::connect(&p,SIGNAL(showGameOver(int,int,int,int)),&gg,SLOT(receivePass(int,int,int,int)));
    QObject::connect(&gg,SIGNAL(BackHome()),&m,SLOT(receivelogin()));
    return a.exec();
}
