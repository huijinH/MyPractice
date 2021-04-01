#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setGeometry(0, 0, 100, 100);
    w.show();
    return a.exec();
}
