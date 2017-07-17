#include "aboutwindow.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(1000,500);
    button_AboutHome=new QPushButton(this);
    button_AboutHome->setGeometry(QRect(849,449,150,50));
    button_AboutHome->setIcon(QIcon(":/developer/media/developer/关卡选择后退键.png"));
    button_AboutHome->setIconSize(QSize(150,50));
    button_AboutHome->setFlat(true);
    connect(button_AboutHome,SIGNAL(clicked()),this,SLOT(showMain()));
}

AboutWindow::~AboutWindow()
{
    delete ui;
}
void AboutWindow::mousePressEvent (QMouseEvent *aboutMouse)
{
    last_about = aboutMouse->globalPos();
}
void AboutWindow:: mouseMoveEvent (QMouseEvent *aboutMouse)
{
    int dx = aboutMouse->globalX() - last_about.x();
    int dy = aboutMouse->globalY() - last_about.y();
    last_about = aboutMouse->globalPos();
    move(x()+dx,y()+dy);
}
void AboutWindow:: mouseReleaseEvent (QMouseEvent *aboutMouse)
{
    int dx = aboutMouse->globalX() - last_about.x();
    int dy = aboutMouse->globalY() - last_about.y();
    move(x()+dx, y()+dy);
}
void AboutWindow::showMain()
{

    this->close();
    emit ShowMain();
}
void AboutWindow::paintEvent(QPaintEvent *)
{
    QPixmap image(":/developer/media/developer/IMG_4541.png");
    QPainter painter(this);
    painter.drawPixmap(0,0,1000,500,image);
}
void AboutWindow::receiveMain()
{
    this->show();
}
