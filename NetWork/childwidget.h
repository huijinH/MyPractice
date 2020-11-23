#ifndef CHILDWIDGET_H
#define CHILDWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QFile>

class ChildWidget : public QWidget
{
    Q_OBJECT
public:
    ChildWidget(QWidget* parent = nullptr);

public slots:
    void downloadBtnSlot();
    void managerFinishedSlot();
    void replayReadyRead();
    void replayProgressSlot(qint64 curSize, qint64 total);
    void replayFinished();

signals:
    void addChildWidget();

private:
    const unsigned int ReadSize = 5 * 1024 * 1024;

    QLineEdit* urlLineEdit;
    QPushButton* downloadBtn;
    QProgressBar* progressBar;
    QHBoxLayout* hBoxLayout;
    QVBoxLayout* mainLayout;

    QUrl url;
    QNetworkAccessManager* manager;
    QNetworkReply* replay = nullptr;
    QFile* file = nullptr;
    int fileSize = 0;
};

#endif // CHILDWIDGET_H
