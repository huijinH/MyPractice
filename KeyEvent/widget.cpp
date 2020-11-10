#include "widget.h"
#include "ui_widget.h"
#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this -> setWindowTitle(tr("键盘事件"));
    this -> setAutoFillBackground(true);
//    QPalette palette;
//    palette.setColor(QPalette::Window, Qt::white);
//    this -> setPalette(palette);
    this -> setFixedSize(800, 400);
    width = size().width();
    height = size().height();
    pix = new QPixmap(width, height);
    img.load("./image/image.jpg");
    startX = 100;
    startY = 100;
    step = 20;
    drawPix();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::drawPix()
{
    pix -> fill(Qt::yellow);
    QPainter* painter = new QPainter;
    QPen pen(Qt::DotLine);
    for (int i = step; i < width; i += step)
    {
        painter -> begin(pix);
        painter -> setPen(pen);
        painter -> drawLine(QPoint(i, 0), QPoint(i, height));
        painter -> end();
    }
    for (int i = step; i < width; i += step)
    {
        painter -> begin(pix);
        painter -> setPen(pen);
        painter -> drawLine(QPoint(0, i), QPoint(width, i));
        painter -> end();
    }
    painter -> begin(pix);
    painter -> drawImage(QPoint(startX, startY), img);
    painter -> end();
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    if (e -> modifiers() == Qt::ControlModifier)  // pressed ctrl
    {
        if (e -> key() == Qt::Key_Left)
        {
            startX = (startX - 1 < 0) ? startX : startX - 1;
        }
        if (e -> key() == Qt::Key_Right)
        {
            startX = (startX + 1 + img.width() > width) ? startX : startX + 1;
        }
        if (e -> key() == Qt::Key_Up)
        {
            startY = (startY - 1 < 0) ? startY : startY - 1;
        }
        if (e -> key() == Qt::Key_Down)
        {
            startY = (startY + 1 + img.height() > height) ? startY : startY + 1;
        }
    }
    else
    {
        startX = startX - startX % step;  // Adjust position to online
        startY = startY - startY % step;  // Adjust position to online
        if (e -> key() == Qt::Key_Left)
        {
            startX = (startX - step < 0) ? startX : startX - step;
        }
        if (e -> key() == Qt::Key_Right)
        {
            startX = (startX + step + img.width() > width) ? startX : startX + step;
        }
        if (e -> key() == Qt::Key_Up)
        {
            startY = (startY - step < 0) ? startY : startY - step;
        }
        if (e -> key() == Qt::Key_Down)
        {
            startY = (startY + step + img.height() > height) ? startY : startY + step;
        }
        if (e -> key() == Qt::Key_Home)
        {
            startX = 0;
            startY = 0;
        }
        if (e -> key() == Qt::Key_End)
        {
            startX = width - img.width();
            startY = height - img.height();
        }
    }
    drawPix();
    this -> update();
}

void Widget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(QPoint(0, 0), *pix);
    painter.end();
}
