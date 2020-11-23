#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui -> setupUi(this);
    childList.clear();
    addChildWidgetSlot();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::addChildWidgetSlot()
{
    if (childList.count() > 3)
        return;
    ChildWidget* childWidget = new ChildWidget(this);
    connect(childWidget, SIGNAL(addChildWidget()), this, SLOT(addChildWidgetSlot()));
    childList.append(childWidget);
    ui -> verticalLayout_2 -> addWidget(childWidget);
    ui -> verticalLayout_2 -> addStretch(1);
}

