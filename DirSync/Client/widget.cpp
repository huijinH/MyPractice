#include "widget.h"
#include "ui_widget.h"
#include <QDir>
#include <QFileInfo>
#include <Windows.h>
#include <QDebug>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    baseDir = qApp -> applicationDirPath() + "/RWOne_html_js";
    client = new Client;
    client -> connectServer("127.0.0.1", 8090);
    savefilesMap(baseDir);
    QMap<QString, QStringList>::const_iterator i;
    for (i = filesMap.constBegin(); i != filesMap.constEnd(); i++)
    {
        addWatcher(i.key(), i.value());
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::savefilesMap(const QString &basePath)
{
    QStringList files;
    QDir dir(basePath);
    if (dir.exists())
    {
        QFileInfoList fileDirsInfo = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
        foreach (QFileInfo path, fileDirsInfo)
        {
            if (path.isDir())
            {
                savefilesMap(path.absoluteFilePath());
            }
            else
            {
                files.append(path.absoluteFilePath());
            }
        }
    }
    filesMap.insert(basePath, files);
}

void Widget::addWatcher(const QString& key, const QStringList &watchPathList)
{
    Watcher* watcher = new Watcher;
    watcherVector.append(watcher);

    connect(watcher, SIGNAL(addFile(QString, QByteArray)), client, SLOT(addFileSlot(QString, QByteArray)));
    connect(watcher, SIGNAL(addDir(QString)), client, SLOT(addDirSlot(QString)));
    connect(watcher, SIGNAL(deleteFile(QString)), client, SLOT(deleteFileSlot(QString)));
    connect(watcher, SIGNAL(deleteDir(QString)), client, SLOT(deleteDirSlot(QString)));
    connect(watcher, SIGNAL(renameFile(QString, QString)), client, SLOT(renameFileSlot(QString, QString)));
    connect(watcher, SIGNAL(renameDir(QString, QString)), client, SLOT(renameDirSlot(QString, QString)));
    connect(watcher, SIGNAL(changeFile(QString, QByteArray)), client, SLOT(changeFileSlot(QString, QByteArray)));
    connect(watcher, SIGNAL(newDir(QString, QStringList)), this, SLOT(addWatcher(QString,QStringList)));
    connect(watcher, SIGNAL(delWatcher(QString)), this, SLOT(delWatcherSlot(QString)));

    watcher -> setWatcherPath(key, watchPathList);
}

void Widget::delWatcherSlot(const QString path)
{
    for (int i = 0; i < watcherVector.count(); i++)
    {
        if (watcherVector.at(i) -> key == path)
        {
            delete watcherVector.at(i);
            watcherVector.removeAt(i);
            QDir dir(path);
            if (dir.exists())
            {
                QFileInfoList infoList = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
                foreach (QFileInfo info, infoList)
                {
                    QFile::remove(info.absoluteFilePath());
                }

                if (dir.isEmpty())
                    Sleep(100);
                dir.rmdir(path);
            }
        }
    }
}
