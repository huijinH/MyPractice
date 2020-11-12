#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMouseEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui -> setupUi(this);
    ui -> label_4-> installEventFilter(this);
    ui -> label_5 -> installEventFilter(this);
    ui -> label_6 -> installEventFilter(this);
    resize(600, 400);
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui -> label_4)
    {
        if (event -> type() == QEvent::MouseButtonPress)
        {
            ui -> label -> setFixedSize(180, 180);
            ui -> label -> setStyleSheet("QLabel{background-color:green; border-radius:90px;}");
        }
        if (event -> type() == QEvent::MouseButtonRelease)
        {
            ui -> label -> setStyleSheet("QLabel{}");
        }
    }
    else if (watched == ui -> label_5)
    {
        if (event -> type() == QEvent::MouseButtonPress)
        {
            ui -> label_2 -> setFixedSize(180, 180);
            QImage* img = new QImage;
            img -> load("./images/sweet_2.jpg");
            ui -> label_2 -> setPixmap(QPixmap::fromImage(*img));
        }
        if (event -> type() == QEvent::MouseButtonRelease)
        {
            ui -> label_2 -> setPixmap(QPixmap());
        }
    }
    else if (watched == ui -> label_6)
    {
        if (event -> type() == QEvent::MouseButtonPress)
        {
            ui -> label_3 -> setFixedSize(180, 180);
            ui -> label_3 -> setStyleSheet("QLabel{background-color:yellow;}");
        }
        if (event -> type() == QEvent::MouseButtonRelease)
        {
            ui -> label_3 -> setStyleSheet("QLabel{}");
        }
    }
    return QWidget::eventFilter(watched, event);
}
