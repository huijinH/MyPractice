#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QList>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class Widget;
}

enum MsgType {AddFile = 0, AddDir, DelFile, DelDir, RenameFile, RenameDir, ChangeFile};

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QString getPath(QString &path, const QString &name);
    void delDirFiles(const QString& path);

public slots:
    void newConnectionSlot();
    void connectSlot();
    void readyReadSlot();
    void disconnectedSlot();
    void errorSlot(QAbstractSocket::SocketError);

private:
    Ui::Widget *ui;
    const int port = 8090;
    QTcpServer* server;
    QList<QTcpSocket*> socketList;
    QString baseDir;
};

#endif // WIDGET_H
