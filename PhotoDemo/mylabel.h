#ifndef MYLABEL_H
#define MYLABEL_H

#include <QObject>
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>
#include <QWheelEvent>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget* parent = nullptr);
    void setLocalFileName(const QString& imgName);

protected:
    void paintEvent(QPaintEvent *event);
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void OnZoomInImage();
    void OnZoomOutImage();
    void OnPresetImage();       // Picture restoration

private:
    QImage Image;
    qreal ZoomValue = 1.0;
    int XPtInterval = 0;
    int YPtInterval = 0;
    QPoint OldPos;
    bool Pressed = false;
    QString LocalFileName;
};

#endif // MYLABEL_H
