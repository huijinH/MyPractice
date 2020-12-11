#include "photoalbumwidget.h"
#include "singleimgwidget.h"
#include <QDir>
#include <QDebug>

extern QMap<QString, QStringList> albumMap;

PhotoAlbumWidget::PhotoAlbumWidget(QStringList paths, QWidget *parent) : imgPath(paths),  QWidget(parent)
{
    setFont(QFont("Microsoft yahei", 10));
    setFixedSize(400, 600);
    setBgColor(Qt::black);

    dataBase = new DataBase;
    dataBase->openDB("mydb.db3");
    for (int i = 0; i < imgPath.count(); i++)
        dataBase->saveImg(imgPath.at(i));

    dataBase->retrieveImg();

    topLayout = new QGridLayout;
    topLayout->setAlignment(Qt::AlignTop);
    topLayout->setMargin(11);

    for (int i = 0; i < dataBase->pixList.count(); i++)
    {
        QLabel* label = new QLabel(this);
        label->setStyleSheet("QLabel:hover{border-width:2px; border-style:solid; border-color:gray;}");
        label->installEventFilter(this);
        pixLabelList.append(label);
        label->setFixedSize(90, 90);
        QPixmap tmpPix = dataBase->pixList.at(i).scaled(label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        label->setPixmap(tmpPix);
        topLayout->addWidget(label, i / 4, i % 4);
    }

    addBtn = new QPushButton("Add");
    connect(addBtn, SIGNAL(clicked(bool)), this, SLOT(addBtnSlot()));
    delBtn = new QPushButton("Delete");
    connect(delBtn, SIGNAL(clicked(bool)), this, SLOT(delBtnSlot()));
    backBtn = new QPushButton("Back");
    connect(backBtn, SIGNAL(clicked(bool)), this, SLOT(backBtnSlot()));

    bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(addBtn);
    bottomLayout->addWidget(delBtn);
    bottomLayout->addWidget(backBtn);
    bottomLayout->setAlignment(Qt::AlignBottom);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);
    mainLayout->setMargin(0);
}

PhotoAlbumWidget::~PhotoAlbumWidget()
{
    dataBase->deleteLater();
}

bool PhotoAlbumWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick)
    {
        addBtn->setVisible(false);
        delBtn->setVisible(false);
        backBtn->setVisible(false);

        setBgColor(Qt::white);

        int idx = 0;
        for (int i = 0; i < pixLabelList.count(); i++)
        {
            pixLabelList.at(i)->setVisible(false);
            if (watched == pixLabelList.at(i))
                idx = i;
        }

        SingleImgWidget* imgWidget = new SingleImgWidget(this);
        connect(imgWidget, SIGNAL(delImg(int)), this, SLOT(delImgSlot(int)));
        connect(imgWidget, SIGNAL(closeSingleWidget()), this, SLOT(restoreWidget()));
        imgWidget->savePixMapList(dataBase->pixList);
        imgWidget->saveFileNameList(dataBase->fileNameList);
        imgWidget->saveFileSizeList(dataBase->fileSizeList);
        imgWidget->saveCreatedTimeList(dataBase->createdTimeList);
        imgWidget->setLabelIcon(idx);

        topLayout->addWidget(imgWidget);
        topLayout->setAlignment(Qt::AlignCenter);
        topLayout->setMargin(0);
    }
    else if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* e = dynamic_cast<QMouseEvent*>(event);
        if (e -> button() == Qt::LeftButton)
        {
        }
    }

    return QWidget::eventFilter(watched, event);
}

void PhotoAlbumWidget::setBgColor(const QColor &color)
{
    QPalette palette;
    palette.setColor(QPalette::Background, color);
    setAutoFillBackground(true);
    setPalette(palette);
}

void PhotoAlbumWidget::setAlbumName(const QString &name)
{
    albumName = name;
}

void PhotoAlbumWidget::restoreWidget()
{
    for (int i = 0; i < pixLabelList.count(); i++)
    {
        pixLabelList.at(i)->setVisible(true);
        topLayout->setAlignment(Qt::AlignTop);
        topLayout->setMargin(11);
    }
    addBtn->setVisible(true);
    delBtn->setVisible(true);
    backBtn->setVisible(true);
    setBgColor(Qt::black);
}

void PhotoAlbumWidget::delImgSlot(int idx)
{
    QStringList t = albumMap.value(albumName);
    t.removeAt(idx);
    albumMap.insert(albumName, t);
    dataBase->delData("images/" + dataBase->fileNameList.at(idx));

    pixLabelList.removeAt(idx);
    for (int i = 0; i < pixLabelList.count(); i++)
        topLayout->addWidget(pixLabelList.at(i), i / 4, i % 4);
}

void PhotoAlbumWidget::addBtnSlot()
{

}

void PhotoAlbumWidget::delBtnSlot()
{

}

void PhotoAlbumWidget::backBtnSlot()
{
    emit backSig();
    delete this;
}
