#ifndef ABOUT_H
#define ABOUT_H

#include <QMainWindow>
#include <QMouseEvent>
#include<QDesktopWidget>
#include<QPushButton>
#include <QPainter>
#include <QIcon>
namespace Ui {
class AboutWindow;
}

class AboutWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AboutWindow(QWidget *parent = 0);
    ~AboutWindow();
    void mousePressEvent (QMouseEvent *aboutMouse);    //鼠标移动
    void mouseMoveEvent (QMouseEvent *aboutMouse);    //鼠标释放
    void mouseReleaseEvent (QMouseEvent *aboutMouse);
    void paintEvent(QPaintEvent *);
private:
    Ui::AboutWindow *ui;
    QPoint last_about;
    QPushButton *button_AboutHome;
private slots:
    void showMain();
    void receiveMain();
signals:
    void ShowMain();
};

#endif // ABOUT_H
