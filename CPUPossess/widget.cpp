#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

__int64 CompareFileTime(FILETIME time1, FILETIME time2)
{
    // time from double to int
    __int64 a = time1.dwHighDateTime << 32 | time1.dwLowDateTime;
    __int64 b = time2.dwHighDateTime << 32 | time2.dwLowDateTime;

    return   (b - a);
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui -> setupUi(this);

    curve = new QwtPlotCurve;
    curve-> setPen(Qt::red, 2);
    curve -> setSamples(time, val, 10);

    ui -> qwtPlot -> setTitle(tr("CPU Possess"));
    ui -> qwtPlot -> setAxisTitle(QwtPlot::xBottom, "t(s)");
    ui -> qwtPlot -> setAxisTitle(QwtPlot::yLeft, "p(%)");
    ui -> qwtPlot -> setAxisScale(QwtPlot::xBottom, 1, 10, 1);
    ui -> qwtPlot -> setAxisScale(QwtPlot::yLeft, 0, 100, 10);

    curve -> setCurveAttribute(QwtPlotCurve::Fitted, true);
    curve -> attach(ui -> qwtPlot);

    startTimer(1000);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::timerEvent(QTimerEvent *e)
{
    res = GetSystemTimes(&idleTime, &kernelTime, &userTime);
    int idle = CompareFileTime(preidleTime, idleTime);
    int kernel = CompareFileTime(prekernelTime, kernelTime);
    int user = CompareFileTime(preuserTime, userTime);
    double cpu = (kernel + user - idle) *100.0 / (kernel + user);

    qDebug() << cpu << "%";
    for (int i = 0; i < 9; i++)
    {
        val[i] = val[i + 1];
    }
    val[9] = cpu;
    curve -> setSamples(time, val, 10);
    ui -> qwtPlot -> replot();

    preidleTime = idleTime;
    prekernelTime = kernelTime;
    preuserTime = userTime;
}

void Widget::initCPUVal()
{
    res = GetSystemTimes(&idleTime, &kernelTime, &userTime);
    preidleTime = idleTime;
    prekernelTime = kernelTime;
    preuserTime = userTime;
    hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
}
