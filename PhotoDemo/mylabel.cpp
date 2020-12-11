#include "mylabel.h"
#include <QPainter>
#include <QWheelEvent>
#include <QDebug>

MyLabel::MyLabel(QWidget* parent) : QLabel(parent)
{
    QPalette palette;
    palette.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);
    setPalette(palette);
}

void MyLabel::setLocalFileName(const QString &imgName)
{
    LocalFileName = imgName;
    OnPresetImage();
    update();
}

void MyLabel::paintEvent(QPaintEvent *event)
{
    if (LocalFileName.isNull())
        return QWidget::paintEvent(event);

    Image.load(LocalFileName);
    QPainter painter(this);

    int width = qMin(Image.width(), this->width());
    int height = width * 1.0 / (Image.width() * 1.0 / Image.height());

    painter.translate(this->width() / 2 + XPtInterval, this->height() / 2 + YPtInterval);

    painter.scale(ZoomValue, ZoomValue);

    QRect picRect(-width / 2, -height / 2, width, height);
    painter.drawImage(picRect, Image);
}

void MyLabel::wheelEvent(QWheelEvent *event)
{
    int value = event->delta();
    if (value > 0)
        OnZoomInImage();
    else
        OnZoomOutImage();

    update();
}

void MyLabel::mousePressEvent(QMouseEvent *event)
{
    OldPos = event->pos();
    Pressed = true;
}

void MyLabel::mouseMoveEvent(QMouseEvent *event)
{
    if (!Pressed)
        return QWidget::mouseMoveEvent(event);

    this->setCursor(Qt::SizeAllCursor);
    QPoint pos = event->pos();
    int xPtInterval = pos.x() - OldPos.x();
    int yPtInterval = pos.y() - OldPos.y();

    XPtInterval += xPtInterval;
    YPtInterval += yPtInterval;

    OldPos = pos;
    update();
}

void MyLabel::mouseReleaseEvent(QMouseEvent* event)
{
    Q_UNUSED(event);
    Pressed = false;
    setCursor(Qt::ArrowCursor);
}

void MyLabel::OnZoomInImage()
{
    ZoomValue += 0.05;
    update();
}

void MyLabel::OnZoomOutImage()
{
    ZoomValue -= 0.05;
    if (ZoomValue <= 0)
    {
        ZoomValue = 0.05;
        return;
    }

    update();
}

void MyLabel::OnPresetImage()
{
    ZoomValue = 1.0;
    XPtInterval = 0;
    YPtInterval = 0;
    update();
}

