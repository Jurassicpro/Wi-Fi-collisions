#include "window.h"
#include <QDebug>
#include <ctime> // для функции time()
#include <cstdlib> // для функций rand() и srand()
#include <string>
#include <iostream>
#include <QString>
#include <QPainter>

std::string getRandIconRouter();

//------------конструктор включает в себя установку начальных конфигураций----------------------------
Window::Window()
{

    setRenderHint(QPainter::Antialiasing);                      // сглаживание примитивов
    setCacheMode(QGraphicsView::CacheNone);                     // кэширование фона(отключение)
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);         // scroll (отключение ползунка)
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);       // scroll (отключение ползунка)

    setWindowTitle("Wi-Fi network");                            // устанавливаем заголовок для окна
    //setToolTip("QWidget");                                      // устанавливаем всплывающую подсказку для виджета
    setWindowIcon(QIcon(":/pics/pics/wifi_icon.png"));
    setFrameStyle(0);                                           // отключение фреймов/отступов?
    setSceneRect(0,0,1400,800);                                 // размер сцены / левый верхний угол 0;0 / правый нижний 800;800
    QPalette pal;
    pal.setColor(backgroundRole(), QColor(150,150,150));   //QColor(128,128,128) / Qt::darkGray
    setAutoFillBackground(false);                 //заполнять фон автоматически

    setPalette(pal);

    // установка фиксированного окна (вертикальное и горизонтальное направление)
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));

    setFixedSize(1400,800);                                      // фиксированный размер для виджета

    mScene.setItemIndexMethod(QGraphicsScene::NoIndex);         // установка способа индексации(отключение)
    // индексирование эффктивно для статичных сцен, где нет перемещения элементов

    setScene(&mScene);                                          // установка сцены

    //------инициализация элементов/методов----------
    mRouterVector = new std::vector <Router*>;

    _init_view_elements();
}
//-------функция инициализации----------------------------

void  Window::_init_view_elements()
{

    //----------------соединение сигналов с активацией роутера-------------------
    connect(&add_menu, &AddMenu::addRouterSignal, this, &Window::addRouter);
    connect(&add_menu, &AddMenu::addPCSignal, this, &Window::addPCfunc);
    connect(&add_menu, &AddMenu::changeChannel, this, &Window::changeChannel);
    connect(&add_menu, &AddMenu::OffOnRouterWave, this, &Window::OffOnWave);

    mScene.addWidget(&add_menu);
}


void Window::changeChannel()
{
    QString routerName = add_menu.getRouterNameForChangeChannel();       // получаем имя нужного роутера
    QString channelName = add_menu.getRouterChannelNameForChange();
    // ищем объект роутера по имени
    //qWarning() << "routerName == " << routerName;
    //qWarning() <<"mRouterVector->size() == " << mRouterVector->size();
    for(size_t i = 0; i < mRouterVector->size();i++)
    {
        if((((*(mRouterVector->begin()+i))->getName()) == routerName))
        {
            (*(mRouterVector->begin()+i))->setChannelName(channelName);
            break;
        }
    }
}

std::string getRandIconRouter()
{
    srand(static_cast<unsigned int>(time(0))); // устанавливаем значение системных часов в качестве стартового числа
    int randomValue = rand() % 5;

    switch(randomValue)
    {
        case 1: return ":/pics/pics/wifi-router.png";
        case 2: return ":/pics/pics/wifi-router2.png";
        case 3: return ":/pics/pics/wifi-router3.png";
        case 4: return ":/pics/pics/wifi-router4.png";
        case 5: return ":/pics/pics/wifi-router5.png";
    default:return ":/pics/pics/wifi-router.png";
    }

}
std::string getRandIconPC()
{
    srand(static_cast<unsigned int>(time(0))); // устанавливаем значение системных часов в качестве стартового числа
    int randomValue = rand() % 5;

    switch(randomValue)
    {
        case 1: return ":/pics_pc/pics/PC icons/pc1.png";
        case 2: return ":/pics_pc/pics/PC icons/pc2.png";
        case 3: return ":/pics_pc/pics/PC icons/pc3.png";
        case 4: return ":/pics_pc/pics/PC icons/pc4.png";
        case 5: return ":/pics_pc/pics/PC icons/pc5.png";
    default:return ":/pics_pc/pics/PC icons/pc5.png";
    }

}
//-----------------------создание ПК--------------------------------
PC * Window::addPC(Router *pRouter)
{
    qWarning() <<"mathafuakca";
    srand(static_cast<unsigned int>(time(0))); // устанавливаем значение системных часов в качестве стартового числа
    PC *mPC;
    mPC = new PC;
    mPC->setRouter(pRouter);
    mPC->setPos(rand() % 1000,rand() % 700);
    mPC->setGeometry(50,50);
    mPC->setName(add_menu.getPCName());
    mPC->setInternetSpeed(pRouter->getInternetSpeed());
    //drawLine(pRouter,mPC);
    char text[38];// = ":/pics/pics/wifi-router3.png";
    std::string texta = getRandIconPC();
    strcpy_s(text,texta.c_str());
    QString a(text);
    mPC->setImage(a);
    mPC->setPntRouterVector(mRouterVector);
    connect(mPC, &PC::PCMouseReleaseEvent, this, &Window::Routers_clicked);

    mScene.addItem(mPC);     // добавление ПК в сцену

    std::vector <PC*> *vec = (pRouter->getVectorPC());
    vec->push_back(mPC);
    return mPC;
}

void Window::addPCfunc()
{
    QString routerName = add_menu.getRouterNameFromBtn();       // получаем имя нужного роутера
    // ищем объект роутера по имени
    //qWarning() << "routerName == " << routerName;
    //qWarning() <<"mRouterVector->size() == " << mRouterVector->size();
    for(size_t i = 0; i < mRouterVector->size();i++)
    {
        if(((*(mRouterVector->begin()+i))->getName()) == routerName)
        {
            //qWarning() << "Найден";
            addPC((*(mRouterVector->begin()+i)));

            break;
        }
    }

}

//-------функция добавления роутера----------------------------
Router* Window::addRouter()
{
    srand(static_cast<unsigned int>(time(0))); // устанавливаем значение системных часов в качестве стартового числа
    Router *mRouters;
    mRouters = new Router;
    mRouters->setPos(rand() % 1000,rand() % 700);//rand() % 5;
    mRouters->setGeometry(50,50);
    mRouters->setName(add_menu.getRouterName());
    mRouters->setInternetSpeed(add_menu.getInternetSpeed());
    mRouters->setChannelName(add_menu.getRouterChannelName());
    char text[30];// = ":/pics/pics/wifi-router3.png";
    std::string texta = getRandIconRouter();
    strcpy_s(text,texta.c_str());
    QString a(text);
    mRouters->setImage(a);
    mRouters->setPntRouterVector(mRouterVector);
    connect(mRouters, &Router::RouterMouseReleaseEvent, this, &Window::Routers_clicked);

    // первый параметр - что связываем/какой объект класса              // один класс
    // второй параметр - какой сигнал                                   // один класс
    // третий параметр - связывание объекта/текущий класс       // другой класс
    // четверный параметр - указываем обработчик сигнала/слот   // другой класс
    mRouterVector->push_back(mRouters);
    mScene.addItem(mRouters);     // добавление роутера в сцену
    mRouters->setPrintWaveFlag(flagOnOffWave);
    add_menu.update();
    return mRouters;
}

void Window::OffOnWave()
{

    if(flagOnOffWave)
    {
        flagOnOffWave = false;
        qWarning() << "Wave OFF";
    }
    else
    {
        flagOnOffWave = true;
        qWarning() << "Wave ON";
    }

    for (size_t i = 0;i < mRouterVector->size(); i++)
        (*(mRouterVector->begin()+i))->setPrintWaveFlag(flagOnOffWave);

}


void Window::Routers_clicked(Qt::MouseButton aRouter)
{

    if(aRouter == Qt::RightButton)
    {
        //qWarning() <<sender();

        for(size_t i = 0; i < mRouterVector->size();i++)
        {
            if((*(mRouterVector->begin()+i)) == sender())
            {
                add_menu.deleteRouterName((*(mRouterVector->begin()+i))->getName());
                mRouterVector->erase(mRouterVector->begin()+i);               // удаление из вектора роутеров
            }
        }

        sender()->~QObject();

        //qWarning() << "mRouterA was removed" << aRouter;
        mScene.update();
    }
}


void Window::PC_clicked(Qt::MouseButton aPC)
{
    if(aPC == Qt::RightButton)
    {
        //qWarning() <<sender();

        for(size_t i = 0; i < mRouterVector->size();i++)
        {

            if((*(mRouterVector->begin()+i)) == sender())
            {
                add_menu.deleteRouterName((*(mRouterVector->begin()+i))->getName());
                add_menu.update();
                mRouterVector->erase(mRouterVector->begin()+i);               // удаление из вектора роутеров
            }
        }

        sender()->~QObject();

        //qWarning() << "mRouterA was removed" << aPC;
        mScene.update();

    }
}
