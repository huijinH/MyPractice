#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QList>
#include "childwidget.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void addChildWidgetSlot();

private:
    Ui::Widget *ui;
    QList<ChildWidget*> childList;
};

#endif // WIDGET_H
