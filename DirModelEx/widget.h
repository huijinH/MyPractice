#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QDirModel>
#include <QTreeView>
#include <QListView>
#include <QTableView>
#include <QSplitter>
#include <QHBoxLayout>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void setUpWidget();

public slots:
    void showItemConetent(QModelIndex model);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
