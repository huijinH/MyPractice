#include "client.h"
#include <QDataStream>

Client::Client(QWidget *parent) : QWidget(parent)
{
    socket = new QTcpSocket;
    connect(socket, SIGNAL(connected()), this, SLOT(connectSlot()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyReadSlot()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorSlot(QAbstractSocket::SocketError)));
}

void Client::connectServer(QString hostAddr, int port)
{
    socket -> connectToHost(hostAddr, port);
}

void Client::firstSync(QString baseDir)
{
    Q_UNUSED(baseDir);
}

void Client::connectSlot()
{
    qDebug() << "connectedSlot: ";
}

void Client::readyReadSlot()
{
    qDebug() << "readyReadSlot: ";
}

void Client::disconnectedSlot()
{
    qDebug() << "disconnectedSlot: ";
}

void Client::errorSlot(QAbstractSocket::SocketError socketError)
{
    qDebug() << "errorSlot: " << socketError;
}

void Client::addFileSlot(const QString &file, const QByteArray& content)
{
    QByteArray sendByteArray;
    QDataStream stream(&sendByteArray, QIODevice::WriteOnly);
    stream << AddFile << content.size() << file << content;
    socket -> write(sendByteArray);
}

void Client::addDirSlot(const QString &dir)
{
    QByteArray sendByteArray;
    QDataStream stream(&sendByteArray, QIODevice::WriteOnly);
    stream << AddDir << dir;
    socket -> write(sendByteArray);
}

void Client::deleteFileSlot(const QString &file)
{
    QByteArray sendByteArray;
    QDataStream stream(&sendByteArray, QIODevice::WriteOnly);
    stream << DelFile << file;
    socket -> write(sendByteArray);
}

void Client::deleteDirSlot(const QString &dir)
{
    QByteArray sendByteArray;
    QDataStream stream(&sendByteArray, QIODevice::WriteOnly);
    stream << DelDir << dir;
    socket -> write(sendByteArray);
}

void Client::renameFileSlot(const QString &oldName, const QString& newName)
{
    QByteArray sendByteArray;
    QDataStream stream(&sendByteArray, QIODevice::WriteOnly);
    stream << RenameFile << oldName << newName;
    socket -> write(sendByteArray);
}

void Client::renameDirSlot(const QString &oldName, const QString& newName)
{
    QByteArray sendByteArray;
    QDataStream stream(&sendByteArray, QIODevice::WriteOnly);
    stream << RenameDir << oldName << newName;
    socket -> write(sendByteArray);
}

void Client::changeFileSlot(const QString &file, const QByteArray& content)
{
    QByteArray sendByteArray;
    QDataStream stream(&sendByteArray, QIODevice::WriteOnly);
    stream << ChangeFile << content.size() << file << content;
    socket -> write(sendByteArray);
}

