#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTcpSocket>

enum MsgType {AddFile = 0, AddDir, DelFile, DelDir, RenameFile, RenameDir, ChangeFile};

class Client : public QWidget
{
    Q_OBJECT
public:
    Client(QWidget* parent = nullptr);
    void connectServer(QString hostAddr, int port);
    void firstSync(QString baseDir);

public slots:
    void connectSlot();
    void readyReadSlot();
    void disconnectedSlot();
    void errorSlot(QAbstractSocket::SocketError);

    void addFileSlot(const QString& file, const QByteArray &content);
    void addDirSlot(const QString& dir);
    void deleteFileSlot(const QString& file);
    void deleteDirSlot(const QString& dir);
    void renameFileSlot(const QString& oldName, const QString &newName);
    void renameDirSlot(const QString& oldName, const QString &newName);
    void changeFileSlot(const QString& file, const QByteArray& content);

private:
    QTcpSocket* socket;
};

#endif // CLIENT_H
