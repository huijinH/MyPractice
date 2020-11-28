#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPaintEvent>
#include <QList>
#include <QPainter>
#include <QHBoxLayout>
#include <QRegExpValidator>

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void paintEvent(QPaintEvent* e);
    bool eventFilter(QObject *watched, QEvent *event);

public slots:
    void ipLineTextChangedSlot();

private:
    QList<QLineEdit*> ipLineList;
    QHBoxLayout* mainLayout;
};

#endif // WIDGET_H
