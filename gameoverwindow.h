#ifndef GAMEOVERWINDOW_H
#define GAMEOVERWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include<QDesktopWidget>
#include<QPushButton>
#include <QPainter>
#include <QIcon>
#include<QTextEdit>
#include<QString>
#include<QLabel>

namespace Ui {
class GameOverWindow;
}

class GameOverWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameOverWindow(QWidget *parent = 0);
    ~GameOverWindow();
    void mousePressEvent (QMouseEvent *aboutMouse);    //鼠标移动
    void mouseMoveEvent (QMouseEvent *aboutMouse);    //鼠标释放
    void mouseReleaseEvent (QMouseEvent *aboutMouse);


private:
    Ui::GameOverWindow *ui;
    QPushButton *back;
    QPoint last_about;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;
    int score;
    int time;
    int gamemode;
private slots:
    void receivePass(int iswin,int s,int t,int g);
    void backHome();
signals:
    void BackHome();

};

#endif // GAMEOVERWINDOW_H
