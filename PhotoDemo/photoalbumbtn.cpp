#include "photoalbumbtn.h"

PhotoAlbumBtn::PhotoAlbumBtn(QWidget *parent) : QToolButton(parent)
{
    setFixedSize(100, 130);
    setFont(QFont("Microsoft yahei", 12));

    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

void PhotoAlbumBtn::mouseDoubleClickEvent(QMouseEvent *e)
{
    emit enterAlbum();
    QToolButton::mouseDoubleClickEvent(e);
}

