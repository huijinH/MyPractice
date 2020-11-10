#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QString>

MainWindow::MainWindow(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this -> setWindowTitle(tr("鼠标事件"));
    this -> resize(600, 400);

    statusLabel = new QLabel;
    statusLabel -> setFixedWidth(100);
    posLabel = new QLabel;
    posLabel -> setFixedWidth(100);
    this -> statusBar() -> addPermanentWidget(statusLabel);
    this -> statusBar() -> addPermanentWidget(posLabel);
    this -> setMouseTracking(true);  // Set real-time mouse tracking
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    QString posStr;
    posStr = QString::number(e -> x()) + ", " + QString::number(e -> y());
    posLabel -> setText(posStr);

    QMainWindow::mouseMoveEvent(e);
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    QString statusPos = QString::number(e -> x()) + ", " + QString::number(e -> y());
    if (e -> button() == Qt::LeftButton)
    {
        statusLabel -> setText(tr("左键 ") + statusPos);
    }
    else if (e -> button() == Qt::MidButton)
    {
        statusLabel -> setText(tr("中键 ") + statusPos);
    }
    else if (e -> button() == Qt::RightButton)
    {
        statusLabel -> setText(tr("右键 ") + statusPos);
    }

    QMainWindow::mousePressEvent(e);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    QString statusPos = QString::number(e -> x()) + ", " + QString::number(e -> y());
    statusLabel -> setText(tr("释放 ") + statusPos);

    QMainWindow::mouseReleaseEvent(e);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *e)
{
    QString statusPos = QString::number(e -> x()) + ", " + QString::number(e -> y());
    statusLabel -> setText(tr("双击 ") + statusPos);

//    QMainWindow::mouseDoubleClickEvent(e);  // Open will not trigger double click event
}

