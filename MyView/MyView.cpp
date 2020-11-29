#include "MyView.h"
#include <qitemselectionmodel.h>

#pragma execution_character_set("utf-8")

MyView::MyView(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setWindowTitle(tr("View Example"));
    createAction();
    createMenu();
    setupModel();
    setupView();
    resize(600, 600);
}

MyView::~MyView()
{
}

void MyView::createAction()
{
    openAction = new QAction(tr("Open"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(openFileSlot()));
}

void MyView::createMenu()
{
    fileMenu = new QMenu(tr("File"), this);
    fileMenu->addAction(openAction);
    menuBar()->addMenu(fileMenu);
}

void MyView::setupModel()
{
    model = new QStandardItemModel(4, 4, this);
    model->setHeaderData(0, Qt::Horizontal, tr("部门"));
    model->setHeaderData(1, Qt::Horizontal, tr("男"));
    model->setHeaderData(2, Qt::Horizontal, tr("女"));
    model->setHeaderData(3, Qt::Horizontal, tr("退休"));
}

void MyView::setupView()
{
    splitter = new QSplitter;
    splitter->setOrientation(Qt::Vertical);

    histogram = new HistogramView(splitter);
    histogram->setModel(model);

    tableView = new QTableView;
    tableView->setModel(model);

    QItemSelectionModel* selectionModel = new QItemSelectionModel(model);
    tableView->setSelectionModel(selectionModel);
    histogram->setSelectionModel(selectionModel);

    splitter->addWidget(tableView);
    splitter->addWidget(histogram);
    setCentralWidget(splitter);

    connect(selectionModel, SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
        tableView, SLOT(selectionChanged(QItemSelection, QItemSelection)));
    connect(selectionModel, SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
        histogram, SLOT(selectionChanged(QItemSelection, QItemSelection)));
}

void MyView::openFileSlot()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, "打开", ".", "histogram files(*.txt)");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return;
    QTextStream stream(&file);
    QString line;
    model->removeRows(0, model->rowCount(QModelIndex()), QModelIndex());
    int row = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            model->insertRows(row, 1, QModelIndex());
            QStringList pieces = line.split(",", QString::SkipEmptyParts);
            model->setData(model->index(row, 0, QModelIndex()), pieces.value(0));
            model->setData(model->index(row, 1, QModelIndex()), pieces.value(1));
            model->setData(model->index(row, 2, QModelIndex()), pieces.value(2));
            model->setData(model->index(row, 3, QModelIndex()), pieces.value(3));
            row++;
        }
    } while (!line.isEmpty());
    file.close();
}