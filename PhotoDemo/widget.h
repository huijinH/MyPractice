#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QList>
#include <QMap>
#include <QFileDialog>
#include "photoalbumbtn.h"

extern QMap<QString, QStringList> albumMap;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void setBgColor(const QColor& color);

public slots:
    void enterAlbumSlot();
    void closeAlbumSlot();

    void addAlbumBtnSlot();
    void delAlbumBtnSlot();

private:
    Ui::Widget *ui;

    QPushButton* addAlbumBtn;
    QPushButton* delAlbumBtn;
    QHBoxLayout* bottomLayout;

//    QMap<QString, QStringList> albumMap;
    QList<PhotoAlbumBtn*> btnlList;
    QGridLayout* topLayout;
};

#endif // WIDGET_H
