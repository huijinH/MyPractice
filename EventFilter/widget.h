#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QImage>
#include <QEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
