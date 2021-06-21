#include "router.h"
#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QCursor>
#include <QGraphicsScene>
#include <cmath>
//#include <windows.h>
//#include <stdio.h>
#include <chrono>
#include <QTime>


Router::Router()
{

    setAcceptHoverEvents(true);                                           // включаем методы обработки указателя
    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);            // включение только ЛКМ
    pRouterVector = new std::vector <Router*>;
    pRouterVector->size();

    wasFourth.resize(5);
    for(size_t i = 0;i<wasFourth.size();i++)
        wasFourth[i] = 0;

}


Router::~Router()
{

}
//-----------------указываем область для перерисовки-----------------
QRectF Router::boundingRect() const
{
    return QRectF(0,0,mWidth,mHeight);                  // возвращаем размеры прямоугольника
}


//-----------------отрисовка-----------------------------------------
void Router::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    if(mHoverFlag){
        //painter->setBrush(Qt::green);                   // или QColor(255,0,0) / закраска полностю
        painter->setPen(Qt::blue);                      // или QColor(255,0,122)
    }

    //painter->drawLine(100,100,600,600);

    QList<QGraphicsItem*> l = scene()->items();      // список всех графических объектов

    // справа получаем указатель на cписок всех объектов сцены (mScene)

    wasFourth.resize(pRouterVector->size());
    int countDistance = 0;
    std::vector <Router*> pRouterVectorInZoneBuffer;
    foreach(QGraphicsItem *item,l)
    {
        if(item == this)
            continue;
        // если другой объект
        // collideWithPath  - с областью

        if(collidesWithItem(item))        // пересечение с item / другим обхектом
        {
            painter->setBrush(Qt::red);
            item->update();                 // чтобы обновлялся сразу
        }



        for(size_t i = 0; i < pRouterVector->size();i++)
        {

            if(item == *(pRouterVector->begin()+i))
            {
                // найти дистанцию и определить канал
                QPointF f = (**(pRouterVector->begin()+i)).pos() - this->pos();
                QPointF anotherRouterPnt = (**(pRouterVector->begin()+i)).pos();

                //qWarning() << "f = "<<f;
                SelfPoint = this->pos();
                distancePnts = sqrt(pow(abs(f.x()),2) + pow(abs(f.y()),2));

                //qWarning() << "distancePnt = "<<distancePnt;
                //qWarning() << "pos = "<<this->pos();
                if((distancePnts <300) && (abs(channelValue-(*(pRouterVector->begin()+i))->getChannel()) <5))
                {
                    pRouterVectorInZoneBuffer.push_back(*(pRouterVector->begin()+i));
                    if((anotherRouterPnt.x() > SelfPoint.x()) && (anotherRouterPnt.y() < SelfPoint.y()) && wasFourth[i] != 1)// && ( || (flagFourth1 != true)))
                    {

                        if((countRouterFourth1 < ((int)pRouterVector->size()-1)) || (countRouterFourth1 == 0))//nen
                            countRouterFourth1++;
                        flagFourth1 = true;
                        if(wasFourth[i] != 0)
                        {
                            switch(wasFourth[i])
                            {
                            case 2:
                                if(countRouterFourth2 > 0)
                                    countRouterFourth2--;
                                if(countRouterFourth2 == 0)
                                    flagFourth2 = false;
                                break;
                            case 3:
                                if(countRouterFourth3 > 0)
                                    countRouterFourth3--;
                                if(countRouterFourth3 == 0)
                                    flagFourth3 = false;
                                break;
                            case 4:
                                if(countRouterFourth4 > 0)
                                    countRouterFourth4--;
                                if(countRouterFourth4 == 0)
                                    flagFourth4 = false;
                                break;
                            }
                        }

                        wasFourth[i] = 1;
                    }
                    else if(countRouterFourth1 == 0)
                        flagFourth1 = false;

                    if((anotherRouterPnt.x() < SelfPoint.x()) && (anotherRouterPnt.y() <  SelfPoint.y()) && wasFourth[i] != 2)// && ( || (flagFourth2 != true)))
                    {
                        if((countRouterFourth2 < ((int)pRouterVector->size()-1)) || (countRouterFourth2 == 0))
                            countRouterFourth2++;
                        flagFourth2 = true;
                        if(wasFourth[i] != 0)
                        {
                            switch(wasFourth[i])
                            {
                            case 1:
                                if(countRouterFourth1 > 0)
                                    countRouterFourth1--;
                                if(countRouterFourth1 == 0)
                                    flagFourth1 = false;
                                break;
                            case 3:
                                if(countRouterFourth3 > 0)
                                    countRouterFourth3--;
                                if(countRouterFourth3 == 0)
                                    flagFourth3 = false;
                                break;
                            case 4:
                                if(countRouterFourth4 > 0)
                                    countRouterFourth4--;
                                if(countRouterFourth4 == 0)
                                    flagFourth4 = false;
                                break;
                            }
                        }

                        wasFourth[i] = 2;
                    }
                    else if(countRouterFourth2 == 0)
                        flagFourth2 = false;

                    if((anotherRouterPnt.x() <  SelfPoint.x()) && (anotherRouterPnt.y() > SelfPoint.y()) && wasFourth[i] != 3)// && ( || (flagFourth3 != true)))
                    {
                        if((countRouterFourth3 < ((int)pRouterVector->size()-1)) || (countRouterFourth3 == 0))
                            countRouterFourth3++;
                        flagFourth3 = true;
                        if(wasFourth[i] != 0)
                        {
                            switch(wasFourth[i])
                            {
                            case 1:
                                if(countRouterFourth1 > 0)
                                    countRouterFourth1--;
                                if(countRouterFourth1 == 0)
                                    flagFourth1 = false;
                                break;
                            case 2:
                                if(countRouterFourth2 > 0)
                                    countRouterFourth2--;
                                if(countRouterFourth2 == 0)
                                    flagFourth2 = false;
                                break;
                            case 4:
                                if(countRouterFourth4 > 0)
                                    countRouterFourth4--;
                                if(countRouterFourth4 == 0)
                                    flagFourth4 = false;
                                break;
                            }
                        }

                        wasFourth[i] = 3;
                    }
                    else
                    {
                        if(countRouterFourth3 == 0)
                            flagFourth3 = false;

                    }



                    if((anotherRouterPnt.x() >  SelfPoint.x()) && (anotherRouterPnt.y() >  SelfPoint.y()) && wasFourth[i] != 4)// && ( || (flagFourth4 != true)))
                    {
                        if((countRouterFourth4 < ((int)pRouterVector->size()-1)) || (countRouterFourth4 == 0))
                            countRouterFourth4++;
                        flagFourth4 = true;
                        if(wasFourth[i] != 0)
                        {
                            switch(wasFourth[i])
                            {
                            case 1:
                                if(countRouterFourth1 > 0)
                                    countRouterFourth1--;
                                if(countRouterFourth1 == 0)
                                    flagFourth1 = false;
                                break;
                            case 2:
                                if(countRouterFourth2 > 0)
                                    countRouterFourth2--;
                                if(countRouterFourth2 == 0)
                                    flagFourth2 = false;
                                break;
                            case 3:
                                if(countRouterFourth3 > 0)
                                    countRouterFourth3--;
                                if(countRouterFourth3 == 0)
                                    flagFourth3 = false;
                                break;
                            }
                        }

                        wasFourth[i] = 4;
                    }
                    else if(countRouterFourth4 == 0)
                        flagFourth4 = false;
                }
                else
                {
                    countDistance++;
                    switch(wasFourth[i])
                    {
                        case 1: (*(pRouterVector->begin()+i))->setMinusCountRouterFourth(3);break;
                        case 2: (*(pRouterVector->begin()+i))->setMinusCountRouterFourth(4);break;
                        case 3: (*(pRouterVector->begin()+i))->setMinusCountRouterFourth(1);break;
                        case 4: (*(pRouterVector->begin()+i))->setMinusCountRouterFourth(2);break;
                    //default: qWarning()<< "ERROR выбрался ноль";break;
                    }
                    //qWarning() << "countDistance == "<<countDistance;
                    if(countDistance==(int)pRouterVector->size()-1)
                    {
                        countRouterFourth1 = 0;
                        countRouterFourth2 = 0;
                        countRouterFourth3 = 0;
                        countRouterFourth4 = 0;

                        flagFourth1 = false;
                        flagFourth2 = false;
                        flagFourth3 = false;
                        flagFourth4 = false;
                        // надо еще смотреть какая позиция
                        for(int j= 0;j<(int)pRouterVector->size();j++)
                            wasFourth[j] = 0;

                    }
                    wasFourth[i] = 0;
                }
            }
        }

    }
    // вставить код, где от кол-ва роутеров и дистанции изменяется скорость инета


    pRouterVectorInZone.clear();
    for(size_t i = 0; i< pRouterVectorInZoneBuffer.size();i++)
    {
        pRouterVectorInZone.push_back(pRouterVectorInZoneBuffer[i]);
    }
    int sum = countRouterFourth1 + countRouterFourth2 + countRouterFourth3 + countRouterFourth4;

    if(sum == 0)
    {
        InternetSpeed = constSpeed;

        old_sum = sum;
    }
    else
    if(old_sum == 0 || old_sum != sum)
    {
        if(old_sum > sum)
            InternetSpeed += buffer;
        else
        {
            InternetSpeed = constSpeed;
            for(int i = 0,j;i <sum;i++)
            {
                j = (InternetSpeed/5);
                InternetSpeed -= j;
                buffer = j;
            }
        }

        old_sum = sum;
    }

    countDistance = 0;

    painter->drawPixmap(0,0,mWidth,mHeight,mPixmap);

    // первые два параметра отвечают за координаты, след два за высоту и ширину, последние два за округление
    painter->drawRoundedRect(0,0,mWidth, mHeight,5,5);


    //----------------------название роутера--------------------------------
    painter->drawText(0,70,nameThisRouter);
    painter->drawText(0,85,channelName);

    QString to_qstringInternet = QString::number(channelValue) + "   channel";
    painter->drawText(0,100,to_qstringInternet);
    painter->setPen(Qt::black);



    // rec - прямоугольник, в котором чертятся дуги
    //  первый параметр - прямоугольник, второй, начало координаты отрисовки, третий - длина отрисовки


    QRectF *rec[4];
    std::vector<QRectF*> *vecBuffer;

    for(int i = 0; i < 7;i++)
    {
        vecBuffer = new std::vector<QRectF*>;

        for(int j = 0; j <4; j++)
        {
            rec[j] = new QRectF;
            rec[j]->setRect(-30*(i+1),-30*(i+1),mWidth+60*(i+1), mHeight+60*(i+1));
            //painter->drawRect(*rec[j]);
            vecBuffer->push_back(rec[j]);
        }
        vectorRec.push_back(vecBuffer);
    }
    if(printWaveFlag)
        for(countWave = 0; countWave < 7; countWave++)
        {
            if(flagFourth1)
            {
                painter->setPen(Qt::red);
                painter->drawArc(**(vectorRec[countWave]->begin()),150,1137);
                painter->setPen(Qt::black);
            }
            else
                painter->drawArc(**(vectorRec[countWave]->begin()),150,1137);

            if(flagFourth2)
            {
                painter->setPen(Qt::red);
                painter->drawArc(**(vectorRec[countWave]->begin()+1),1587,1137);
                painter->setPen(Qt::black);
            }
            else
                painter->drawArc(**(vectorRec[countWave]->begin()+1),1587,1137);

            if(flagFourth3)
            {
                painter->setPen(Qt::red);
                painter->drawArc(**(vectorRec[countWave]->begin()+2),3025,1137);
                painter->setPen(Qt::black);
            }
            else
                painter->drawArc(**(vectorRec[countWave]->begin()+2),3025,1137);

            if(flagFourth4)
            {
                painter->setPen(Qt::red);
                painter->drawArc(**(vectorRec[countWave]->begin()+3),4462,1137);
                painter->setPen(Qt::black);
            }
            else
                painter->drawArc(**(vectorRec[countWave]->begin()+3),4462,1137);

        }


    scene()->update();

}
void Router::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
    countWave++;
}

//----------------включение передвижения-------------------------
void Router::enableMouseMoving()
{
    mIsMovable = true;
}
//----------------отключение передвижения-------------------------
void Router::disableMouseMoving()
{
    mIsMovable = false;
}



//-----------------задаем ширину и высоту----------------------------
void Router::setGeometry(int aWidth, int aHeight)
{
    mWidth = aWidth;
    mHeight = aHeight;
}


//-----------------загрузка картинки----------------------------
void Router::setImage(QString aPath)
{
    mPixmap.load(aPath);
    //mWidth = mPixmap.width();   // загрузка изначальных размеров
    //mHeight = mPixmap.height();
    //mWidth = 50;mHeight =50;

}

//-----------------функция для обработки курсора, в случае если указатель попадает в область роутера----
void Router::hoverEnterEvent(QGraphicsSceneHoverEvent*)
{
    //qWarning() << "Enter";
    mHoverFlag = true;           // true -> курсор внутри роутера
    //QGuiApplication::setOverrideCursor(Qt::OpenHandCursor);
    setCursor(Qt::PointingHandCursor);
    QGraphicsItem::update();    // перерисовка области
}
//-----------------функция для обработки курсора, в случае если указатель выходит из области роутера---
void Router::hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
    //qWarning() << "Leave";
    mHoverFlag = false;          // false -> курсор снаружи роутера

    QGraphicsItem::update();    // перерисовка области
}

//-----------------при нажатии роутера мыши--------------------------
void Router::mousePressEvent(QGraphicsSceneMouseEvent* aEvent)
{

    mStartMovePos = aEvent->pos();      // запись позиции, как только нажали на роутер
    qWarning() << "Press: " << mStartMovePos;
    qWarning() << "this pos: " << this->pos();
    qWarning() << "mapToScene(this->pos()): " << mapToScene(this->pos());
    mIsMoving = false;


    qWarning() << " flagFourth1 == "<< flagFourth1;
    qWarning() << " flagFourth2 == "<< flagFourth2;
    qWarning() << " flagFourth3 == "<< flagFourth3;
    qWarning() << " flagFourth4 == "<< flagFourth4;

    qWarning() << "selfPoint x == "<<SelfPoint.x();
    qWarning() << "selfPoint y == "<<SelfPoint.y();

    qWarning() << " countRouterFourth1 = "<< countRouterFourth1;
    qWarning() << " countRouterFourth2 = "<< countRouterFourth2;
    qWarning() << " countRouterFourth3 = "<< countRouterFourth3;
    qWarning() << " countRouterFourth4 = "<< countRouterFourth4;

    qWarning() << "pRouterVector.size =  "<<pRouterVector->size();


    for(int i = 0; i < (int)wasFourth.size();i++)
    {
        qWarning() << "wasFourth =  "<<wasFourth[i];
    }


}


//-----------------при нажатии и перемещении мыши в область--------------------------
void Router::mouseMoveEvent(QGraphicsSceneMouseEvent* aEvent)
{
    if(mIsMovable)
    {
        int distance = (aEvent->pos() - mStartMovePos).manhattanLength();       // вычисление дистанции
        // Метод manhattanLength() возвращает сумму абсолютных значений координат Х и У.

        if(distance > 5)        //QApplication::startDragDistance() == 8
        {
            QPointF np = mapToScene(aEvent->pos() -  mStartMovePos);        // новая координата
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
void Router::mouseReleaseEvent(QGraphicsSceneMouseEvent *apEvent)
{
    if(!mIsMoving)
        emit RouterMouseReleaseEvent(apEvent->button());   // возбуждение сигнала
    //qWarning() << "Release";
    //if(1)
    if(mIsMoving)
        setCursor(Qt::OpenHandCursor);
}


void Router::setName(QString pName)
{
    nameThisRouter = pName;
}
QString Router::getName()
{
    return nameThisRouter;
}


void Router::setChannelName (QString pChannelName)
{
    channelName = pChannelName;

    if(channelName == "2,412 GHz")
        channelValue = 1;
    if(channelName == "2,417 GHz")
        channelValue = 2;
    if(channelName == "2,422 GHz")
        channelValue = 3;
    if(channelName == "2,427 GHz")
        channelValue = 4;
    if(channelName == "2,432 GHz")
        channelValue = 5;
    if(channelName == "2,437 GHz")
        channelValue = 6;
    if(channelName == "2,442 GHz")
        channelValue = 7;
    if(channelName == "2,447 GHz")
        channelValue = 8;
    if(channelName == "2,452 GHz")
        channelValue = 9;
    if(channelName == "2,457 GHz")
        channelValue = 10;
    if(channelName == "2,462 GHz")
        channelValue = 11;
    if(channelName == "2,467 GHz")
        channelValue = 12;
    if(channelName == "2,472 GHz")
        channelValue = 13;
    if(channelName == "2,484 GHz")
        channelValue = 14;
}

QString Router::getChannelName()
{
    return nameThisRouter;
}

int Router::getChannel()
{
    return channelValue;
}

void Router::setPrintWaveFlag(bool val)
{
    printWaveFlag = val;
}


void Router::setInternetSpeed(unsigned int speed)
{
    InternetSpeed = speed;
    constSpeed = speed;
}
unsigned int Router::getInternetSpeed()
{
    return InternetSpeed;
}


std::vector <PC*>* Router::getVectorPC()
{
    return &mPCVector;
}

int Router::getCountPC()
{
    countPC = mPCVector.size();
    return countPC;
}

void Router::setCountPC(size_t count)
{
    countPC = count;
}

void Router::setPntRouterVector(std::vector <Router*> *mRouterVector)
{
    pRouterVector = mRouterVector;
}

void Router::setMinusCountRouterFourth(int fourth)
{
    switch (fourth)
    {
        case 1: countRouterFourth1--;break;
        case 2: countRouterFourth2--;break;
        case 3: countRouterFourth3--;break;
        case 4: countRouterFourth4--;break;

    }
}


int Router::getSumRoutersInZone()
{
    return countRouterFourth1+countRouterFourth2+countRouterFourth3+countRouterFourth4;
}

std::vector <Router*> *Router::getVectorRoutersInZone()
{
    return &pRouterVectorInZone;
}
