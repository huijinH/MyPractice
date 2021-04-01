#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <Windows.h>
#include <QTimerEvent>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    virtual ~Widget();

protected:
    void timerEvent(QTimerEvent* e);

private:
    Ui::Widget *ui;
    QwtPlotCurve* curve;

    double time[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};  // x
    double val[10] = {0};  // y

    // cpu val
    HANDLE hEvent;
    BOOL res;
    FILETIME preidleTime;
    FILETIME prekernelTime;
    FILETIME preuserTime;
    FILETIME idleTime;
    FILETIME kernelTime;
    FILETIME userTime;
};

#endif // WIDGET_H
