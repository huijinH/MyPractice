#ifndef RADAR_H
#define RADAR_H

#include <QWidget>
#include <QPainter>
#include <QConicalGradient>
#include <QPaintEvent>
#include <QTimerEvent>

class Radar : public QWidget
{
    Q_OBJECT
public:
    explicit Radar(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* e);
    void timerEvent(QTimerEvent* e);

signals:

public slots:

private:
    const int RandTime = 1000;
    const int ScanTime = 50;
    int randPointTimeID;
    int scanTimeId;
    double angle;
    QList<QPoint> pointList;
    QRect rec;
};

#endif // RADAR_H
