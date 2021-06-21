#ifndef PC_H
#define PC_H

#include "router.h"
class Router;

class PC :  public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    PC();

    QRectF boundingRect() const override;           // указываем область для перерисовки, область взаимодействия

    // отрисовка
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void paintDistanceText();

    void setGeometry(int,int);                      // задаем ширину и высоту

    void setImage(QString);                         // загрузка картинки, передаем путь картинки
    // функция для обработки курсора, в случае если указатель попадает в область кнопки
    void hoverEnterEvent(QGraphicsSceneHoverEvent*)     override;
    // функция для обработки курсора, в случае если указатель выходит из области кнопки
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*)     override;


    void mousePressEvent(QGraphicsSceneMouseEvent*)     override;       // при нажатии кнопки мыши
    void mouseMoveEvent(QGraphicsSceneMouseEvent*)     override;        // при нажатии и перемещении мыши
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*)     override;     // при отжатии кнопки мыши


    void enableMouseMoving();                       // включение перемещения объекта по сцене
    void disableMouseMoving();                      // отключение перемещения объекта по сцене


    void setRouter(Router *);                       // связка с роутером
    void setName(QString);                          // установка имени для данного ПК
    QLineF & GetLine();

    void setInternetSpeed(unsigned int speed);
    unsigned int getInternetSpeed();

    void setPntRouterVector(std::vector <Router*> *);

signals:
    void PCMouseReleaseEvent(Qt::MouseButton);

private:
    //переменные отвечающие за размер
    int mWidth{0};
    int mHeight{0};

    bool mIsMovable{true};          // флаг проверки двиагется ли объект
    bool mHoverFlag{false};         // флаг обработки курсора
    bool mIsMoving{false};          // обработка движения/ двигается кнопка или нет

    QPointF mStartMovePos;          // стартовая координата, где кнопка была нажата

    QPixmap mPixmap;                // объект, содержащий изображение/ отрисовать его сможет painter

    Router *pUseRouter;             // используемый роутер
    QPointF myPnt;                  // точка расположения данного пк, по умолчанию 0;0
    QPointF RouterPnt;              // точка расположения роутера
    QPointF pntTextDist;            // точка для дистанции
    QLineF lineCenter;
    QLineF lineAngle;
    int flag = 0;                   // нужен для обработки цвета в зависимости от расстояния
    int distancePnt;
    unsigned int levelMetr;

    int countPC;// = pUseRouter->getCountPC();
    QString nameThisPC = "DefaultPC";
    unsigned int InternetSpeed = 10;

    std::vector <Router*> *pRouterVector;              // указатель на вектор всех роутеров


};

#endif // PC_H
