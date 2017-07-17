#include "gameoverwindow.h"
#include "ui_gameoverwindow.h"

using namespace std;
GameOverWindow::GameOverWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameOverWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(1000,500);
    back=new QPushButton("",this);
    back->setGeometry(QRect(849,449,150,50));
    back->setIcon(QIcon(":/developer/media/developer/关卡选择后退键.png"));
    back->setIconSize(QSize(150,50));
    back->setFlat(true);
    label1=new QLabel("所用时间:",this);
    label2=new QLabel(this);
    label3=new QLabel("所得分数:",this);
    label4=new QLabel(this);
    label1->setGeometry(QRect(600,50,200,50));
    label2->setGeometry(QRect(800,50,200,50));
    label3->setGeometry(QRect(600,100,200,50));
    label4->setGeometry(QRect(800,100,200,50));
    this->setObjectName("GGWindow");
    label1->setStyleSheet("color:white;font:30pt");
    label2->setStyleSheet("color:white;font:30pt");
    label3->setStyleSheet("color:white;font:30pt");
    label4->setStyleSheet("color:white;font:30pt");
    connect(back,SIGNAL(clicked()),this,SLOT(backHome()));
}

GameOverWindow::~GameOverWindow()
{
    delete ui;
}
void GameOverWindow::receivePass(int iswin,int s, int t, int g)
{
    if(iswin==1)
    {
        setStyleSheet("#GGWindow{background-image:url(:/choice/media/tg.png);}");
        label1->setStyleSheet("color:red;font:30pt");
        label2->setStyleSheet("color:red;font:30pt");
        label3->setStyleSheet("color:red;font:30pt");
        label4->setStyleSheet("color:red;font:30pt");
        label1->setGeometry(QRect(100,50,200,50));
        label2->setGeometry(QRect(300,50,200,50));
        label3->setGeometry(QRect(100,100,200,50));
        label4->setGeometry(QRect(300,100,200,50));
    }
    else
    {
        setStyleSheet("#GGWindow{background-image:url(:/gameover/media/gameover/gg.png);}");

    }

    this->show();
    if (g==1)
    {
        label4->setText(QString::number(s));
        label2->setText(QString::number(t));

    }
    if (g==2)
    {
        label4->setText(QString::number(0));
        label2->setText(QString::number(t));

    }

}
void GameOverWindow::backHome()
{
    this->close();
    emit BackHome();
}
void GameOverWindow::mousePressEvent (QMouseEvent *aboutMouse)
{
    last_about = aboutMouse->globalPos();
}
void GameOverWindow:: mouseMoveEvent (QMouseEvent *aboutMouse)
{
    int dx = aboutMouse->globalX() - last_about.x();
    int dy = aboutMouse->globalY() - last_about.y();
    last_about = aboutMouse->globalPos();
    move(x()+dx,y()+dy);
}
void GameOverWindow:: mouseReleaseEvent (QMouseEvent *aboutMouse)
{
    int dx = aboutMouse->globalX() - last_about.x();
    int dy = aboutMouse->globalY() - last_about.y();
    move(x()+dx, y()+dy);
}


