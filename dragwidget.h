#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QLabel>
#include <QFrame>

//#include <QDragEnterEvent>
//#include <QDropEvent>

//! [0]
class DragWidget : public QFrame
{
public:
    explicit DragWidget(QWidget *parent = nullptr);

protected:
//    void dragEnterEvent(QDragEnterEvent *event) override;
//    void dragMoveEvent(QDragMoveEvent *event) override;
//    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    bool moving = false;
    QPoint initialPointPress = QPoint(0,0);
    QPoint initialPointLabel= QPoint(0,0);
    QLabel *child = nullptr;
};
//! [0]

#endif // DRAGWIDGET_H
