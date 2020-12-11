#include "singleimgwidget.h"
#include <QDebug>

SingleImgWidget::SingleImgWidget(QWidget *parent) : QWidget(parent)
{
    setFont(QFont("Microsoft yahei", 10));

    preBtn = new QPushButton("Previous");
    connect(preBtn, SIGNAL(clicked(bool)), this, SLOT(preBtnSlot()));

    nextBtn = new QPushButton("Next");
    connect(nextBtn, SIGNAL(clicked(bool)), this, SLOT(nextBtnSlot()));

    delBtn = new QPushButton("Delete");
    connect(delBtn, SIGNAL(clicked(bool)), this, SLOT(delBtnSlot()));

    backBtn = new QPushButton("Back");
    connect(backBtn, SIGNAL(clicked(bool)), this, SLOT(backBtnSlot()));

    displayLabel = new MyLabel;
    displayLabel->setFixedSize(400, 400);

    fileNameLabel = new QLabel(" File:  ");
    fileSizeLabel = new QLabel(" Size:  ");
    createTimeLabel = new QLabel(" Created time:  ");

    vLayout = new QVBoxLayout;
    vLayout->addWidget(fileNameLabel);
    vLayout->addWidget(fileSizeLabel);
    vLayout->addWidget(createTimeLabel);

    bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(preBtn);
    bottomLayout->addWidget(nextBtn);
    bottomLayout->addWidget(delBtn);
    bottomLayout->addWidget(backBtn);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch(1);
    mainLayout->addWidget(displayLabel);
    mainLayout->addLayout(vLayout);
    mainLayout->addStretch(1);
    mainLayout->addLayout(bottomLayout);
    mainLayout->setMargin(0);
}

void SingleImgWidget::setLabelIcon(int idx)
{
    pixIdx = idx;

    displayLabel->setLocalFileName("images/" + fileNameList.at(pixIdx));

    QString txt1 = " File:  ";
    fileNameLabel->setText(txt1 + fileNameList.at(pixIdx));

    QString txt2 = " Size:  ";
    fileSizeLabel->setText(txt2 + QString::number(fileSizeList.at(pixIdx)));

    QString txt3 = " Created time:  ";
    createTimeLabel->setText(txt3 + createdTimeList.at(pixIdx));
}

void SingleImgWidget::savePixMapList(const QList<QPixmap> &list)
{
    pixMapList = list;
}

void SingleImgWidget::saveFileNameList(const QList<QString> &list)
{
    fileNameList = list;
}

void SingleImgWidget::saveFileSizeList(const QList<int> &list)
{
    fileSizeList = list;
}

void SingleImgWidget::saveCreatedTimeList(const QList<QString> &list)
{
    createdTimeList = list;
}

void SingleImgWidget::preBtnSlot()
{
    if (pixIdx - 1 < 0)
        return;
    pixIdx--;

    displayLabel->setLocalFileName("images/" + fileNameList.at(pixIdx));

    QString txt1 = " File:  ";
    fileNameLabel->setText(txt1 + fileNameList.at(pixIdx));

    QString txt2 = " Size:  ";
    fileSizeLabel->setText(txt2 + QString::number(fileSizeList.at(pixIdx)));

    QString txt3 = " Created time:  ";
    createTimeLabel->setText(txt3 + createdTimeList.at(pixIdx));
}

void SingleImgWidget::nextBtnSlot()
{
    if (pixIdx + 1 > pixMapList.count() - 1)
        return;
    pixIdx++;

    displayLabel->setLocalFileName("images/" + fileNameList.at(pixIdx));

    QString txt1 = " File:  ";
    fileNameLabel->setText(txt1 + fileNameList.at(pixIdx));

    QString txt2 = " Size:  ";
    fileSizeLabel->setText(txt2 + QString::number(fileSizeList.at(pixIdx)));

    QString txt3 = " Created time:  ";
    createTimeLabel->setText(txt3 + createdTimeList.at(pixIdx));
}

void SingleImgWidget::delBtnSlot()
{
    if (pixMapList.count() == 0)
    {
        return;
    }
    else if (pixMapList.count() == 1)
    {
        pixMapList.removeLast();
        fileNameList.removeLast();
        fileSizeList.removeLast();
        createdTimeList.removeLast();

        displayLabel->setLocalFileName("");
        fileNameLabel->setText("");
        fileSizeLabel->setText("");
        createTimeLabel->setText("");
    }
    else if (pixIdx == pixMapList.count() - 1)
    {
        preBtnSlot();
        pixMapList.removeAt(pixIdx+1);
        fileNameList.removeAt(pixIdx+1);
        fileSizeList.removeAt(pixIdx+1);
        createdTimeList.removeAt(pixIdx+1);
        emit delImg(pixIdx+1);
        return;
    }
    else
    {
        pixMapList.removeAt(pixIdx);
        fileNameList.removeAt(pixIdx);
        fileSizeList.removeAt(pixIdx);
        createdTimeList.removeAt(pixIdx);
        pixIdx--;
        nextBtnSlot();
    }

    emit delImg(pixIdx);
}

void SingleImgWidget::backBtnSlot()
{
    emit closeSingleWidget();
    delete this;
}
