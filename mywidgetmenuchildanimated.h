#ifndef MYWIDGETMENUCHILDANIMATED_H
#define MYWIDGETMENUCHILDANIMATED_H

#include <QWidget>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QPainter>
#include <QStyleOption>
#include "mylabelanimated.h"

#define ANIM_TIME_W 300  //Tiempo de animacion
#define ANIM_SCALE_W 235  //Ancho de icono de menu
#define BOUNCE_SCALE_W 50  //Ancho de rebote de menu

class MyWidgetMenuChildAnimated : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidgetMenuChildAnimated(QWidget *parent = nullptr);
    ~MyWidgetMenuChildAnimated();

    void setEditable(bool);
    void setTextInfo(QString information);
    bool isActivatedState(){
        return activated_state;
    }
    void setActivadeState(bool state){
        activated_state = state;
    }
    void setAnimationInit(QRect start = QRect(), QRect end = QRect());
    void setAnimation(QPropertyAnimation *);
    void startAnimation(int delay = 0, int scale =ANIM_SCALE_W, int anim_time =ANIM_TIME_W, QRect start = QRect(), QRect end = QRect());

    void setChecked(bool checked);
    bool isChecked();

    void setBackgroundImage(const QString image_filename);
    void setAnimationParameters(int delay, int scale, int time, QRect start, QRect end);
    void setAnimationParameters(int delay, int scale, int bounce, int time, QRect start, QRect end);


public slots:
    void hideChilds();
    void showWithAnimation();

    void hideMenu();
    void setOwner(const QString owner_name);
    void emitActionToOwner(QString action);

signals:
    void onHidden();
    void doubleClickedLabel();
    void mouseRightClicked();
    void mouseLeftClicked();
    void clicked();
    void hideAll();
    void mouseEntered(QPoint);
    void actionPressed(QString);

protected:
    void mousePressEvent(QMouseEvent *ev);
    //    void mouseMoveEvent(QMouseEvent *ev);
    void paintEvent(QPaintEvent *event)
    {
        Q_UNUSED(event);
        if(backgroundImage.isEmpty()){
            QStyleOption opt; ///se puede usar este if en el else tambien
            opt.init(this);
            QPainter p(this);
            style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
        }else{
            QPainter painter(this);  ///Este codigo es mas rapido pero no rebota el widget
            painter.drawPixmap(0, 0, QPixmap(backgroundImage));
        }
    }
private slots:
    void setAnimationEnd();
    void finalizadaAnimacion();
    void resizeWidget();
    void setOnIcon();
    void finalizadaAnimacionEnd();
    void setSizeInit();
private:
    QString info ="", backgroundImage = "";
    bool activated_state=false;
    bool parametersSeted=false;
    bool animationOnGoing =false;
    QPropertyAnimation *animation=nullptr;
    QRect startValue;
    QRect midValue;
    QRect endValue;
    QSize maxSize;
    int anim_scale = ANIM_SCALE_W;
    int bounce_scale = BOUNCE_SCALE_W;
    int anim_time = ANIM_TIME_W;

    void setMyLabelAnimatedProperties(MyLabelAnimated *button, QString name, int x, int y);
    void setMyLabelMenuAnimatedProperties(MyLabelAnimated *button, QString name, int x, int y);
};
#endif // MYWIDGETMENUCHILDANIMATED_H
