#include "watcher.h"
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QDateTime>
#include <QDebug>

Watcher::Watcher(QObject* parent) : QObject(parent)
{   
    watcher = new QFileSystemWatcher(this);
    connect(watcher, SIGNAL(fileChanged(QString)), this, SLOT(fileChangedSlot(QString)), Qt::UniqueConnection);
    connect(watcher, SIGNAL(directoryChanged(QString)), this, SLOT(directoryChangedSlot(QString)), Qt::UniqueConnection);
}

void Watcher::setWatcherPath(const QString& key, const QStringList &pathList)
{
    this -> oldFilesList = QDir(key).entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    this -> key = key;
    this -> pathList = pathList;
    oldListCnt = pathList.count();
    watcher -> addPath(key);
    if (pathList.count() > 0)
        watcher -> addPaths(pathList);
}

void Watcher::fileChangedSlot(const QString &path)
{
    if (QFileInfo(path).exists())
    {
        // Solve the repeated trigger problem
        static QString prevTimeStr = "0000-00-00-00-00-00-000";
        QStringList prevTimeStrList = prevTimeStr.split("-");
        QString nowTimeStr = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss-zzz");
        QStringList nowTimeStrList = nowTimeStr.split("-");
        if ((QString(nowTimeStrList.at(2)).toInt() - QString(prevTimeStrList.at(2)).toInt()) > 0 ||
                (QString(nowTimeStrList.at(3)).toInt() - QString(prevTimeStrList.at(3)).toInt()) > 0 ||
                (QString(nowTimeStrList.at(4)).toInt() - QString(prevTimeStrList.at(4)).toInt()) > 0 ||
                (QString(nowTimeStrList.at(5)).toInt() - QString(prevTimeStrList.at(5)).toInt()) > 0 ||
                (QString(nowTimeStrList.at(6)).toInt() - QString(prevTimeStrList.at(6)).toInt()) > 500
                )
        {
            QByteArray content;
            QFile file(path);
            if (file.open(QIODevice::ReadOnly))
            {
                content = file.readAll();
            }
            file.close();
            emit changeFile(path, content);
            qDebug() << "key: " << key;
            qDebug() << "file changed: " << path;
        }
        prevTimeStr = nowTimeStr;
    }
}

void Watcher::directoryChangedSlot(const QString &path)
{
    Q_UNUSED(path);
    qDebug() << "key: " << key;
    bool isDelSelf = true;
    QFileInfoList nowFileInfoList = QDir(key).entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    int nowFilesCnt = nowFileInfoList.count();
    if (nowFilesCnt < oldFilesList.count())
    {
        int nowfile = 0;
        foreach (QFileInfo info, nowFileInfoList)
        {
            if (info.isFile())
                nowfile++;
        }
        if (nowfile < pathList.count())
        {
            qDebug() << "delete file";
            QFileInfo removedFileInfo;
            foreach (QString str, this -> pathList)
            {
                if (!nowFileInfoList.contains(QFileInfo(str)))
                {
                    removedFileInfo = QFileInfo(str);
                    emit deleteFile(str);
                    isDelSelf = false;
                    this -> pathList.removeOne(str);
                    break;
                }
            }
            this -> pathList.removeOne(removedFileInfo.absoluteFilePath());
        }
        else
        {
            qDebug() << "delete dir";
            foreach (QFileInfo info, oldFilesList)
            {
                if (!nowFileInfoList.contains(info))
                {
                    emit deleteDir(info.absoluteFilePath());
                    isDelSelf = false;
                    break;
                }
            }
            oldFilesList = QDir(key).entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
            return;
        }
    }
    else if (nowFilesCnt > oldFilesList.count())
    {
        // add
        foreach (QFileInfo info, nowFileInfoList)
        {
            if (oldFilesList.contains(info))
                nowFileInfoList.removeOne(info);
        }
        if (nowFileInfoList.last().isDir())
        {
            qDebug() << "add dir";
            emit newDir(nowFileInfoList.last().absoluteFilePath(), QStringList());
            emit addDir(nowFileInfoList.last().absoluteFilePath());
            isDelSelf = false;
            oldFilesList = QDir(key).entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
            return;
        }
        qDebug() << "add file";
        QString filePath = nowFileInfoList.last().absoluteFilePath();
        QFile file(filePath);
        QByteArray content;
        if (file.open(QIODevice::ReadOnly))
        {
            content = file.readAll();
        }
        file.close();
        emit addFile(filePath, content);
        isDelSelf = false;
        this -> pathList.append(filePath);
        watcher -> addPath(filePath);
    }
    else
    {
        QStringList tmpInfoList;
        foreach (QFileInfo info, nowFileInfoList)
        {
            if (info.isFile())
                tmpInfoList.append(info.absoluteFilePath());
        }
        if (tmpInfoList == this -> pathList && !QDir(key).isEmpty())
        {
            qDebug() << "dir rename";
            QString oldName, newName;
            foreach (QFileInfo info, nowFileInfoList)
            {
                if (!oldFilesList.contains(info))
                {
                    emit newDir(info.absoluteFilePath(), QStringList());
                    newName = info.absoluteFilePath();
                    break;
                }
            }
            foreach (QFileInfo info, oldFilesList)
            {
                if (!nowFileInfoList.contains(info))
                {
                    oldName = info.absoluteFilePath();
                    emit delWatcher(oldName);
                    emit renameDir(oldName, newName);
                    isDelSelf = false;
                    watcher -> removePath(oldName);
                    break;
                }
            }
        }
        else if (!QDir(key).isEmpty())
        {
            qDebug() << "file rename";
            QString oldName, newName;
            foreach (QString path, tmpInfoList)
            {
                if (!(this -> pathList.contains(path)))
                {
                    newName = path;
                    this -> pathList.append(path);
                    watcher -> addPath(path);
                    break;
                }
            }
            foreach (QString path, this -> pathList)
            {
                if (!tmpInfoList.contains(path))
                {
                    oldName = path;
                    emit renameFile(oldName, newName);
                    isDelSelf = false;
                    this -> pathList.removeOne(oldName);
                    watcher -> removePath(path);
                    break;
                }
            }
        }
    }
    oldFilesList = QDir(key).entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    if (isDelSelf)
    {
        emit delWatcher(this -> key);
    }
}
