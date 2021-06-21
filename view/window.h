#ifndef WINDOW_H
#define WINDOW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <string>
#include "addmenu.h"
#include "pc.h"


class Window : public QGraphicsView
{
public:
    Window();

private:
//----------функции-----------------
    void _init_view_elements();
    //void drawLine(Router *pRouter, PC *pPC);

//--------члены класса--------------
    QGraphicsScene mScene;
    Router mRouterA;                       // роутер A
    Router mRouterB;                       // роутер A
    Router mRouterC;                       // роутер A
    Router *mRouterD;
    AddMenu add_menu;
    std::vector <Router*> *mRouterVector;
    std::vector <PC*> mPCVector;                // вектор подключенных устройств к роутеру

    bool flagOnOffWave{true};


    //Router *mRouters;s

private slots:
    void RouterA_clicked(Qt::MouseButton);
    void RouterB_clicked(Qt::MouseButton);
    void RouterC_clicked(Qt::MouseButton);
    void Routers_clicked(Qt::MouseButton);
    void PC_clicked(Qt::MouseButton);

    void changeChannel();
    void addPCfunc();
    Router * addRouter();
        PC * addPC(Router *);                   // создание ПК, который подключается к данному роутеру

    void OffOnWave();
    //void addRouterSlot();

};

#endif // WINDOW_H
