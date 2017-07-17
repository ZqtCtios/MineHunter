#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QIcon>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//无边框
    this->setFixedSize(1000,500);

    /*----------------button--------------------*/
    button_PassWindow=new QPushButton("",this);
    button_PassWindow->setGeometry(QRect(600,175,275,75));
    button_PassWindow->setIcon(QIcon(":/mainwindow/media/mainwindow/01.png"));
    button_PassWindow->setIconSize(QSize(275,75));
    button_PassWindow->setFlat(true);
    connect(button_PassWindow,SIGNAL(clicked()),this,SLOT(ShowPassWindow()));
    //button_PassWindow
    button_Challenge=new QPushButton("",this);
    button_Challenge->setGeometry(QRect(600,275,275,75));
    button_Challenge->setIcon(QIcon(":/mainwindow/media/mainwindow/02.png"));
    button_Challenge->setIconSize(QSize(275,75));
    button_Challenge->setFlat(true);
    connect(button_Challenge,SIGNAL(clicked()),this,SLOT(ShowChallenge()));
    //button_Chanllge
    button_About=new QPushButton("",this);
    button_About->setGeometry(QRect(600,400,275,75));
    button_About->setIcon(QIcon(":/mainwindow/media/mainwindow/03.png"));
    button_About->setIconSize(QSize(275,75));
    button_About->setFlat(true);
    connect(button_About,SIGNAL(clicked()),this,SLOT(ShowAbout()));
    //button_About
    button_Close = new QPushButton("",this);
    button_Close->setGeometry(QRect(940,0,62,62));
    button_Close->setIcon(QIcon(":/mainwindow/media/mainwindow/主界面关闭.png"));
    button_Close->setIconSize(QSize(62,62));
    button_Close->setFlat(true);
    connect(button_Close,SIGNAL(clicked()),this,SLOT(close()));
    //buttom_close


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::ShowChallenge()
{
    this->hide();
    emit showChallengeWindow();
}
void MainWindow::ShowPassWindow()
{
   this->hide();
    emit showPassWindow(1,1);
}
void MainWindow::ShowAbout()
{
    this->hide();
    emit showAboutWindow();
}
void MainWindow::mousePressEvent (QMouseEvent *e)
{
    last = e->globalPos();
}
void MainWindow:: mouseMoveEvent (QMouseEvent *e)
{
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    last = e->globalPos();
    move(x()+dx,y()+dy);
}
void MainWindow:: mouseReleaseEvent (QMouseEvent *e)
{
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    move(x()+dx, y()+dy);
}
void MainWindow::receivelogin()
{
    this->show();
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPixmap image(":/mainwindow/media/mainwindow/主界面.png");
    QPainter painter(this);
    painter.drawPixmap(0,0,1000,500,image);
}

