#include "addmenu.h"
#include <QAction>
#include <QPalette>
#include <QDebug>
#include <QLineF>
#include <QPainter>

AddMenu::AddMenu()
{
    //addButtonRouter();
    setGeometry(1100,0,400,800);
    setAutoFillBackground(false);
    QPalette pal;
    pal.setColor(backgroundRole(), Qt::lightGray);
    setAutoFillBackground(true);                 //заполнять фон автоматически

    setPalette(pal);
    _init_elements();

    //mScene.addLine(1100,265,1400,265);
}


AddMenu::~AddMenu()
{
    //delete nameRouterEdit;
}

void AddMenu::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //painter.setPen(QPen(Qt::black, 12, Qt::DashDotLine, Qt::RoundCap));
    painter.drawLine(0, 275, 300, 275);
    painter.drawLine(0, 470, 300, 470);
}
void AddMenu::_init_elements()
{
    addQuitButton();
    OffOnWaveBtn();
    addRouterFunc();
    addPCFunc();
    addBtnSpeed();
    addRouterChannelFunc();
    choiseRouterForPC();
    changeChannelBtn();
}

//----------------------кнопка выхода----------------------------------------
void AddMenu::addQuitButton()
{
    QPushButton *quitBtn = new QPushButton("Quit", this);                       // создаем новую кнопку
    quitBtn->setGeometry(125, 725, 75, 30);                                     // изменяем размеры кнопки в пикселях и помещаем на форму окна

    //quitBtn->
    connect(quitBtn, &QPushButton::clicked, this, &QApplication::quit);
    //quitBtn->setStyleSheet("background-color:white");
}

//---------------------------включение/отключение Wi-Fi волн-------------------
void AddMenu::OffOnWaveBtnAct()
{
    emit OffOnRouterWave();
}
void AddMenu::OffOnWaveBtn()
{
    QPushButton *waveBtn = new QPushButton(QIcon(":/pics/pics/wifi_icon.png"),"Off/On Wave",this);
    waveBtn->setGeometry(110, 675, 105, 30);
    connect(waveBtn, &QPushButton::clicked, this, &AddMenu::OffOnWaveBtnAct);
}

//------------------Получение последнего названия роутера--------------------
QString AddMenu::getPCName()
{
    return PCName;
}
//----------------вызов дополнительной функции, в качестве слота--------------------
void AddMenu::addPCAct()
{
    listRouterNameBtn = listRoutersBtn->text();
    if(listRouterNameBtn != "Select a router:")
    {
        namePC.push_back(namePCEdit->text());
        PCName = namePCEdit->text();
        emit addPCSignal(); //QPushButton
        namePCEdit->clear();
    }


}
//------------------------обработка кнопок по добавлению ПК------------------------
void AddMenu::addPCFunc()
{
    //------------строка "Введите имя роутера"-------------------------------------
    QLabel *labelPCName = new QLabel(this);
    labelPCName->setText("Enter the name of the PC:");
    labelPCName->setGeometry(80,550,150,30);

    namePCEdit = new QLineEdit(this);
    namePCEdit->setStyleSheet("background-color:white");
    namePCEdit->setGeometry(80,575,150,30);


    QPushButton *addPCBtn = new QPushButton("Add", this); // создаем новую кнопку
    addPCBtn->setGeometry(80, 625, 150, 30); // изменяем размеры кнопки в пикселях и помещаем на форму окна
    addPCBtn->setStyleSheet("background-color:lime");
    addPCBtn->setCursor(Qt::PointingHandCursor);
    connect(addPCBtn, &QPushButton::clicked, this, &AddMenu::addPCAct);


}

unsigned int AddMenu::getInternetSpeed()
{
    if(speedValueText == "256 Kbps")
        return 256;
    if(speedValueText == "512 Kbps")
        return 512;
    if(speedValueText == "1 Mbps")
        return 1000;
    if(speedValueText == "2 Mbps")
        return 2000;
    if(speedValueText == "4 Mbps")
        return 4000;
    if(speedValueText == "8 Mbps")
        return 8000;
    else
    //if(speedValueText == "10 Mbps")
        return 10000;
}


//------------------Получение последнего названия роутера--------------------
QString AddMenu::getRouterName()
{
    return RouterName;
}

QString AddMenu::getRouterChannelName()
{
    return channelName;
}

//-----------------------------обработка сигналов для создания роутера-------------------------
void AddMenu::addRouterAct()
{


    channelName = channelsBtn->text();
    speedValueText =speedInternetBtn->text();
    // чтобы нельзя было создать без номера канала
    if((channelName != "Select a channel:") && (speedValueText != "Select a speed Internet"))
    {
        nameRouter.push_back(nameRouterEdit->text());

        // добавление в список роутеров + сразу соединение со слотом
        routersVector.push_back(pMenuRouters->addAction(nameRouterEdit->text()));
        routersVectorForChangeChannel.push_back(pMenuRoutersChangeChannel->addAction(nameRouterEdit->text()));


        connect(routersVector[countRouter],&QAction::triggered,this,&AddMenu::BtnMenuChangeRouterText);
        connect(routersVectorForChangeChannel[countRouter],&QAction::triggered,this,&AddMenu::BtnMenuChangeRouterChannelText);

        RouterName = nameRouter[countRouter++];
        emit addRouterSignal(); //QPushButton
    }

    // очистка поля для названия роутера
    nameRouterEdit->clear();
    iterRouter++;

}
//---------------------создание кнопок для создания роутера-----------------------------------
void AddMenu::addRouterFunc()
{
    //------------строка "Введите имя роутера"-------------------------------------
    QLabel *labelRouterName = new QLabel(this);
    labelRouterName->setText("Enter the name of the router:");
    labelRouterName->setGeometry(80,150,150,30);

    nameRouterEdit = new QLineEdit(this);
    nameRouterEdit->setStyleSheet("background-color:white");
    nameRouterEdit->setGeometry(80,175,150,30);


    QPushButton *addRouterBtn = new QPushButton("Add", this); // создаем новую кнопку
    addRouterBtn->setGeometry(80, 225, 150, 30); // изменяем размеры кнопки в пикселях и помещаем на форму окна
    addRouterBtn->setStyleSheet("background-color:lime");
    addRouterBtn->setCursor(Qt::PointingHandCursor);
    connect(addRouterBtn, &QPushButton::clicked, this, &AddMenu::addRouterAct);


}

//---------------------------выбор скорости интернета для роутера---------------------------
void AddMenu::addBtnSpeed()
{
    QLabel *labelSpeed = new QLabel(this);
    labelSpeed->setText("Select a speed Internet:");
    labelSpeed->setGeometry(80,85,150,30);

    speedInternetBtn = new QPushButton("Select a speed Internet:",this);
    speedInternetBtn->setGeometry(80,110,150,30);
    speedInternetBtn->clicked();


    QMenu *pMenuSpeed = new QMenu(speedInternetBtn);
    pMenuSpeed->setAutoFillBackground(false);

    pActSpeed[0] = pMenuSpeed->addAction("256 Kbps");
    pActSpeed[1] = pMenuSpeed->addAction("512 Kbps");
    pActSpeed[2] = pMenuSpeed->addAction("1 Mbps");
    pActSpeed[3] = pMenuSpeed->addAction("2 Mbps");
    pActSpeed[4] = pMenuSpeed->addAction("4 Mbps");
    pActSpeed[5] = pMenuSpeed->addAction("8 Mbps");
    pActSpeed[6] = pMenuSpeed->addAction("10 Mbps");

    for (int i = 0; i <= 6; i++)
        connect(pActSpeed[i],&QAction::triggered,this,&AddMenu::BtnMenuChangeSpeedText);

    speedInternetBtn->setMenu(pMenuSpeed);
    speedInternetBtn->setStyleSheet("background-color:white");
    speedInternetBtn->setCursor(Qt::PointingHandCursor);
}
void AddMenu::BtnMenuChangeSpeedText()
{
    for(int i = 0; i <= 6;i++)
        if(pActSpeed[i] ==  sender())
            speedInternetBtn->setText(pActSpeed[i]->text());
    //qWarning()<<"works2";
}

void AddMenu::addRouterChannelFunc()
{
    QLabel *labelChannel = new QLabel(this);
    labelChannel->setText("Select a channel:");
    labelChannel->setGeometry(80,25,150,30);

    channelsBtn = new QPushButton("Select a channel:",this);
    channelsBtn->setGeometry(80,50,150,30);
    channelsBtn->clicked();



    QMenu *pMenuChannel = new QMenu(channelsBtn);
    pMenuChannel->setAutoFillBackground(false);
    pActChannel[0] = pMenuChannel->addAction("2,412 GHz");
    pActChannel[1] = pMenuChannel->addAction("2,417 GHz");
    pActChannel[2] = pMenuChannel->addAction("2,422 GHz");
    pActChannel[3] = pMenuChannel->addAction("2,427 GHz");
    pActChannel[4] = pMenuChannel->addAction("2,432 GHz");
    pActChannel[5] = pMenuChannel->addAction("2,437 GHz");
    pActChannel[6] = pMenuChannel->addAction("2,442 GHz");
    pActChannel[7] = pMenuChannel->addAction("2,447 GHz");
    pActChannel[8] = pMenuChannel->addAction("2,452 GHz");
    pActChannel[9] = pMenuChannel->addAction("2,457 GHz");
    pActChannel[10] = pMenuChannel->addAction("2,462 GHz");
    pActChannel[11] = pMenuChannel->addAction("2,467 GHz");
    pActChannel[12] = pMenuChannel->addAction("2,472 GHz");
    pActChannel[13] = pMenuChannel->addAction("2,484 GHz");


    for (int i = 0; i <= 13; i++)
        connect(pActChannel[i],&QAction::triggered,this,&AddMenu::BtnMenuChangeChannelText);

    pMenuChannel->setCursor(Qt::PointingHandCursor);

    channelsBtn->setMenu(pMenuChannel);
    channelsBtn->setStyleSheet("background-color:white");
    channelsBtn->setCursor(Qt::PointingHandCursor);

}

void AddMenu::BtnMenuChangeChannelText()
{
    for(int i = 0; i <= 13;i++)
    {
        if(pActChannel[i] ==  sender())
            channelsBtn->setText(pActChannel[i]->text());
        if(pActChannelForChange[i] ==  sender())
            routersBtnChannel->setText(pActChannelForChange[i]->text());
    }

}



void AddMenu::choiseRouterForPC()
{
    QLabel *labelChannel = new QLabel(this);
    labelChannel->setText("Select a router:");
    labelChannel->setGeometry(80,490,150,30);

    listRoutersBtn = new QPushButton("Select a router:",this);
    listRoutersBtn->setGeometry(80,515,150,30);
    listRoutersBtn->clicked();

    pMenuRouters = new QMenu(listRoutersBtn);
    pMenuRouters->setAutoFillBackground(false);

    pMenuRouters->setCursor(Qt::PointingHandCursor);

    listRoutersBtn->setMenu(pMenuRouters);
    listRoutersBtn->setStyleSheet("background-color:white");
    listRoutersBtn->setCursor(Qt::PointingHandCursor);

}


void AddMenu::BtnMenuChangeRouterText()
{
    for(int i = 0; i <= countRouter;i++)
        if(routersVector[i] ==  sender())
            listRoutersBtn->setText(routersVector[i]->text());

}

void AddMenu::BtnMenuChangeRouterChannelText()
{
    for(int i = 0; i <= countRouter;i++)
    {
        if(routersVectorForChangeChannel[i] ==  sender())
            listRoutersBtnChannel->setText(routersVectorForChangeChannel[i]->text());
    }

}

QString AddMenu::getRouterNameFromBtn()
{
    return listRoutersBtn->text();
}



void AddMenu::deleteRouterName(QString aName)
{
    for (int i = 0; i < countRouter; i++)
    {
        if(routersVector[i]->text() == aName)
        {
            pMenuRouters->removeAction(routersVector[i]);
            routersVector.erase(routersVector.begin()+i);
            nameRouter.erase(nameRouter.begin()+i);
            countRouter--;

        }

    }
}

void AddMenu::changeChannelBtn()
{
    QLabel *labelChannel = new QLabel(this);
    labelChannel->setText("Select a router:");
    labelChannel->setGeometry(80,285,150,30);

    listRoutersBtnChannel = new QPushButton("Select a router:",this);
    listRoutersBtnChannel->setGeometry(80,310,150,30);
    listRoutersBtnChannel->clicked();

    QLabel *labelChannel2 = new QLabel(this);
    labelChannel2->setText("Select a channel:");
    labelChannel2->setGeometry(80,345,150,30);

    pMenuRoutersChangeChannel = new QMenu(listRoutersBtnChannel);
    pMenuRoutersChangeChannel->setAutoFillBackground(false);

    routersBtnChannel = new QPushButton("Select a channel:",this);
    routersBtnChannel->setGeometry(80,370,150,30);
    routersBtnChannel->clicked();

    QMenu *pMenuChannel = new QMenu(routersBtnChannel);
    pMenuChannel->setAutoFillBackground(false);
    pActChannelForChange[0] = pMenuChannel->addAction("2,412 GHz");
    pActChannelForChange[1] = pMenuChannel->addAction("2,417 GHz");
    pActChannelForChange[2] = pMenuChannel->addAction("2,422 GHz");
    pActChannelForChange[3] = pMenuChannel->addAction("2,427 GHz");
    pActChannelForChange[4] = pMenuChannel->addAction("2,432 GHz");
    pActChannelForChange[5] = pMenuChannel->addAction("2,437 GHz");
    pActChannelForChange[6] = pMenuChannel->addAction("2,442 GHz");
    pActChannelForChange[7] = pMenuChannel->addAction("2,447 GHz");
    pActChannelForChange[8] = pMenuChannel->addAction("2,452 GHz");
    pActChannelForChange[9] = pMenuChannel->addAction("2,457 GHz");
    pActChannelForChange[10] = pMenuChannel->addAction("2,462 GHz");
    pActChannelForChange[11] = pMenuChannel->addAction("2,467 GHz");
    pActChannelForChange[12] = pMenuChannel->addAction("2,472 GHz");
    pActChannelForChange[13] = pMenuChannel->addAction("2,484 GHz");


    for (int i = 0; i <= 13; i++)
        connect(pActChannelForChange[i],&QAction::triggered,this,&AddMenu::BtnMenuChangeChannelText);

    pMenuRoutersChangeChannel->setCursor(Qt::PointingHandCursor);

    listRoutersBtnChannel->setMenu(pMenuRoutersChangeChannel);
    listRoutersBtnChannel->setStyleSheet("background-color:white");
    listRoutersBtnChannel->setCursor(Qt::PointingHandCursor);

    routersBtnChannel->setMenu(pMenuChannel);
    routersBtnChannel->setStyleSheet("background-color:white");
    routersBtnChannel->setCursor(Qt::PointingHandCursor);


    QPushButton *ChangeRouterChannelBtn = new QPushButton("Change channel", this); // создаем новую кнопку
    ChangeRouterChannelBtn->setGeometry(80, 410, 150, 30); // изменяем размеры кнопки в пикселях и помещаем на форму окна
    ChangeRouterChannelBtn->setStyleSheet("background-color:orange");
    ChangeRouterChannelBtn->setCursor(Qt::PointingHandCursor);
    connect(ChangeRouterChannelBtn, &QPushButton::clicked, this, &AddMenu::changeRouterChannelAct);
}

//----------------вызов дополнительной функции, в качестве слота--------------------
void AddMenu::changeRouterChannelAct()//151
{

    if((listRoutersBtnChannel->text() != "Select a router:") && (routersBtnChannel->text() != "Select a channel:"))
    {
        channelNameForChange = routersBtnChannel->text();       // присваимваем номер канала
        RouterNameForChangeChannel = listRoutersBtnChannel->text();
        emit changeChannel(); //QPushButton
        listRoutersBtnChannel->setText("Select a router:");
        routersBtnChannel->setText("Select a channel:");
    }


}
QString AddMenu::getRouterChannelNameForChange()
{
    return routersBtnChannel->text();
}

QString AddMenu::getRouterNameForChangeChannel()
{
    return listRoutersBtnChannel->text();
}
