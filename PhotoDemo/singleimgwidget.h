#ifndef SINGLEIMGWIDGET_H
#define SINGLEIMGWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QList>
#include "mylabel.h"

/*   展示单独图片大图的界面
* 1，大图展示
* 2，详细信息展示
* 3，上一张，下一张
* 4，放大，缩小
* 5，删除
* 6，返回
*/

class SingleImgWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SingleImgWidget(QWidget *parent = nullptr);
    void setLabelIcon(int idx);
    void savePixMapList(const QList<QPixmap>& list);
    void saveFileNameList(const QList<QString>& list);
    void saveFileSizeList(const QList<int>& list);
    void saveCreatedTimeList(const QList<QString>& list);

signals:
    void delImg(int idx);
    void closeSingleWidget();

public slots:
    void preBtnSlot();
    void nextBtnSlot();
    void delBtnSlot();
    void backBtnSlot();

private:
    int pixIdx = 0;

    QPushButton* preBtn;
    QPushButton* nextBtn;
    QPushButton* delBtn;
    QPushButton* backBtn;

    MyLabel* displayLabel = nullptr;
    QLabel* fileNameLabel;
    QLabel* fileSizeLabel;
    QLabel* createTimeLabel;

    QHBoxLayout* bottomLayout;
    QVBoxLayout* vLayout;
    QVBoxLayout* mainLayout;

    QList<QPixmap> pixMapList;
    QList<QString> fileNameList;
    QList<int> fileSizeList;
    QList<QString> createdTimeList;
};

#endif // SINGLEIMGWIDGET_H
