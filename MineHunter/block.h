
#include <QPushButton>
#include <QMouseEvent>
#include<QDebug>
class block : public QPushButton
{
    Q_OBJECT
public:
    explicit block(int i,int l,QWidget *parent = 0);//block构造函数 i为ID l为level

    void sweep();         //翻开当前block
    bool isMine(){ return num==9?true:false; }//判断是否是地雷
    void setMine(){ num = 9; }//设置当前格子为地雷
    void numIncrease(){ if(num!=9) num++; }//周围地雷数加一
    int index(){return id;}//返回block Id
    int isNum(){return num;}//判断是否为数字格
    bool isMarked(){ return marked ;}//是否被标记
    bool marked;
    void Marked();//标记
protected:
    void mousePressEvent(QMouseEvent *e);   //重定义鼠标事件，左键翻开block，右键标记(或取消已标记)block

signals:
    void expand(int);  //对当前block周围进行拓展的信号
    void testWin();  //测试是否获胜信号
    void lost();   //游戏失败信号

    void markIncrease(); //标记数目增加
    void markDecrease(); //标记数目减少

private:
    int num;  //若num为9则为雷，为0~8表示周围block的雷数
      //当前block是否被标记
    int id;   //当前block在雷区中的位置(范围是从左上角0到右下角的row*column)
    int level;//当前关卡

};


