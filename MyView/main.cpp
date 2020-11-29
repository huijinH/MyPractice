#include "MyView.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyView w;
    w.show();
    return a.exec();
}
