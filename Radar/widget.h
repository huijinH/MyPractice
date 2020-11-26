#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "radar.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void resizeEvent(QResizeEvent* e);

private:
    Ui::Widget *ui;
    Radar* radar;
};

#endif // WIDGET_H
