#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void mousePressEvent(QMouseEvent* e) override;
    void mouseMoveEvent(QMouseEvent* e) override;
    void mouseDoubleClickEvent(QMouseEvent* e) override;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();


private:
    Ui::Widget *ui;
    bool isMax = false;
    int winWidth, winHeight;
    const int SIDELEN = 15;
    QPoint geometryPos;
    QPoint pressPos;
    QPoint pos;  // The position of the mouse relative to the top left vertex of the window
};

#endif // WIDGET_H
