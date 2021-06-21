#ifndef ADDMENU_H
#define ADDMENU_H

//#include "pc.h"
#include <QObject>
#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <vector>
#include <QMenu>


class AddMenu : public QWidget
{
    Q_OBJECT
public:
    AddMenu();
    void _init_elements();                          // инициализация кнопок
    void addBtnSpeed();
    void addQuitButton();
    void OffOnWaveBtn();
    void OffOnWaveBtnAct();
    void addRouterFunc();
    void addPCFunc();
    void addRouterAct();
    void addPCAct();
    void changeRouterChannelAct();
    void changeChannelBtn();

    void deleteRouterName(QString);



    void addRouterChannelFunc();
    QString getRouterName();
    QString getRouterChannelName();
    QString getRouterNameFromBtn();

    QString getPCName();

    void choiseRouterForPC();

    unsigned int getInternetSpeed();

    QString getRouterChannelNameForChange();
    QString getRouterNameForChangeChannel();



private:
    const int X = 100;
    const int Y = 100;
    int countRouter = 0;

    std::vector<QString>::iterator iterRouter = nameRouter.begin();
    std::vector<QString>::iterator iterPC = namePC.begin();
    std::vector<QString> nameRouter;            // вектор имен
    std::vector<QString> namePC;
    QString RouterName = "Default";
    QString channelName;
    QString speedValueText;

    QString PCName = "Default";
    QString listRouterNameBtn;


    QLineEdit *nameRouterEdit;
    QLineEdit *namePCEdit;

    QPushButton *channelsBtn;
    QPushButton *speedInternetBtn;

    QAction *pActChannel[14];
    QAction *pActChannelForChange[14];
    QAction *pActSpeed[7];

    std::vector<QAction*> routersVector;                        // вектор экшенов у роутера
    std::vector<QAction*> routersVectorForChangeChannel;        // вектор экшенов у роутера

    QMenu *pMenuRouters;
    QPushButton *listRoutersBtn;


    QMenu *pMenuRoutersChangeChannel;
    QPushButton *listRoutersBtnChannel;
    QPushButton *routersBtnChannel;
    QString channelNameForChange;
    QString RouterNameForChangeChannel;


protected:
    void paintEvent(QPaintEvent *event);

signals:
    void addRouterSignal();
    void addPCSignal();
    void changeChannel();
    void OffOnRouterWave();
    //void chooseChannel();

private slots:
    void BtnMenuChangeChannelText();
    void BtnMenuChangeRouterText();
    //void BtnMenuChangeChannelText2();
    void BtnMenuChangeRouterChannelText();
    void BtnMenuChangeSpeedText();

};

#endif // ADDMENU_H
