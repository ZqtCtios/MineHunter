    #ifndef PASSWINDOW_H
#define PASSWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QLCDNumber>
#include<QPushButton>
#include<QDesktopWidget>
#include<QMessageBox>
#include<QDebug>
#include<block.h>
#include<QTime>
#include<QTimer>
#include<QtCore>
#include<string.h>
//游戏界面
namespace Ui {
class PassWindow;
}

class PassWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PassWindow(QWidget *parent = 0);
    QVector<block *> Around(block *);
    ~PassWindow();
    void showLcdTime();//显示时间
    void showLcdScore();//显示分数
    void showGame();//显示游戏布局
    void showHomeButton();//显示返回主界面按钮
    void setGame(int gamemode,int level);//设置游戏信息
    void showLcdCount();
    void startMine();//棋局确定
    void BackUp();
    //QPushButton *button_close;//关闭按钮
    QPushButton *button_home;//返回主界面按钮
    QLCDNumber *lcdTime;//时间显示LCD
    QLCDNumber *lcdScore;//分数显示LCD
    QVector<block *> base;  //保存所有block的指针
    block * tempBlock; //构建雷区时使用的临时指针
    QVector<block *> mine;//保存所有为雷的block的指针
    QLCDNumber *lcdCount;//当前剩余雷数
    int markedCount;// 未被标记的雷数
    int r;//行数
    int c;//列数
    int n;//地雷总数
    int mineXY;
    int mineSize;
    int gamemode;//游戏模式
    int level;//当前关卡；
    int removeTime;//撤销次数
    int score;//当前分数
    bool win;
    bool isClickdeMine;
    int Start;
    int End;
    int time;
    int lastTime;

private:

    Ui::PassWindow *ui;

public slots:
    void showHome();
    void receiveAll(int g, int l);
    void Expand(int x);    //用于自动展开周围的block
    void TestWin();  //测试是否获胜
    void Lost();   //触发游戏失败
    void LcdIncrease(){emit LCDIn(--markedCount);}
    void LcdDecrease(){emit LCDDe(++markedCount);}
    void timerUpdate();
    void remove();
    //void Test(int id);
signals:
    void LCDIn(int);
    void LCDDe(int);
    void showMainWindow();
    void showGameOver(int isWin,int s,int t,int g);
};

#endif // PASSWINDOW_H
