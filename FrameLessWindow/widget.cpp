#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this -> setWindowFlags(Qt::FramelessWindowHint);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    pressPos = e -> globalPos();
    geometryPos = QPoint(this -> geometry().x(), this -> geometry().y());
    pos = (e -> globalPos()) - QPoint(this -> geometry().x(), this -> geometry().y());
    winWidth = this -> width();
    winHeight = this -> height();

    QWidget::mousePressEvent(e);
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    if (!isMax)                                              // adjust window size
    {
        if (pos.x() < SIDELEN &&                        // left top (0 ~ SIDELEN, 0 ~ SIDELEN)
                pos.y() < SIDELEN)
        {
            int offsetX, offsetY;
            offsetX = (pressPos - e -> globalPos()).x();
            offsetY = (pressPos - e -> globalPos()).y();
            winWidth += offsetX;
            winHeight += offsetY;
            this -> setGeometry(geometryPos.x() - offsetX, geometryPos.y() - offsetY,
                                winWidth, winHeight);
            // update
            pressPos = e -> globalPos();
            geometryPos = QPoint(this -> geometry().x(), this -> geometry().y());
        }
        else if (pos.x() < SIDELEN &&                        // left side (0 ~ SIDELEN, SIDELEN ~ (height - SIDELEN))
                     pos.y() > SIDELEN &&
                     pos.y() < winHeight - SIDELEN)
        {
            int offsetX;
            offsetX = (pressPos - e -> globalPos()).x();
            winWidth += offsetX;
            this -> setGeometry(geometryPos.x() - offsetX, geometryPos.y(),
                                winWidth, winHeight);
            // update
            pressPos = e -> globalPos();
            geometryPos = QPoint(this -> geometry().x(), this -> geometry().y());
        }
        else if (pos.x() < SIDELEN &&                        // left bottom (0 ~ SIDELEN, (height - SIDELEN) ~ height)
                     pos.y() > winHeight - SIDELEN)
        {
            int offsetX, offsetY;
            offsetX = (pressPos - e -> globalPos()).x();
            offsetY = (pressPos - e -> globalPos()).y();
            winWidth += offsetX;
            winHeight -= offsetY;
            this -> setGeometry(geometryPos.x() - offsetX, geometryPos.y(),
                                winWidth, winHeight);
            // update
            pos = (e -> globalPos()) - QPoint(this -> geometry().x(), this -> geometry().y());
            pressPos = e -> globalPos();
            geometryPos = QPoint(this -> geometry().x(), this -> geometry().y());
        }
        else if (pos.x() > winWidth - SIDELEN &&     // right side ((width - SIDELEN) ~ width, SIDELEN ~ (height - SIDELEN))
                pos.y() > SIDELEN &&
                pos.y() < winHeight - SIDELEN)
        {
            int offsetX;
            offsetX = (pressPos - e -> globalPos()).x();
            winWidth -= offsetX;
            this -> setGeometry(geometryPos.x(), geometryPos.y(),
                                winWidth, winHeight);
            // update
            pos = (e -> globalPos()) - QPoint(this -> geometry().x(), this -> geometry().y());
            pressPos = e -> globalPos();
            geometryPos = QPoint(this -> geometry().x(), this -> geometry().y());
        }
        else if (pos.x() > winWidth - SIDELEN &&     // right bottom ((width - SIDELEN) ~ width, (height - SIDELEN) ~ height)
                pos.y() > winHeight - SIDELEN)
        {
            int offsetX, offsetY;
            offsetX = (pressPos - e -> globalPos()).x();
            offsetY = (pressPos - e -> globalPos()).y();
            winWidth -= offsetX;
            winHeight -= offsetY;
            this -> setGeometry(geometryPos.x(), geometryPos.y(),
                                winWidth, winHeight);
            // update
            pos = (e -> globalPos()) - QPoint(this -> geometry().x(), this -> geometry().y());
            pressPos = e -> globalPos();
            geometryPos = QPoint(this -> geometry().x(), this -> geometry().y());
        }
        else if (pos.x() > SIDELEN &&                       // bottom side (SIDELEN ~ (width - SIDELEN), (height - SIDELEN) ~ height)
                pos.x() < winWidth -SIDELEN &&
                pos.y() > winHeight - SIDELEN)
        {
            int offsetY;
            offsetY = (pressPos - e -> globalPos()).y();
            winHeight -= offsetY;
            this -> setGeometry(geometryPos.x(), geometryPos.y(),
                                winWidth, winHeight);
            // update
            pos = (e -> globalPos()) - QPoint(this -> geometry().x(), this -> geometry().y());
            pressPos = e -> globalPos();
            geometryPos = QPoint(this -> geometry().x(), this -> geometry().y());
        }
        else
        {
            this -> move((e -> globalPos()) - pos);
        }
    }

    QWidget::mouseMoveEvent(e);
}

void Widget::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    if (!isMax)
    {
        this -> setWindowState(Qt::WindowMaximized);
        isMax = true;
    }
    else
    {
        this -> setWindowState(Qt::WindowNoState);
        isMax = false;
    }
}

void Widget::on_pushButton_clicked()
{
    this -> close();
}

void Widget::on_pushButton_2_clicked()
{
    if (!isMax)
    {
        this -> setWindowState(Qt::WindowMaximized);
        isMax = true;
    }
    else
    {
        this -> setWindowState(Qt::WindowNoState);
        isMax = false;
    }
}

void Widget::on_pushButton_3_clicked()
{
    this -> setWindowState(Qt::WindowMinimized);
}


