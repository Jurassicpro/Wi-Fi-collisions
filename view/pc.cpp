#include "pc.h"
#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QCursor>
#include <QGraphicsScene>
#include <string>
#include <cmath>
PC::PC()
{

    setAcceptHoverEvents(true);                                           // включаем методы обработки указателя
    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);            // включение только ЛКМ
}

PC::~PC()
{

}


//-----------------указываем область для перерисовки-----------------
QRectF PC::boundingRect() const
{


    return QRectF(0,0,mWidth,mHeight);                  // возвращаем размеры прямоугольника
}
void paintText(QPainter *painter)
{
    painter->rotate(45);
    painter->setPen(Qt::black);
    //painter->drawText(0,100,"nameThisPC");
    painter->rotate(-45);
}
//-----------------отрисовка-----------------------------------------
void PC::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    if(mHoverFlag){
        //painter->setBrush(Qt::green);                   // или QColor(255,0,0) / закраска полностю
        painter->setPen(Qt::blue);                      // или QColor(255,0,122)

    }


    QList<QGraphicsItem*> l = scene()->items();      // список всех графических объектов
    // справа получаем указатель на cписок всех объектов сцены (mScene)
    int minusSpeedCoef = 0;
    bool flagOutZone{true};
    foreach(QGraphicsItem *item,l)
    {
        if(item == this)
            continue;
        // если другой объект

        // collideWithPath  - с областью
        if(collidesWithItem(item))        // пересечение с item / другим обхектом
        {
            //painter->drawRoundedRect(0,0,mWidth, mHeight,5,5);
            painter->setBrush(Qt::red);
            item->update();                 // чтобы обновлялся сразу
        }
        if(item == pUseRouter)
        {
            RouterPnt = pUseRouter->pos()-this->pos();
            myPnt.setX(0);
            myPnt.setY(0);
            lineAngle.setPoints(RouterPnt,myPnt);
            RouterPnt.setX(RouterPnt.x() + 25);
            RouterPnt.setY(RouterPnt.y() + 25);
            myPnt.setX(25);
            myPnt.setY(25);

            lineCenter.setPoints(RouterPnt,myPnt);

            pntTextDist.setX((lineAngle.x1() + lineAngle.x2())/2+10);
            pntTextDist.setY((lineAngle.y1()+lineAngle.y2())/2-10);

            //int distancePntManh = (RouterPnt - myPnt).manhattanLength();
            distancePnt = sqrt(pow(abs(lineCenter.dx()),2) + pow(abs(lineCenter.dy()),2));


            //----------------установка расстояний----------------------------------------
            if(distancePnt < 200)
                flag = 1;
            else if(distancePnt <300)
                flag = 2;
            else
                flag = 3;

            //---------------установка цвета в зависимости от расстояния------------------
            if(!mHoverFlag || mIsMoving)
            {
                if(flag == 1)
                    painter->setPen(Qt::green);
                //painter->setPen()
                if(flag == 2)
                    painter->setPen(Qt::yellow);
                if(flag == 3)
                    painter->setPen(Qt::red);
            }

            //qWarning() <<"distancePnt = "<<  distancePnt;
            painter->drawLine(lineAngle);
            //std::string to_string("int distancePnt");
            //QString to_qstring(to_string.c_str());
            QString to_qstring = QString::number(double(double(distancePnt)/25));
            levelMetr = distancePnt/25;
            //painter->setPen(QColor(0,200,0));
            painter->drawText(pntTextDist,to_qstring);
            //painter->drawText(QPoint(50, 50), "VERTICAL TEXT");

            item->update();
            scene()->update();
        }

        for(size_t i = 0; i < pRouterVector->size();i++)
        {

            if(item == *(pRouterVector->begin()+i))
            {
                if(item == pUseRouter)
                    continue;
                // найти дистанцию и определить канал
                QPointF f = (**(pRouterVector->begin()+i)).pos() - this->pos();

                std::vector <Router*> *bufferVectorRoutersInZone = pUseRouter->getVectorRoutersInZone();

                int distancePntsAnotherRouter = sqrt(pow(abs(f.x()),2) + pow(abs(f.y()),2));
                flagOutZone =true;
                //qWarning() << "distancePnt = "<<distancePnt;
                //qWarning() << "pos = "<<this->pos();
                for(size_t counts = 0; counts < bufferVectorRoutersInZone->size(); counts++)
                {
                    // если роутер в зоне видимости является роутером, который идет по списку , то его не обрабатывать
                    if(*(bufferVectorRoutersInZone->begin()+counts) == *(pRouterVector->begin()+i))
                    {
                        flagOutZone = false;
                    }
                }
                if((distancePntsAnotherRouter <300) && (abs(pUseRouter->getChannel()-(*(pRouterVector->begin()+i))->getChannel()) <5)  && (flagOutZone == true))
                {

                    int differenceDistance = distancePntsAnotherRouter - distancePnt;

                    if((differenceDistance)>200)
                    {
                        //qWarning()<<"distancePntsAnotherRouter - distancePnt = "<<distancePntsAnotherRouter - distancePnt;
                        //qWarning()<<"вплотную почти";
                        continue;
                    }
                    // 1-2 метра
                    if(((differenceDistance)>150) && ((differenceDistance)<200))
                    {

                        //qWarning()<<"distancePntsAnotherRouter - distancePnt = "<<distancePntsAnotherRouter - distancePnt;
                        //qWarning()<<"1-2 метра чуть дальше чем чусть";
                        minusSpeedCoef+=2+rand() % 2;
                        // по 2-3 процента сверху
                        continue;
                    }
                    if(((differenceDistance)>100) && ((differenceDistance)<150))
                    {

                        //qWarning()<<"distancePntsAnotherRouter - distancePnt = "<<distancePntsAnotherRouter - distancePnt;
                        //qWarning()<<"3-4 метра чуть достает";
                        minusSpeedCoef+=3+rand() % 2;
                        // по 3-4 процента сверху
                        continue;
                    }
                    if(((differenceDistance)>50) && ((differenceDistance)<100))
                    {

                        //qWarning()<<"distancePntsAnotherRouter - distancePnt = "<<distancePntsAnotherRouter - distancePnt;
                        //qWarning()<<"5-6 метра на краю волн";
                        minusSpeedCoef+=4+rand() % 2;
                        // по 4-5 процентов сверху
                        continue;
                    }
                    // почти одинаковое расстояние между роутерами
                    if((abs(differenceDistance)<50))
                    {
                        //qWarning()<<"distancePntsAnotherRouter - distancePnt = "<<distancePntsAnotherRouter - distancePnt;
                        //qWarning()<<"7 метра половина";
                        minusSpeedCoef+=10+rand() % 10;
                        // по 10-20 процентов сверху
                        continue;

                    }

                    differenceDistance = distancePnt - distancePntsAnotherRouter;

                    if((differenceDistance)>200)
                    {
                        //qWarning()<<"distancePntsAnotherRouter - distancePnt = "<<distancePntsAnotherRouter - distancePnt;
                        //qWarning()<<"вплотную к другому ";
                        minusSpeedCoef+=20+rand() % 10;
                        // по 20-30 процентов сверху
                        // 10 метров максимум близко
                        continue;

                    }
                    if(((differenceDistance)>150) && ((differenceDistance)<200))
                    {
                        //qWarning()<<"distancePntsAnotherRouter - distancePnt = "<<distancePntsAnotherRouter - distancePnt;
                        //qWarning()<<"1-2 метра от другого ";
                        minusSpeedCoef+=10+rand() % 15;
                        // по 10-25 процентов сверху
                        // 9 метров от основного роутера максимум близко
                        continue;
                    }
                    if(((differenceDistance)>100) && ((differenceDistance)<150))
                    {
                        //qWarning()<<"distancePntsAnotherRouter - distancePnt = "<<distancePntsAnotherRouter - distancePnt;
                        //qWarning()<<"3-4 метра от другого ";
                        minusSpeedCoef+=10+rand() % 10;
                        // по 10-20 процентов сверху
                        // 8 метров от основного роутера максимум близко
                        continue;
                    }
                    if(((differenceDistance)>50) && ((differenceDistance)<100))
                    {
                        //qWarning()<<"distancePntsAnotherRouter - distancePnt = "<<distancePntsAnotherRouter - distancePnt;
                        //qWarning()<<"5-6 метра от другого ";
                        // по 10-20 процентов сверху
                        // 7 метров от основного роутера максимум близко
                        minusSpeedCoef+=20+rand() % 15;
                        continue;
                    }
                }
            }
        }
    }
    painter->drawPixmap(0,0,mWidth,mHeight,mPixmap);

    // первые два параметра отвечают за координаты, след два за высоту и ширину, последние два за округление
    //if(!mHoverFlag)
        //painter->setPen(Qt::black);
    painter->drawRoundedRect(0,0,mWidth, mHeight,5,5);
    //paintText(painter);
    painter->drawText(0,70,nameThisPC);

    //-----------вычисление скорости в зависимости от расстояния--------------------------

    levelMetr = distancePnt/25;
    InternetSpeed = pUseRouter->getInternetSpeed()/pUseRouter->getCountPC();
    switch (levelMetr)
    {
        case 0: InternetSpeed -= ((InternetSpeed/100)*(0+minusSpeedCoef+rand() % 2));break;     // от 0-1% уменьшение базовой скорости
        case 1: InternetSpeed -= ((InternetSpeed/100)*(2+minusSpeedCoef+rand() % 2));break;     // от 2-3% уменьшение базовой скорости
        case 2: InternetSpeed -= ((InternetSpeed/100)*(2+minusSpeedCoef+rand() % 3));break;     // от 2-4% уменьшение базовой скорости
        case 3: InternetSpeed -= ((InternetSpeed/100)*(3+minusSpeedCoef+rand() % 3));break;     // от 3-5% уменьшение базовой скорости
        case 4: InternetSpeed -= ((InternetSpeed/100)*(8+minusSpeedCoef+rand() % 3));break;     // от 8-10% уменьшение базовой скорости
        case 5: InternetSpeed -= ((InternetSpeed/100)*(9+minusSpeedCoef+rand() % 4));break;     // от 9-12% уменьшение базовой скорости
        case 6: InternetSpeed -= ((InternetSpeed/100)*(12+minusSpeedCoef+rand() % 9));break;    // от 12-20% уменьшение базовой скорости
        case 7: InternetSpeed -= ((InternetSpeed/100)*(20+minusSpeedCoef+rand() % 11));break;     // от 20-30% уменьшение базовой скорости
        case 8: InternetSpeed -= ((InternetSpeed/100)*(30+minusSpeedCoef+rand() % 11));break;     // от 30-40% уменьшение базовой скорости
        case 9: InternetSpeed -= ((InternetSpeed/100)*(40+minusSpeedCoef+rand() % 11));break;     // от 40-50% уменьшение базовой скорости
        case 10: InternetSpeed -= ((InternetSpeed/100)*(50+minusSpeedCoef+rand() % 11));break;     // от 50-60% уменьшение базовой скорости
        case 11: InternetSpeed -= ((InternetSpeed/100)*(60+minusSpeedCoef+rand() % 21));break;     // от 60-80% уменьшение базовой скорости
        default: InternetSpeed = 0;
    }
    minusSpeedCoef = 0;

    //---------------------конвертация скорости-------------------------
    if(InternetSpeed > 1000)
    {
        QString to_qstringInternet = QString::number((double)InternetSpeed/1000);// + "\t Mbps";
        painter->drawText(0,84,to_qstringInternet);
        QString to_qstringInternet2 = "Mbps";
        painter->drawText(25,84,to_qstringInternet2);
    }
    else
    {
        QString to_qstringInternet = QString::number(InternetSpeed) + "   Kbps";
        painter->drawText(0,84,to_qstringInternet);
    }
    update();
}


//----------------включение передвижения-------------------------
void PC::enableMouseMoving()
{
    mIsMovable = true;
}
//----------------отключение передвижения-------------------------
void PC::disableMouseMoving()
{
    mIsMovable = false;
}



//-----------------задаем ширину и высоту----------------------------
void PC::setGeometry(int aWidth, int aHeight)
{
    mWidth = aWidth;
    mHeight = aHeight;
}


//-----------------загрузка картинки----------------------------
void PC::setImage(QString aPath)
{
    mPixmap.load(aPath);
    //mWidth = mPixmap.width();   // загрузка изначальных размеров
    //mHeight = mPixmap.height();
    //mWidth = 50;mHeight =50;

}

//-----------------функция для обработки курсора, в случае если указатель попадает в область кнопки
void PC::hoverEnterEvent(QGraphicsSceneHoverEvent*)
{
    //qWarning() << "Enter";
    mHoverFlag = true;           // true -> курсор внутри кнопки
    setCursor(Qt::PointingHandCursor);
    QGraphicsItem::update();    // перерисовка области
}
//-----------------функция для обработки курсора, в случае если указатель выходит из области кнопки
void PC::hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
    //qWarning() << "Leave";
    mHoverFlag = false;          // false -> курсор снаружи кнопки
    QGraphicsItem::update();    // перерисовка области
}

//-----------------при нажатии кнопки мыши--------------------------
void PC::mousePressEvent(QGraphicsSceneMouseEvent* aEvent)
{

    mStartMovePos = aEvent->pos();      // запись позиции, как только нажали на кнопку
    qWarning() << "Press: " << mStartMovePos;

    qWarning() <<"pUseRouter pos = "<<  pUseRouter->pos();
    qWarning() <<"mapToScene pUseRouter pos = "<<  mapToScene(pUseRouter->pos());
    qWarning() <<"pUsePC pos = "<<  this->pos();
    qWarning() <<"mapToScene pUsePC pos = "<<  mapToScene(this->pos());


    qWarning() <<"dx lineCenter == "<<lineCenter.dx();
    qWarning() <<"dy lineCenter == "<<lineCenter.dy();
    qWarning() <<"Distance == "<<sqrt(pow(abs(lineCenter.dx()),2) + pow(abs(lineCenter.dy()),2));


    mIsMoving = false;
}


//-----------------при нажатии и перемещении мыши в область--------------------------
void PC::mouseMoveEvent(QGraphicsSceneMouseEvent* aEvent)
{
    if(mIsMovable)
    {
        int distance = (aEvent->pos() - mStartMovePos).manhattanLength();       // вычисление дистанции

        // Метод manhattanLength() возвращает сумму абсолютных значений координат Х и У.
        if(distance > 5)        //QApplication::startDragDistance() == 8
        {
            QPointF np = mapToScene(aEvent->pos() -  mStartMovePos);        // новая координата
            qWarning() <<"np pos = "<<  np;

            // mapToScene переводит относительные координаты в координаты сцены

            // проверка, чтобы координаты не ушли за пределы экрана
            if((np.x() < 0) || (np.y() < 0))
                return;
            if((np.x() > 920) || (np.y() > 700))
                return;
            mIsMoving = true;
            setCursor(Qt::ClosedHandCursor);
            this->setPos(np);


            qWarning() << "Move";
            qWarning() << "x = "<<np.x();
            qWarning() << "y = "<<np.y();

        }
    }

}

//-----------------при отжатии кнопки мыши--------------------------
void PC::mouseReleaseEvent(QGraphicsSceneMouseEvent *apEvent)
{
    if(!mIsMoving)
        emit PCMouseReleaseEvent(apEvent->button());   // возбуждение сигнала
    //qWarning() << "Release";
    //if(1)
    if(mIsMoving)
        setCursor(Qt::OpenHandCursor);
    mIsMoving = false;
}


//-----------------Присвоили роутер данному устройству--------------------------
void PC::setRouter(Router * pRouter)
{
    pUseRouter = pRouter;

    lineCenter.setP2(pUseRouter->pos());
}

void PC::setName(QString aName)
{
    nameThisPC = aName;
}

QLineF & PC::GetLine()
{
    return lineCenter;
}


void PC::setInternetSpeed(unsigned int speed)
{
    InternetSpeed = speed;
}
unsigned int PC::getInternetSpeed()
{
    return InternetSpeed;
}

void PC::setPntRouterVector(std::vector <Router*> *mRouterVector)
{
    pRouterVector = mRouterVector;
}
