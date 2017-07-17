#include "block.h"
#include <QString>
#include <QStyle>
#include <QIcon>
block::block(int i,int l, QWidget *parent):
    QPushButton(parent)
{
    id = i;
    num=0;
    marked = false;
    level=l;
    switch (l)
    {
        case 1:setFixedSize(40,40);setIconSize(QSize(37, 37));break;
        case 2:setFixedSize(30,30);setIconSize(QSize(27, 27));break;
        case 3:setFixedSize(25,25);setIconSize(QSize(22, 22));break;
    }

    switch(l)
    {
        case 1:setIcon(QIcon(":/level1/media/level1/brick.png"));break;
        case 2:setIcon(QIcon(":/level2/media/level2/normal.png"));break;
        case 3:setIcon(QIcon(":/level3/media/level3/brick.png"));break;
    }
    setCheckable(true);
}//构造函数


void block::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton && !marked)
    {
        if(num==9)
        {
            switch(level)
            {
                case 1:setIcon(QIcon(":/level1/media/level1/bomb.png"));break;
                case 2:setIcon(QIcon(":/level2/media/level2/bomb.png"));break;
                case 3:setIcon(QIcon(":/level3/media/level3/bomb.png"));break;
            }
            emit lost();
        }
        else
        {
            emit expand(id);
        }
    }

    if(e->button() == Qt::RightButton)
    {
       Marked();
    }
}//重定义鼠标事件

void block::sweep()
{
    if(!marked && this->isEnabled())
    {
        setDisabled(true);

        setIcon(QIcon(""));
        switch(num)
        {
              case 0 : break;
              case 1 : setText(QString::number(num)); setStyleSheet("color:green;font:12pt"); emit testWin();break;
              case 2 : setText(QString::number(num)); setStyleSheet("color:orange;font:12pt"); emit testWin();break;
              case 3 : setText(QString::number(num)); setStyleSheet("color:blue;font:12pt"); emit testWin();break;
              case 4 : setText(QString::number(num)); setStyleSheet("color:red;font:12pt"); emit testWin();break;
              case 5 : setText(QString::number(num)); setStyleSheet("color:red;font:12pt"); emit testWin();break;
              case 6 : setText(QString::number(num)); setStyleSheet("color:red;font:12pt"); emit testWin();break;
              case 7 : setText(QString::number(num)); setStyleSheet("color:red;font:12pt"); emit testWin();break;
              default : setText(QString::number(num)); setStyleSheet("color:red;font:12pt"); emit testWin();break;
        }
    }
}
//翻开格子
void block::Marked()
{
    if(marked)
    {
        marked = false;
        switch(level)
        {
            case 1:setIcon(QIcon(":/level1/media/level1/brick.png"));break;
            case 2:setIcon(QIcon(":/level2/media/level2/normal.png"));break;
            case 3:setIcon(QIcon(":/level3/media/level3/brick.png"));break;
        }
        emit markDecrease();
    }
    else
    {
        marked = true;
        setIcon(QIcon(":/level1/media/level1/flag.png"));
        emit markIncrease();
        emit testWin();
    }
}//标记格子



