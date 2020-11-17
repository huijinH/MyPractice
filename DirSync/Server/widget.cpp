#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QIODevice>
#include <QDataStream>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    baseDir = qApp -> applicationDirPath() + "/RWOne_html_js";
    server = new QTcpServer;
    if (server -> listen(QHostAddress::AnyIPv4, port))
    {
        qDebug() << "listening...";
    }
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnectionSlot()));
}

Widget::~Widget()
{
    delete ui;
}

QString Widget::getPath(QString &path, const QString& name)
{
    QStringList tmpStrList;
    tmpStrList = path.split("/");
    tmpStrList.removeLast();
    if (tmpStrList.last() == "RWOne_html_js")
    {
        path = baseDir + "/" +name;
        return path;
    }
    else
    {
        for (;;)
        {
            tmpStrList.removeFirst();
            if (tmpStrList.at(0) == "RWOne_html_js")
            {
                tmpStrList.removeFirst();
                break;
            }
        }
        path = baseDir + "/" + tmpStrList.join("/") + "/" + name;
        return path;
    }
}

void Widget::delDirFiles(const QString &path)
{
    QDir dir(path);
    QFileInfoList infoList = dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    foreach (QFileInfo info, infoList)
    {
        QString infoPath = info.absoluteFilePath();
        if (info.isFile())
        {
            QFile::remove(infoPath);
        }
        else if (info.isDir())
        {
            if (QDir(infoPath).isEmpty())
            {
                QDir(infoPath).rmdir(infoPath);
            }
            else
            {
                delDirFiles(infoPath);
            }
        }
    }
}

void Widget::newConnectionSlot()
{
    qDebug() << "connectedSlot: ";

    QTcpSocket* s = server ->nextPendingConnection();
    socketList.append(s);
    connect(s, SIGNAL(connected()), this, SLOT(connectSlot()));
    connect(s, SIGNAL(readyRead()), this, SLOT(readyReadSlot()));
    connect(s, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));
    connect(s, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorSlot(QAbstractSocket::SocketError)));
}

void Widget::connectSlot()
{
    qDebug() << "connectSlot: ";
}

void Widget::readyReadSlot()
{
    qDebug() << "readyReadSlot: ";
    QTcpSocket* s = qobject_cast<QTcpSocket*>(this -> sender());
    QDataStream stream(s);

    int msgType;
    int fileSize;
    QString path, oldName, newName, name;
    QByteArray content;
    QFile file;
    QDir dir;
    stream >> msgType;

    //    while (!stream.atEnd())
    {
        switch (msgType)
        {
        case AddFile:
            stream >> fileSize;
            stream >> path;
            name = QFileInfo(path).fileName();
            path = getPath(path, name);
            stream >> content;
            file.setFileName(path);
            if (file.open(QIODevice::WriteOnly))
            {
                file.write(content);
            }
            file.close();
            break;
        case AddDir:
            stream >> path;
            name = path.split("/").last();
            path = getPath(path, name);
            dir.mkdir(path);
            break;
        case DelFile:
            stream >> path;
            name = QFileInfo(path).fileName();
            path = getPath(path, name);
            QFile::remove(path);
            break;
        case DelDir:
            stream >> path;
            name = path.split("/").last();
            path = getPath(path, name);
            delDirFiles(path);
            dir.setPath(path);
            dir.rmdir(path);
            break;
        case RenameFile:
            stream >> oldName;
            oldName = getPath(oldName, QFileInfo(oldName).fileName());
            stream >> newName;
            newName = getPath(newName, QFileInfo(newName).fileName());
            file.setFileName(oldName);
            file.rename(newName);
            break;
        case RenameDir:
            stream >> oldName;
            oldName = getPath(oldName, oldName.split("/").last());
            stream >> newName;
            newName = getPath(newName, newName.split("/").last());
            dir.setPath(oldName);
            dir.rename(oldName, newName);
            break;
        case ChangeFile:
            stream >> fileSize;
            stream >> path;
            name = QFileInfo(path).fileName();
            path = getPath(path, name);
            stream >> content;
            file.setFileName(path);
            if (file.open(QIODevice::WriteOnly))
            {
                file.write(content);
            }
            file.close();
            break;
        }
    }
}

void Widget::disconnectedSlot()
{
    qDebug() << "disconnectedSlot: ";
    socketList.removeOne(qobject_cast<QTcpSocket*>(this -> sender()));
}

void Widget::errorSlot(QAbstractSocket::SocketError)
{
    qDebug() << "errorSlot: ";
    socketList.removeOne(qobject_cast<QTcpSocket*>(this -> sender()));
}
