#include "dragwidget.h"

#include <QMouseEvent>
//! [0]
DragWidget::DragWidget(QWidget *parent)
    : QFrame(parent)
{
    setMinimumSize(200, 200);
    setAcceptDrops(true);
    QCursor cursor;
    cursor.setShape(Qt::OpenHandCursor);
    this->setCursor(cursor);
}
//! [0]

void DragWidget::mousePressEvent(QMouseEvent *event)
{
    child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;

    QCursor cursor;
    cursor.setShape(Qt::ClosedHandCursor);
    child->setCursor(cursor);
    moving = true;
    initialPointPress = event->pos();
    initialPointLabel = child->pos();
    QFrame::mousePressEvent(event);
}

void DragWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(moving){
        QPoint movementPoint = initialPointPress - event->pos();
        child->move(initialPointLabel - movementPoint);
    }
     QFrame::mouseMoveEvent(event);
}

void DragWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QCursor cursor;
    cursor.setShape(Qt::OpenHandCursor);
    child->setCursor(cursor);
    moving = false;
    initialPointPress = QPoint(0,0);
    initialPointLabel= QPoint(0,0);
    if(child != nullptr){
        child = nullptr;
    }
    QFrame::mouseReleaseEvent(event);
}










