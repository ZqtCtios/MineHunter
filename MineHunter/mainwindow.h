#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMouseEvent>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void mousePressEvent (QMouseEvent *e);    //鼠标移动
    void mouseMoveEvent (QMouseEvent *e);    //鼠标释放
    void mouseReleaseEvent (QMouseEvent *e);
    void paintEvent(QPaintEvent *);
    //QPushButton *custButton(QString str,QString str1);
private:
    Ui::MainWindow *ui;
    QPushButton *button_PassWindow;
    QPushButton *button_Challenge;
    QPushButton *button_About;
    QPushButton *button_Close;
    QPoint last;
private slots:
    void ShowChallenge();
    void ShowAbout();
    void ShowPassWindow();
    void receivelogin();
signals:
    void showPassWindow(int g,int l);
    void showChallengeWindow();
    void showAboutWindow();
};

#endif // MAINWINDOW_H
