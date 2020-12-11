#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QFileInfo>
#include <QDateTime>
#include <QList>
#include <QVariant>

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();
    void saveImg(const QString& imgFileName);
    void setMaxId();
    void retrieveImg();
    void delData(const QString& fileName);

signals:

public slots:
    void openDB(const QString& dbName);

public:
    int maxId;
    QList<QPixmap> pixList;
    QList<QString> fileNameList;
    QList<int> fileSizeList;
    QList<QString> createdTimeList;

private:
    QSqlQuery query;
    QSqlDatabase db;
};

#endif // DATABASE_H
