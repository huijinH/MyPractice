#include "radar.h"
#include <ctime>

Radar::Radar(QWidget *parent) : QWidget(parent)
{
    angle = 0.0;
    randPointTimeID = startTimer(RandTime);
    scanTimeId = startTimer(ScanTime);
}

void Radar::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), Qt::black);

    // x, y, 3 round
    painter.setPen(Qt::yellow);
    if (width() > height())
    {
        rec.setRect((width() - height()) / 2, 0, height(), height());
        painter.drawLine((width() - height()) / 2,
                         height() / 2,
                         width() - ((width() - height()) / 2),
                         height() / 2);
        painter.drawLine(QPoint(width() / 2, 0), QPoint(width() / 2, height()));
    }
    else
    {
        rec.setRect(0, (height() - width()) / 2, width(), width());
        painter.drawLine(QPoint(0, height() / 2), QPoint(width(), height() / 2));
        painter.drawLine(width() / 2,
                                (height() - width()) / 2,
                                width() / 2,
                                height() - ((height() - width()) / 2));
    }
    int shortSide = width() > height() ? height() : width();
    painter.drawEllipse(rect().center(), shortSide / 6, shortSide / 6);
    painter.drawEllipse(rect().center(), shortSide / 3, shortSide / 3);
    painter.drawEllipse(rect().center(), shortSide / 2, shortSide / 2);

    // SpinLine  cos, sin usage: parameter = angle * 180 * 3.14  lost my so much time!
    qreal x = rect().center().x() + (qreal)cos(angle / 180.0 * 3.14159) * shortSide / 2;
    qreal y = rect().center().y() + (qreal)sin(angle / 180.0 * 3.14159) * shortSide / 2;
    painter.drawLine(rect().center(), QPointF(x, y));

    // Sector and shadow
    QConicalGradient gradient;
    gradient.setCenter(rect().center());
    gradient.setAngle(360 - angle + 180);
    gradient.setColorAt(0.4, QColor(255, 255, 0, 100));
    gradient.setColorAt(0.8, QColor(255, 255, 0, 0));
    painter.setBrush(QBrush(gradient));
    painter.setPen(Qt::NoPen);
    painter.drawPie(rec, (360 - angle) * 16, 90 * 16);

    // rand point
    QPen pen(Qt::red);
    pen.setWidth(5);
    painter.setPen(pen);

    for (int i = 0; i < pointList.count(); i++)
    {
        painter.drawPoint(pointList.at(i));
    }
}

void Radar::timerEvent(QTimerEvent *e)
{
    if (scanTimeId == e -> timerId())
    {
        angle += 5.0;
        if (angle > 360.0)
            angle = angle - 360.0;
        update();
    }
    else if (randPointTimeID == e -> timerId())
    {
        pointList.clear();
        int cnt = 3 + rand() % 4;
        for (int i = 0; i < cnt; i++)
        {
            int x = rec.topLeft().x() + rand() % rec.width();
            int y = rec.topLeft().y() + rand() % rec.height();
            pointList.append(QPoint(x, y));
        }
        update();
    }
}
