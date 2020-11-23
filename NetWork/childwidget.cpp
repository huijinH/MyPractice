#include <QApplication>
#include <QFileInfo>
#include <QMessageBox>
#include <windows.h>
#include <QDebug>
#include "childwidget.h"

ChildWidget::ChildWidget(QWidget* parent) : QWidget(parent)
{
    this -> setWindowFlags(Qt::FramelessWindowHint);
    this -> setFixedSize(400, 100);

    urlLineEdit = new QLineEdit(this);
    urlLineEdit -> setPlaceholderText(tr("URL"));
    downloadBtn = new QPushButton(tr("Download"), this);
    connect(downloadBtn, SIGNAL(clicked(bool)), this, SLOT(downloadBtnSlot()));
    progressBar = new QProgressBar(this);
    progressBar -> setFixedWidth(377);
    progressBar -> setAlignment(Qt::AlignHCenter);

    hBoxLayout = new QHBoxLayout;
    hBoxLayout -> addWidget(urlLineEdit);
    hBoxLayout -> addWidget(downloadBtn);
    mainLayout = new QVBoxLayout(this);
    mainLayout -> addLayout(hBoxLayout);
    mainLayout -> addWidget(progressBar);

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(managerFinishedSlot()));
}

void ChildWidget::downloadBtnSlot()
{
    downloadBtn -> setEnabled(false);
    emit addChildWidget();

    url = QUrl(urlLineEdit -> text());
    file = new QFile("downloaded/" + QFileInfo(url.path()).fileName() + ".download");
    if (!(file -> open(QIODevice::WriteOnly | QIODevice::Append)))
        return;

    QNetworkRequest request;
    request.setUrl(url);
    replay = manager -> head(request);
    connect(replay, SIGNAL(readyRead()), this, SLOT(replayReadyRead()));
    connect(replay, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(replayProgressSlot(qint64,qint64)));
    connect(replay, SIGNAL(finished()), this, SLOT(replayFinished()));
}

void ChildWidget::managerFinishedSlot()
{
    qDebug() << "managerFinished";
    Sleep(200);
    fileSize = replay -> rawHeader("Content-Length").toInt();
    if (fileSize == 0)
        return;

    QNetworkRequest request;
    request.setUrl(url);
    QString range = QString("bytes=%1-%2").arg(QString::number(file -> size()))  \
            .arg(QString::number(fileSize));
    progressBar -> setRange(0, fileSize);
    request.setRawHeader("Range", range.toLocal8Bit());
    replay = manager -> get(request);
    connect(replay, SIGNAL(readyRead()), this, SLOT(replayReadyRead()));
    connect(replay, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(replayProgressSlot(qint64,qint64)));
    connect(replay, SIGNAL(finished()), this, SLOT(replayFinished()));
}

void ChildWidget::replayReadyRead()
{

    QByteArray data;
    data = replay -> read(ReadSize);
    if (data.isEmpty())
        return;
    file -> write(data);
    QCoreApplication::processEvents();
}

void ChildWidget::replayProgressSlot(qint64 curSize, qint64 total)
{
    progressBar -> setValue(file -> size());
    if (curSize == total)
    {
        file -> close();
        file -> rename("downloaded/" + QFileInfo(url.path()).fileName());
        downloadBtn -> setEnabled(true);
        return;
    }
}

void ChildWidget::replayFinished()
{
    qDebug() << "replayFinished";
}
