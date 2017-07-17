#include "challengewindow.h"
#include "ui_challengewindow.h"
#include<QPainter>
#include<QIcon>
#include<QPushButton>

ChallengeWindow::ChallengeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChallengeWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//无边框
    this->setFixedSize(1000,500);

    level_One=new QPushButton("",this);
    QIcon ico1(":/choice/media/choice/1.png");
    level_One->setIcon(ico1);
    level_One->setFlat(true);
    level_One->setIconSize(QSize(200,200));
    level_two=new QPushButton("",this);
    QIcon ico2(":/choice/media/choice/2.png");
    level_two->setIcon(ico2);
    level_two->setFlat(true);
    level_two->setIconSize(QSize(200,200));
    level_three=new QPushButton("",this);
    QIcon ico3(":/choice/media/choice/3.png");
    level_three->setIcon(ico3);
    level_three->setFlat(true);
    level_three->setIconSize(QSize(200,200));
    level_One->setGeometry(QRect(99,99,200,200));
    level_two->setGeometry(QRect(399,99,200,200));
    level_three->setGeometry(QRect(699,99,200,200));
    connect(level_One,SIGNAL(clicked()),this,SLOT(showlevel1()));
    connect(level_two,SIGNAL(clicked()),this,SLOT(showlevel2()));
    connect(level_three,SIGNAL(clicked()),this,SLOT(showlevel3()));
    challengeButton_home=new QPushButton("",this);
    challengeButton_home->setGeometry(QRect(749,403,150,50));
    challengeButton_home->setIcon(QIcon(":/choice/media/choice/关卡选择后退键.png"));
    challengeButton_home->setIconSize(QSize(150,50));
    challengeButton_home->setFlat(true);
    connect(challengeButton_home,SIGNAL(clicked()),this,SLOT(ShowMainWindow()));
}

ChallengeWindow::~ChallengeWindow()
{
    delete ui;
}
void ChallengeWindow::mousePressEvent (QMouseEvent *challengeMouse)
{
    last_challenge = challengeMouse->globalPos();
}
void ChallengeWindow:: mouseMoveEvent (QMouseEvent *challengeMouse)
{
    int dx = challengeMouse->globalX() - last_challenge.x();
    int dy = challengeMouse->globalY() - last_challenge.y();
    last_challenge = challengeMouse->globalPos();
    move(x()+dx,y()+dy);
}
void ChallengeWindow:: mouseReleaseEvent (QMouseEvent *challengeMouse)
{
    int dx = challengeMouse->globalX() - last_challenge.x();
    int dy = challengeMouse->globalY() - last_challenge.y();
    move(x()+dx, y()+dy);
}
void ChallengeWindow::showlevel1()
{
    this->hide();
    emit showPassWindow(2,1);

}
void ChallengeWindow::showlevel2()
{
    this->hide();
    emit showPassWindow(2,2);

}
void ChallengeWindow::showlevel3()
{
    this->hide();
    emit showPassWindow(2,3);
}
void ChallengeWindow::receivemain()
{
    this->show();
}
void ChallengeWindow::paintEvent(QPaintEvent *){
    QPixmap image(":/choice/media/choice/bg.png");
    QPainter painter(this);
    painter.drawPixmap(0,0,1000,500,image);
}
void ChallengeWindow::ShowMainWindow()
{
    this->close();
    emit showMainWindow();
}
