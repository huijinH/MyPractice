#include "widget.h"
#include "ui_widget.h"
#include "photoalbumwidget.h"
#include <QDebug>

QMap<QString, QStringList> albumMap;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setBgColor(Qt::white);
    setFont(QFont("Microsoft yahei", 10));

    topLayout = new QGridLayout;
    topLayout->setAlignment(Qt::AlignTop);

    addAlbumBtn = new QPushButton("新建相册");
    connect(addAlbumBtn, SIGNAL(clicked(bool)), this, SLOT(addAlbumBtnSlot()));
    delAlbumBtn = new QPushButton("删除相册");
    connect(delAlbumBtn, SIGNAL(clicked(bool)), this, SLOT(delAlbumBtnSlot()));

    bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(addAlbumBtn);
    bottomLayout->addWidget(delAlbumBtn);
    bottomLayout->setAlignment(Qt::AlignBottom);

    ui->verticalLayout->addLayout(topLayout);
    ui->verticalLayout->addLayout(bottomLayout);
    ui->verticalLayout->setMargin(0);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setBgColor(const QColor &color)
{
    QPalette palette;
    palette.setColor(QPalette::Background, color);
    setAutoFillBackground(true);
    setPalette(palette);
}

void Widget::enterAlbumSlot()
{
    addAlbumBtn->setVisible(false);
    delAlbumBtn->setVisible(false);
    for (int i = 0; i < btnlList.count(); i++)
        btnlList.at(i)->setVisible(false);

    QString tmpKey = dynamic_cast<PhotoAlbumBtn*>(sender())->text();
    PhotoAlbumWidget* ptw = new PhotoAlbumWidget(albumMap.value(tmpKey));
    ptw->setAlbumName(tmpKey);
    connect(ptw, SIGNAL(backSig()), this, SLOT(closeAlbumSlot()));
    ui->verticalLayout->addWidget(ptw);
    ui->verticalLayout->setMargin(0);
}

void Widget::closeAlbumSlot()
{
    addAlbumBtn->setVisible(true);
    delAlbumBtn->setVisible(true);
    for (int i = 0; i < btnlList.count(); i++)
        btnlList.at(i)->setVisible(true);
}

void Widget::addAlbumBtnSlot()
{
    QDialog* dlg = new QDialog;

    QStringList filePaths;

    QLabel* albumNameLabel = new QLabel("相册名称：", dlg);
    QLineEdit* albumNameLineEdit = new QLineEdit(dlg);

    QLabel* selectImgLabel = new QLabel("已选图片：", dlg);
    QLabel* selectedLabel = new QLabel(dlg);
    QPushButton* selectImgBtn = new QPushButton("选择图片", dlg);
    connect(selectImgBtn, &QPushButton::clicked, [&](){
        filePaths = QFileDialog::getOpenFileNames(this, "选择图片", ".", "Images (*.png *.jpeg *.jpg)");
        selectedLabel->setText(QString("%1 张").arg(filePaths.count()));
    });

    QPushButton* cancelBtn = new QPushButton("取消", dlg);
    connect(cancelBtn, &QPushButton::clicked, [&](){
        dlg->close();
    });

    QPushButton* okBtn = new QPushButton("确定", dlg);
    connect(okBtn, &QPushButton::clicked, [&](){
        albumMap.insert(albumNameLineEdit->text(), filePaths);
        dlg->close();
    });


    QGridLayout* dlgLayout = new QGridLayout(dlg);
    dlgLayout->addWidget(albumNameLabel, 0, 0);
    dlgLayout->addWidget(albumNameLineEdit, 0, 1, 1, 2);
    dlgLayout->addWidget(selectImgLabel, 1, 0);
    dlgLayout->addWidget(selectedLabel, 1, 1);
    dlgLayout->addWidget(selectImgBtn, 1, 2);
    dlgLayout->addWidget(cancelBtn, 2, 0);
    dlgLayout->addWidget(okBtn, 2, 2);

    dlg->exec();

    QMap<QString, QStringList>::const_iterator itor;
    int i = 0;
    for (itor = albumMap.begin(); itor != albumMap.end(); itor++)
    {
        PhotoAlbumBtn* photoAlbumBtn = new PhotoAlbumBtn(this);
        btnlList.append(photoAlbumBtn);
        connect(photoAlbumBtn, SIGNAL(enterAlbum()), this, SLOT(enterAlbumSlot()));
        photoAlbumBtn->setText(itor.key());
        if (itor.value().count() > 0)
            photoAlbumBtn->setIcon(QIcon(itor.value().first()));
        else
            photoAlbumBtn->setIcon(QIcon());
        photoAlbumBtn->setIconSize(QSize(100, 100));
        topLayout->addWidget(photoAlbumBtn, i / 4, i % 4);
        i++;
    }
}

void Widget::delAlbumBtnSlot()
{

}
