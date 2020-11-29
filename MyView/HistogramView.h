#pragma once
#include <qabstractitemview.h>
#include <qitemselectionmodel.h>
#include <qregion.h>
#include <QMouseEvent>

class HistogramView :
    public QAbstractItemView
{
    Q_OBJECT
public:
    HistogramView(QWidget* parent = nullptr);

    // virsual func; Unnecessary to implement, but need declaration
    QRect visualRect(const QModelIndex& index) const 
    {
        return QRect();
    }
    void scrollTo(const QModelIndex& index, ScrollHint hint = EnsureVisible) {}
    QModelIndex indexAt(const QPoint& point) const;
    
    void setSelectionModel(QItemSelectionModel* selectionModel);
    QRegion itemRegin(QModelIndex index);
    void paintEvent(QPaintEvent* e);
    void mousePressEvent(QMouseEvent* e);

protected slots:
    void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
    void dataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight);

protected:
    // virsual func; Unnecessary to implement, but need declaration
    QModelIndex moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers) 
    {
        return QModelIndex();
    }
    int horizontalOffset() const { return 0; }
    int verticalOffset() const { return 0; }
    bool isIndexHidden(const QModelIndex& index) const { return false; }
    void setSelection(const QRect& rect, QItemSelectionModel::SelectionFlags flags);
    QRegion visualRegionForSelection(const QItemSelection& selection) const 
    {
        return QRegion();
    }

private:
    QItemSelectionModel* selections;
    QList<QRegion> MRegionList;
    QList<QRegion> FRegionList;
    QList<QRegion> SRegionList;
};