#ifndef WATCHER_H
#define WATCHER_H

#include <QObject>
#include <QFileInfoList>
#include <QFileSystemWatcher>

class Watcher : public QObject
{
    Q_OBJECT
public:
    Watcher(QObject* parent = nullptr);
    void setWatcherPath(const QString& key, const QStringList& pathList);

    QString key;


public slots:
    void fileChangedSlot(const QString& path);
    void directoryChangedSlot(const QString& path);

signals:
     void newDir(const QString&, const QStringList&);
     void delWatcher(const QString);

     void addFile(const QString &file, const QByteArray& content);
     void addDir(const QString& dir);
     void deleteFile(const QString& file);
     void deleteDir(const QString& dir);
     void renameFile(const QString& oldName, const QString& newName);
     void renameDir(const QString& oldName, const QString& newName);
     void changeFile(const QString& file, const QByteArray& content);

private:
    QStringList pathList;
    QFileSystemWatcher* watcher;
    int oldListCnt;
    QFileInfoList oldFilesList;
};

#endif // WATCHER_H
