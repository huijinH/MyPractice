#ifndef PHOTOALBUMBTN_H
#define PHOTOALBUMBTN_H

#include <QWidget>
#include <QToolButton>
#include <QMouseEvent>

class PhotoAlbumBtn : public QToolButton
{
    Q_OBJECT
public:
    PhotoAlbumBtn(QWidget* parent = nullptr);
    void mouseDoubleClickEvent(QMouseEvent* e) override;

signals:
    void enterAlbum();
};

#endif // PHOTOALBUMBTN_H
