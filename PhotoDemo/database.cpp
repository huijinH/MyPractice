#include "database.h"
#include <QDebug>

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{
    db.close();
}

void DataBase::saveImg(const QString &imgFileName)
{
    QFile inImg(imgFileName);
    if (!inImg.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(nullptr, "Error", "Open image file failed!");
        return;
    }
    fileNameList.append(QFileInfo(inImg).fileName());
    fileSizeList.append(inImg.size());
    createdTimeList.append(QFileInfo(inImg).created().toString("yyyy-MM-dd hh:mm:ss"));

    QByteArray inData = inImg.readAll();
    query.prepare("INSERT INTO imageTable (filename, imgdata, size, datetime) VALUES (:filename, :imgdata, :size, :datetime)");
    query.bindValue(":filename", inImg.fileName());
    query.bindValue(":imgdata", inData);
    query.bindValue(":size", inImg.size());
    query.bindValue(":datetime", QFileInfo(inImg).created().toString("yyyy-MM-dd hh:mm:ss"));
    if (!query.exec())
    {
        QMessageBox::warning(nullptr, "Error", QString("Fail to insert image to imageTable\n%1").arg(query.lastError().text()));
        return;
    }
    qDebug() << "insert: " << QFileInfo(inImg).fileName();
}

void DataBase::setMaxId()
{
    query.prepare("select max(id) from imageTable");
    if (!query.exec())
    {
        qDebug() << query.lastError();
        return;
    }
    while(query.next())
        maxId = query.value(0).toInt();
}

void DataBase::retrieveImg()
{
    if (!query.exec("SELECT imgdata from imageTable"))
    {
        QMessageBox::warning(nullptr, "Error", "Fail to get image from imageTable");
        return;
    }

    while (query.next())
    {
        QPixmap outImg;
        QByteArray data = query.value(0).toByteArray();
        outImg.loadFromData(data);
        pixList.append(outImg);
    }
}

void DataBase::delData(const QString &fileName)
{
    query.prepare("delete from imageTable where filename = ?");
    query.addBindValue(fileName);
    if (!query.exec())
    {
        QMessageBox::warning(nullptr, "Error", "Fail to delete data from imageTable");
        return;
    }
    else
    {
        qDebug() << "database delete " << fileName;

        for (int i = 0; i < fileNameList.count(); i++)
        {
            if (fileName.split("/").last() == fileNameList.at(i))
            {
                pixList.removeAt(i);
                fileNameList.removeAt(i);
                fileSizeList.removeAt(i);
                createdTimeList.removeAt(i);
            }
        }
    }
}

void DataBase::openDB(const QString &dbName)
{
    QFile::remove(dbName);

    if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else
      db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(dbName);
    if (!db.open())
    {
        QMessageBox::warning(nullptr, "Error", "Open database error!");
        return;
    }
    query = QSqlQuery(db);
    query.exec("CREATE TABLE IF NOT EXISTS imageTable (filename TEXT, imgdata BLOB, size INTEGER, datetime TEXT)");
}
