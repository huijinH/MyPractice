#include "WinAPI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WinAPI w;
    w.show();
    return a.exec();
}
