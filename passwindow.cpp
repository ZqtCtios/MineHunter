#include "passwindow.h"
#include "ui_passwindow.h"



PassWindow::PassWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PassWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    lcdTime=new QLCDNumber(this);
    lcdScore=new QLCDNumber(this);
    lcdCount=new QLCDNumber(this);
    button_home=new QPushButton(this);
    connect(button_home,SIGNAL(clicked()),this,SLOT(showHome()));
    removeTime=0;
    lastTime=0;
    r=c=0;
    score=0;
    connect(this,SIGNAL(LCDIn(int)),lcdCount,SLOT(display(int)));
    connect(this,SIGNAL(LCDDe(int)),lcdCount,SLOT(display(int)));
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);
     this->setObjectName("PassWindow");
}

PassWindow::~PassWindow()
{
    base.clear();
    delete tempBlock;
    delete ui;
}


void PassWindow::setGame(int gamemode, int level)
{

    this->gamemode=gamemode;
    this->level=level;
    if (gamemode==1)
    switch(level)
    {
        case 1:score=3000;break;
        case 2:score+=3000;break;
        case 3:score+=3000;break;
    }
    if (gamemode==2) score=0;
    switch(level)
    {
        case 1:r=c=8;n=8;removeTime=1;mineSize=40;mineXY=40;break;
        case 2:r=c=18;n=60;removeTime+=2;mineSize=30;mineXY=30;break;
        case 3:r=c=28;n=150;removeTime+=3;mineSize=25;mineXY=50;break;
    }
    switch (level)
    {
        case 1:this->setFixedSize(600,400);break;
        case 2:this->setFixedSize(900,600);break;
        case 3:this->setFixedSize(1200,800);break;
    }
    switch (level)
    {
        case 1:this->setStyleSheet("#PassWindow{background-image:url(:/level1/media/level1/bg01.png);}");break;
        case 2:this->setStyleSheet("#PassWindow{background-image:url(:/level2/media/level2/bg01.png);}");break;
        case 3:this->setStyleSheet("#PassWindow{background-image:url(:/level3/media/level3/bg01.png);}");break;
    }
    this->markedCount=n;
    lcdCount->display(markedCount);
    QDesktopWidget *deskdop = QApplication::desktop();
    move((deskdop->width() - this->width())/2, (deskdop->height() - this->height())/2);
    showGame();

    showLcdTime();
    showLcdScore();
    showHomeButton();
    showLcdCount();
    startMine();
}

void PassWindow::showLcdTime()
{
    lcdTime->setStyleSheet("color:red");
    lcdTime->display(0000);
    switch(level)
    {
        case 1:lcdTime->setGeometry(440,160,120,60);break;
        case 2:lcdTime->setGeometry(660,180,165,75);break;
        case 3:lcdTime->setGeometry(850,250,250,100);break;
    }


}
void PassWindow::showLcdScore()
{
    lcdScore->setStyleSheet("color:red");
    lcdScore->display(score);
    switch(level)
    {
        case 1:lcdScore->setGeometry(440,60,120,60);break;
        case 2:lcdScore->setGeometry(660,60,165,75);break;
        case 3:lcdScore->setGeometry(850,100,250,100);break;
    }
}
void PassWindow::showLcdCount()
{
    lcdCount->setStyleSheet("color:red");
    lcdCount->display(markedCount);
    switch(level)
    {
        case 1:lcdCount->setGeometry(440,240,120,40);break;
        case 2:lcdCount->setGeometry(660,300,165,75);break;
        case 3:lcdCount->setGeometry(850,400,250,100);break;
    }
}

void PassWindow::showHomeButton()
{
    switch (level)
    {
        case 1:
        button_home->setIconSize(QSize(40,40));
        button_home->setIcon(QIcon(":/level1/media/level1/IMG_4506.png"));
        button_home->setGeometry(540-1,300+1,40,40);
        break;
        case 2:
        button_home->setIconSize(QSize(60,60));
        button_home->setIcon(QIcon(":/level2/media/level2/IMG_4506.png"));
        button_home->setGeometry(810,450,60,60);
        break;
        case 3:
        button_home->setIconSize(QSize(100,100));
        button_home->setIcon(QIcon(":/level3/media/level3/IMG_4506.png"));
        button_home->setGeometry(1050-1,600+3,100,100);
        break;
    }


}

void PassWindow::showGame()
{

   int x=mineXY;
   int y=mineXY;
   for (int i=0;i<r;i++)
   {
       for (int j=0;j<c;j++)
       {
           base[i*r+j]->setGeometry(QRect(x,y,mineSize,mineSize));
           x+=mineSize;
       }
       y+=mineSize;
       x=mineXY;

   }
}
void PassWindow::showHome()
{
    this->close();
    emit showMainWindow();
}
void PassWindow::receiveAll(int g, int l)
{

    for(int i=0;i<r*c;i++)
        delete base[i];
    base.clear();
     mine.erase(mine.begin(),mine.end());
    switch (l) {
    case 1:
        r=c=8;
        break;
    case 2:
        r=c=18;
        break;
    case 3:
        r=c=28;
        break;
    }

    for (int i=0;i<r*c;i++)
    {
        tempBlock=new block(i,l,this);
        base.append(tempBlock);
        connect(tempBlock,SIGNAL(expand(int)),this,SLOT(Expand(int)));
        connect(tempBlock,SIGNAL(testWin()),this,SLOT(TestWin()));
        connect(tempBlock,SIGNAL(lost()),this,SLOT(Lost()));
        connect(tempBlock,SIGNAL(markIncrease()),this,SLOT(LcdIncrease()));
        connect(tempBlock,SIGNAL(markDecrease()),this,SLOT(LcdDecrease()));
        //connect(tempBlock,SIGNAL(test(int)),this,SLOT(Test(int));
    }
    this->show();
    setGame(g,l);

}
void PassWindow::TestWin()
{
    win=true;

     for(int i=0;i<r*c;i++)   //若不是雷的都被翻开，则获胜
     {
         if(base[i]->isEnabled()&& !base[i]->isMine())
         {
             win=false;
             break;
         }
     }

     if(!win)    //若并没有全部翻开，但是凡是雷的都已经被标记，则也获胜
     {
         win=true;
         for(int i=0;i<base.count();i++)
         {
             if( base[i]->isEnabled() && ( (!base[i]->isMine()&&base[i]->isMarked()) || (base[i]->isMine() && !base[i]->isMarked()) ) )
             {
                 win=false;
                 break;
             }
         }
     }

     if(win)  //一旦获胜，就弹出对话框提示是否继续
     {
         if (gamemode==1&&level<3)
         {
            this->close();
             lastTime=End;
             receiveAll(gamemode,level+1);
         }
         else

         {
             this->close();
             emit showGameOver(1,score,End,gamemode);
         }
     }
}
void PassWindow::Expand(int x)
{
    if(!base[x]->isMine()&&base[x]->isEnabled())
        {
            base[x]->sweep();
            if(base[x]->isNum()==0)
            {
                foreach(tempBlock,Around(base[x]))
                {
                    if(tempBlock->isNum()==0)
                        Expand(tempBlock->index());
                    else
                        tempBlock->sweep();
                }
            }
            if(base[x]->isNum()!=0)
            {
                foreach(tempBlock,Around(base[x]))
                {
                    if(tempBlock->isNum()==0)
                        Expand(tempBlock->index());
                }
            }
        }
}


void PassWindow::Lost()
{
    isClickdeMine=1;
    if (removeTime==0||gamemode==2)
    {
    foreach(tempBlock,mine)
        {

                switch(level)
                {
                    case 1:tempBlock->setIcon(QIcon(":/level1/media/level1/bomb.png"));break;
                    case 2:tempBlock->setIcon(QIcon(":/level2/media/level2/bomb.png"));break;
                    case 3:tempBlock->setIcon(QIcon(":/level3/media/level3/bomb.png"));break;
                }
        }
    }
    if (gamemode==1)
    {
    QString string("剩余撤销次数");
    string+=QString::number(removeTime);
    string+="  是否撤销";
    if (removeTime>0)
    {
    QMessageBox::StandardButton rb = QMessageBox::information(this,"你点到雷啦!",string,QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);

    if(rb==QMessageBox::Yes)
    {
        remove();
        removeTime--;
    }
    else
    {
        this->close();
        emit showGameOver(0,score,End,gamemode);
    }
    } else
    {
        QMessageBox::StandardButton xb = QMessageBox::information(this,"游戏结束","撤销次数已经用完",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        if(xb==QMessageBox::Yes)
        {
            this->close();
            emit showGameOver(0,score,End,gamemode);
        }
        else
        {
            this->close();
            emit showGameOver(0,score,End,gamemode);
        }
    }
    }
    else {
        this->close();
        emit showGameOver(0,score,End,gamemode);
    }

}
void PassWindow::timerUpdate()
{
    QTime timeEnd = QTime::currentTime();
    End = timeEnd.minute()*60+timeEnd.second()-Start;
    End+=lastTime;
    lcdTime->display(End);
    if (gamemode==1)
    {
        switch(level)
        {
            case 1:score-=50;
            case 2:score-=15;
            case 3:score-=5;
        }
        if (score<0)score=0;
        lcdScore->display(score);
    }
}
void PassWindow::startMine()
{
    QTime time = QTime::currentTime();
        time = QTime::currentTime();
        qsrand(time.second());
        int temp = 0;
        for(int i=0; i<n ; i++)
        {

            temp = qrand()%(r*c);
            if(!base[temp]->isMine())
            {
                base[temp]->setMine();
                mine.append(base[temp]);
            }
            else
            {
                i--;
                continue;
            }
            foreach(tempBlock,Around(base[temp]))
            {
                tempBlock->numIncrease();
            }

        }

        QTime timeStart = QTime::currentTime();
        Start = timeStart.minute()*60+timeStart.second();

}


QVector<block *> PassWindow::Around(block * blo)
{
    int x = blo->index();
    QVector<block *> around;

    if(x < c)     //UP
    {
        if(x == 0)
        {
            around.append(base[x+1]);
            around.append(base[x+c]);
            around.append(base[x+c+1]);
            return around;
        }
        else if(x == c-1)
        {
            around.append(base[x-1]);
            around.append(base[x+c]);
            around.append(base[x+c-1]);
            return around;
        }
        else
        {
            around.append(base[x+1]);
            around.append(base[x-1]);
            around.append(base[x+c]);
            around.append(base[x+c+1]);
            around.append(base[x+c-1]);
            return around;
        }
    }else if(x >= (r-1)*c)  //DOWN
    {
        if(x == (r-1)*c)
        {
            around.append(base[x-c]);
            around.append(base[x+1]);
            around.append(base[x-c+1]);
            return around;
        }
        else if (x == r * c -1)
        {
            around.append(base[x-1]);
            around.append(base[x-c]);
            around.append(base[x-c-1]);
            return around;
        }
        else
        {
            around.append(base[x+1]);
            around.append(base[x-1]);
            around.append(base[x-c]);
            around.append(base[x-c+1]);
            around.append(base[x-c-1]);
            return around;
        }

    }else if(x % c == 0 )   //LEFT except CONNER
    {
        around.append(base[x-c]);
        around.append(base[x-c+1]);
        around.append(base[x+1]);
        around.append(base[x+c+1]);
        around.append(base[x+c]);
        return around;
    }else if(x % c == c -1 )   //RIGHT except CONNER
    {
        around.append(base[x-c]);
        around.append(base[x-c-1]);
        around.append(base[x-1]);
        around.append(base[x+c-1]);
        around.append(base[x+c]);
        return around;
    }else                              // CENTER
    {
        around.append(base[x-c]);
        around.append(base[x-c+1]);
        around.append(base[x+1]);
        around.append(base[x+c+1]);
        around.append(base[x+c]);
        around.append(base[x-c-1]);
        around.append(base[x-1]);
        around.append(base[x+c-1]);
        return around;
    }
}
void PassWindow::remove()
{
    if (removeTime>0)
        {
    if (isClickdeMine)
        foreach (tempBlock, mine)
        {
           tempBlock->Marked();
           tempBlock->Marked();
        }
    }

}
