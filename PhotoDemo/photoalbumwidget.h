#ifndef PHOTOALBUMWIDGET_H
#define PHOTOALBUMWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QEvent>
#include <QList>
#include "database.h"


class PhotoAlbumWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PhotoAlbumWidget(QStringList paths, QWidget *parent = nullptr);
    ~PhotoAlbumWidget();
    bool eventFilter(QObject *watched, QEvent *event) override;

    void setBgColor(const QColor& color);
    void setAlbumName(const QString& name);

signals:
    void backSig();

public slots:
    void restoreWidget();
    void delImgSlot(int idx);

    void addBtnSlot();
    void delBtnSlot();
    void backBtnSlot();

private:

    QString albumName;
    QStringList imgPath;

    QPushButton* addBtn;
    QPushButton* delBtn;
    QPushButton* backBtn;

    QGridLayout* topLayout;
    QHBoxLayout* bottomLayout;
    QVBoxLayout* mainLayout;
    QList<QLabel*> pixLabelList;

    DataBase* dataBase = new DataBase;
};

#endif // PHOTOALBUMWIDGET_H
