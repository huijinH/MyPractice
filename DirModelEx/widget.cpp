#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QTextEdit>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui -> setupUi(this);
    resize(1400, 800);
    setWindowTitle(tr("Model/View"));

    setUpWidget();

    ui -> tabWidget->setTabEnabled(0, false);
    ui -> tabWidget->setTabEnabled(1, false);
    ui -> tabWidget -> setStyleSheet("QTabBar::tab:disabled {width: 0; color: transparent;}");
    ui -> tabWidget -> addTab(new QTextEdit, tr("empty"));
    ui -> tabWidget -> setCurrentIndex(2);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setUpWidget()
{
    QDirModel* model = new QDirModel;

    QTreeView* tree = new QTreeView;
    QListView* list = new QListView;
    QTableView* table = new QTableView;

    tree -> setModel(model);
    list -> setModel(model);
    table -> setModel(model);

    tree -> setSelectionMode(QAbstractItemView::SingleSelection);
    list -> setSelectionMode(QAbstractItemView::SingleSelection);
    table -> setSelectionMode(QAbstractItemView::SingleSelection);

    connect(tree, SIGNAL(doubleClicked(QModelIndex)), list, SLOT(setRootIndex(QModelIndex)));
    connect(tree, SIGNAL(doubleClicked(QModelIndex)), table, SLOT(setRootIndex(QModelIndex)));
    connect(list, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(showItemConetent(QModelIndex)));

    QSplitter* splitter = new QSplitter;
    splitter -> addWidget(tree);
    splitter -> addWidget(list);
    splitter -> addWidget(table);

    QHBoxLayout* layout = new QHBoxLayout(ui -> upwWidget);
    layout -> addWidget(splitter);
}

void Widget::showItemConetent(QModelIndex model)
{
    int tabCnt = ui -> tabWidget -> count();

    QStringList strList;
    QString fileName = model.data().toString();
    for (;;)
    {
        QString str;
        model = model.parent();
        str = model.data().toString();
        if (str == "")
            break;
        strList.append(str);
    }
    QString filePath = "";
    for (int i = strList.count() - 1; i >= 0; i--)
        filePath += strList.at(i) + "/";

    filePath += fileName;
    QFileInfo fileInfo(filePath);
    if (fileInfo.suffix() == "txt"  ||
        fileInfo.suffix() == "html" ||
        fileInfo.suffix() == "js"   ||
        fileInfo.suffix() == "css"  ||
        fileInfo.suffix() == "c"    ||
        fileInfo.suffix() == "cpp"  ||
        fileInfo.suffix() == "h"    ||
        fileInfo.suffix() == "py"   ||
        fileInfo.suffix() == "go")
    {
        QByteArray data;
        QFile file(filePath);
        if (!(file.open(QIODevice::ReadOnly)))
            return;
        data = file.readAll();
        file.close();
        qobject_cast<QTextEdit*>(ui -> tabWidget -> widget(tabCnt - 1)) -> setText(data);
        ui -> tabWidget -> setTabText(tabCnt - 1, fileName);
        ui -> tabWidget -> setCurrentIndex(tabCnt - 1);
        ui -> tabWidget -> addTab(new QTextEdit, tr("empty"));
    }
    else if (fileInfo.suffix().toLower() == "jpg"  ||
             fileInfo.suffix().toLower() == "jpeg" ||
             fileInfo.suffix().toLower() == "png"  ||
             fileInfo.suffix().toLower() == "bmp")
    {
        qobject_cast<QTextEdit*>(ui -> tabWidget -> widget(tabCnt - 1)) -> append("<img src=\"" + filePath + "\" />");
        ui -> tabWidget -> setTabText(tabCnt - 1, fileName);
        ui -> tabWidget -> setCurrentIndex(tabCnt - 1);
        ui -> tabWidget -> addTab(new QTextEdit, tr("empty"));
    }
}
