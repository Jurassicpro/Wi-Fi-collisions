#include <QApplication>
#include "window.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Window view;
    view.show();

    return a.exec();
}
