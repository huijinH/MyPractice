#include "widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    mainLayout = new QHBoxLayout(this);

    QRegExp rx("[0-9]{3}");
    QRegExpValidator* pReg = new QRegExpValidator(rx);
    for (int i = 0; i < 4; i++)
    {
        QLineEdit* line = new QLineEdit;
        line -> setFixedHeight(30);
        line -> setFont(QFont("Microsoft yahei", 10));
        line -> setAlignment(Qt::AlignHCenter);
        line -> setStyleSheet("QLineEdit{border:0xpx;}");
        line -> setValidator(pReg);
        line -> installEventFilter(this);
        connect(line, SIGNAL(textChanged(QString)), this, SLOT(ipLineTextChangedSlot()));
        ipLineList.append(line);
        mainLayout -> addWidget(line);
    }
    setFixedSize(250, 70);
    mainLayout -> setSpacing(15);
    setPalette(Qt::white);
}

Widget::~Widget()
{

}

void Widget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::black);
    painter.setPen(pen);

    for (int i = 0; i < 4; i++)
    {
        painter.drawLine(ipLineList.at(i) -> geometry().x() + 7,
                         ipLineList.at(i) -> geometry().y() + ipLineList.at(0) -> height() + 5,
                         ipLineList.at(i) -> geometry().x() + ipLineList.at(0) -> width() - 7,
                         ipLineList.at(i) -> geometry().y() + ipLineList.at(0) -> height() + 5);
    }
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawPoint(QPoint(ipLineList.at(0) -> geometry().x() + ipLineList.at(0) -> width() + 15 / 2,
                             ipLineList.at(0) -> geometry().y() + (ipLineList.at(0) -> height()) / 2));
    painter.drawPoint(QPoint(ipLineList.at(1) -> geometry().x() + ipLineList.at(0) -> width() + 15 / 2,
                             ipLineList.at(1) -> geometry().y() + (ipLineList.at(0) -> height()) / 2));
    painter.drawPoint(QPoint(ipLineList.at(2) -> geometry().x() + ipLineList.at(0) -> width() + 15 / 2,
                             ipLineList.at(2) -> geometry().y() + (ipLineList.at(0) -> height()) / 2));
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ipLineList.at(0))
    {
        if (event -> type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvent = dynamic_cast<QKeyEvent*>(event);
            if (keyEvent -> key() == Qt::Key_Right)
            {
                    if (ipLineList.at(0) -> cursorPosition() == ipLineList.at(0) -> text().length())
                        ipLineList.at(1) -> setFocus();
            }
        }
    }
    else if (watched == ipLineList.at(1))
    {
        if (event -> type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvent = dynamic_cast<QKeyEvent*>(event);
            if (keyEvent -> key() == Qt::Key_Left)
            {
                if (ipLineList.at(1) -> cursorPosition() == 0)
                    ipLineList.at(0) -> setFocus();
            }
            else if (keyEvent -> key() == Qt::Key_Right)
            {
                if (ipLineList.at(1) -> cursorPosition() == ipLineList.at(1) -> text().length())
                    ipLineList.at(2) -> setFocus();
            }
        }
    }
    else if (watched == ipLineList.at(2))
    {
        if (event -> type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvent = dynamic_cast<QKeyEvent*>(event);
            if (keyEvent -> key() == Qt::Key_Left)
            {
                if (ipLineList.at(2) -> cursorPosition() == 0)
                    ipLineList.at(1) -> setFocus();
            }
            else if (keyEvent -> key() == Qt::Key_Right)
            {
                if (ipLineList.at(2) -> cursorPosition() == ipLineList.at(2) -> text().length())
                    ipLineList.at(3) -> setFocus();
            }
        }
    }
    else if (watched == ipLineList.at(3))
    {
        if (event -> type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvent = dynamic_cast<QKeyEvent*>(event);
            if (keyEvent -> key() == Qt::Key_Left)
            {
                if (ipLineList.at(3) -> cursorPosition() == 0)
                    ipLineList.at(2) -> setFocus();
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void Widget::ipLineTextChangedSlot()
{
    QLineEdit* line = qobject_cast<QLineEdit*>(sender());

    if (line -> text().length() == 3)
    {
        int i = 0;
        for (; i < 4; i++)
        {
            if (line == ipLineList.at(i))
                break;
        }
        if (i < 3)
            ipLineList.at(i + 1) -> setFocus();
    }
}


