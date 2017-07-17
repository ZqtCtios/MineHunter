#ifndef CHALLENGE_H
#define CHALLENGE_H

#include <QMainWindow>
#include <QPushButton>
#include <QMouseEvent>
#include <QWidget>
#include <QLCDNumber>
namespace Ui {
class ChallengeWindow;
}

class ChallengeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChallengeWindow(QWidget *parent = 0);
    ~ChallengeWindow();
    void mousePressEvent (QMouseEvent *challengeMouse);    //鼠标移动
    void mouseMoveEvent (QMouseEvent *challengeMouse);    //鼠标释放
    void mouseReleaseEvent (QMouseEvent *challengeMouse);
private:
    Ui::ChallengeWindow *ui;
    QPushButton *level_One;
    QPushButton *level_two;
    QPushButton *level_three;
    QPushButton *challengeButton_home;
    QPoint last_challenge;
    QPushButton *returnMain;
public slots:
    void showlevel1();
    void showlevel2();
    void showlevel3();
    void receivemain();
    void ShowMainWindow();
signals:
    void showPassWindow(int g, int l);
    void showMainWindow();
protected:
    void paintEvent(QPaintEvent *);
};

#endif // CHALLENGE_H
