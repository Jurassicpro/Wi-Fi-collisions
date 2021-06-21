#ifndef ROUTER_H
#define ROUTER_H

#include <QObject>
#include <QGraphicsItem>
#include <QPointF>
#include <QPixmap>
#include <QString>
#include <vector>

class PC;

class Router : public QObject, public QGraphicsItem
{
    Q_OBJECT        // включение макроса
public:
    Router();
    ~Router();

    QRectF boundingRect() const override;           // указываем область для перерисовки

    // отрисовка
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setGeometry(int,int);                      // задаем ширину и высоту

    void setImage(QString);                         // загрузка картинки, передаем путь картинки

    // функция для обработки курсора, в случае если указатель попадает в область роутера
    void hoverEnterEvent(QGraphicsSceneHoverEvent*)     override;

    // функция для обработки курсора, в случае если указатель выходит из области роутера
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*)     override;


    void mousePressEvent(QGraphicsSceneMouseEvent*)     override;       // при нажатии роутера мыши
    void mouseMoveEvent(QGraphicsSceneMouseEvent*)     override;        // при нажатии и перемещении мыши
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*)     override;     // при отжатии роутера мыши


    void enableMouseMoving();                       // включение перемещения объекта по сцене
    void disableMouseMoving();                      // отключение перемещения объекта по сцене
    void setName(QString );
    QString getName();
    void setChannelName (QString);
    QString getChannelName();
    int getChannel();

    void setPrintWaveFlag(bool);


    void setInternetSpeed(unsigned int);
    unsigned int getInternetSpeed();

    std::vector <PC*>* getVectorPC();


    int getCountPC();
    void setCountPC(size_t);

    void setPntRouterVector(std::vector <Router*> *);
    void setMinusCountRouterFourth(int);

    int getSumRoutersInZone();
    std::vector <Router*> *getVectorRoutersInZone();
protected:
    void timerEvent(QTimerEvent *e) override;

signals:
    void RouterMouseReleaseEvent(Qt::MouseButton);

//private slots:
    //void setChannelValue();
    //void setFlagForWave();

private:
    //переменные отвечающие за размер роутера
    int mWidth{0};
    int mHeight{0};

    int countWave;

    QString nameThisRouter = "Default";
    QString channelName = "2,412 GHz";
    int channelValue = 1;
    std::vector<std::vector<QRectF*>*> vectorRec;       // вектор прямоугольников для отрисовки волн Wi-Fi

    bool mIsMovable{true};          // флаг проверки двиагется ли объект
    bool mHoverFlag{false};         // флаг обработки курсора
    bool mIsMoving{false};          // обработка движения/ двигается роутер или нет

    QPointF mStartMovePos;          // стартовая координата, где роутер был нажат

    QPixmap mPixmap;                // объект, содержащий изображение/ отрисовать его сможет painter
    bool printWaveFlag{false};

    unsigned int InternetSpeed = 0;
    unsigned int constSpeed;

    std::vector <PC*> mPCVector;                       // вектор подключенных устройств к роутеру
    std::vector <Router*> *pRouterVector;              // указатель на вектор всех роутеров
    std::vector <Router*> pRouterVectorInZone;        // указатель на вектор роутеров входящих в зону видимости
    int countRouter = 0;
    int countPC = 0;

    //QLineF lineCenter;                          // линия для определения расстояния между роутерами
    QPointF SelfPoint;
    int distancePnts;
    bool flagFourth1{false};
    bool flagFourth2{false};
    bool flagFourth3{false};
    bool flagFourth4{false};

    int countRouterFourth1 = 0;
    int countRouterFourth2 = 0;
    int countRouterFourth3 = 0;
    int countRouterFourth4 = 0;
    std::vector<int> wasFourth;
    int old_sum = 0;
    int buffer;
};

#endif // ROUTER_H
