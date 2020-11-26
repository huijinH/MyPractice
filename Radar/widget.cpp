#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui -> setupUi(this);

    radar = new Radar(this);
    radar -> resize(width(), height());
}

Widget::~Widget()
{
    delete ui;
}

void Widget::resizeEvent(QResizeEvent *e)
{
    radar -> resize(width(), height());
}
