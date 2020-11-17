#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileSystemWatcher>
#include <QFileInfoList>
#include <QMap>
#include <QList>
#include "watcher.h"
#include "client.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void savefilesMap(const QString& basePath);
    void addWatcher(const QString& key, const QStringList& watchPathList);
    void delWatcherSlot(const QString path);

private:
    Ui::Widget *ui;
    QList<Watcher*> watcherVector;
    QMap<QString, QStringList> filesMap;
    QString baseDir;

    Client* client;
};

#endif // WIDGET_H
