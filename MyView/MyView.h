#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MyView.h"
#include <qstandarditemmodel.h>
#include <qtableview.h>
#include <qmenubar.h>
#include <qmenu.h>
#include <qaction.h>
#include <qsplitter.h>
#include <qfile.h>
#include <qfiledialog.h>
#include <qtextstream.h>
#include <qstringlist.h>
#include "HistogramView.h"


class MyView : public QMainWindow
{
    Q_OBJECT

public:
    MyView(QWidget *parent = Q_NULLPTR);
    ~MyView();

    void createAction();
    void createMenu();
    void setupModel();
    void setupView();

public slots:
    void openFileSlot();


private:
    Ui::MyViewClass ui;
    QMenu* fileMenu;
    QAction* openAction;
    QStandardItemModel* model;
    QTableView* tableView;
    QSplitter* splitter;

    HistogramView* histogram;
};
