#pragma once

#include <QtWidgets/QWidget>
#include "x64/Debug/uic/ui_WinAPI.h"

class WinAPI : public QWidget
{
    Q_OBJECT

public:
    WinAPI(QWidget *parent = Q_NULLPTR);

public slots:
    void btnSlot();

private:
    Ui::WinAPIClass ui;
};
