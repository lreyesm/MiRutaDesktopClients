#include "mywidgetmenuchildanimated.h"
#include <QDebug>
#include <QTimer>
#include "mylabelmenuanimated.h"
#include "mylabelmenuchildanimated.h"

MyWidgetMenuChildAnimated::MyWidgetMenuChildAnimated(QWidget *parent)
    :QWidget(parent)
{
    //    this->move(0,0);
    //    this->setFixedSize(0, 0);///poner alto del padre (Toda la pantalla) y ancho 0
    //    setScaledContents(true);
    //    this->setMouseTracking(true);
    //    QTimer::singleShot(500, this, SLOT(setSizeInit()));
//    initializeGL();
}
MyWidgetMenuChildAnimated::~MyWidgetMenuChildAnimated()
{
    //    delete animation;
}

void MyWidgetMenuChildAnimated::emitActionToOwner(QString action){
    emit actionPressed(action);
}

void MyWidgetMenuChildAnimated::setMyLabelAnimatedProperties(MyLabelAnimated *button, QString name, int x, int y)
{
    button->setObjectName("l_" + name);
    button->setBackgroundImage("fondo_transparente");
    button->setPixmap(QPixmap(":/icons/"+name+".png"));
    button->setScaledContents(true);
    connect(button,SIGNAL(mouseLeftClicked(QString)),this,SLOT(emitActionToOwner(QString)));
    button->move(x,  y);
    button->show();
}

//void MyWidgetMenuChildAnimated::setMyLabelMenuAnimatedProperties(MyLabelMenuAnimated *button, QString name, int x, int y)
//{
//    button->setObjectName("l_" + name);
//    button->setBackgroundImage("fondo_transparente");
//    button->setPixmap(QPixmap(":/icons/"+name+".png"));
//    button->setScaledContents(true);
//    connect(this, SIGNAL(onHidden()),button,SLOT(hideChilds()));
//    connect(button,SIGNAL(actionPress(QString)),this,SLOT(emitActionToOwner(QString)));
//    button->move(x,  y);
//    button->show();
//}

void MyWidgetMenuChildAnimated::setOwner(const QString owner_name)
{
    if(owner_name == "l_archivo"){
        MyLabelAnimated *importar = new MyLabelAnimated(this);
        setMyLabelAnimatedProperties(importar, "importar", 60, 25);

        MyLabelAnimated *respaldar = new MyLabelAnimated(this);
        setMyLabelAnimatedProperties(respaldar, "respaldar", 60, 85);
    }
    else if (owner_name == "l_ordenar") {
        MyLabelMenuChildAnimated *ordenar_fecha = new MyLabelMenuChildAnimated(this);
        ordenar_fecha->setObjectName("l_ordenar_fecha");
        ordenar_fecha->setBackgroundImage("fondo_transparente");
        ordenar_fecha->setPixmap(QPixmap(":/icons/ordenar_fecha.png"));
        ordenar_fecha->setScaledContents(true);
        //        int xpos = (int)((float)this->size().width()/2 - (float)importar->size().width()/2);
        //        int ypos = (int)((float)this->size().height()/4 - (float)importar->size().height()/2);
        connect(this, SIGNAL(onHidden()),ordenar_fecha,SLOT(hideChilds()));
        connect(ordenar_fecha,SIGNAL(actionPress(QString)),this,SLOT(emitActionToOwner(QString)));
        ordenar_fecha->move(60,  25);
        ordenar_fecha->show();

        MyLabelAnimated *ubicacion_bateria = new MyLabelAnimated(this);
        setMyLabelAnimatedProperties(ubicacion_bateria, "ubicacion_bateria", 60, 85);
    }
    else if (owner_name == "l_ordenar_fecha") {
        MyLabelAnimated *ordenar_fecha_importacion = new MyLabelAnimated(this);
        setMyLabelAnimatedProperties(ordenar_fecha_importacion, "ordenar_fecha_importacion", 60, 25);

        MyLabelAnimated *ordenar_fecha_exportacion = new MyLabelAnimated(this);
        setMyLabelAnimatedProperties(ordenar_fecha_exportacion, "ordenar_fecha_exportacion", 60, 85);

        MyLabelAnimated *ordenar_fecha_devuelta = new MyLabelAnimated(this);
        setMyLabelAnimatedProperties(ordenar_fecha_devuelta, "ordenar_fecha_devuelta", 60, 145);

        MyLabelAnimated *ordenar_fecha_revision = new MyLabelAnimated(this);
        setMyLabelAnimatedProperties(ordenar_fecha_revision, "ordenar_fecha_revision", 60, 205);

        MyLabelAnimated *ordenar_fecha_modificacion = new MyLabelAnimated(this);
        setMyLabelAnimatedProperties(ordenar_fecha_modificacion, "ordenar_fecha_modificacion", 60, 265);

    }
    else if (owner_name == "l_tareas") {
        MyLabelAnimated *asignar_campos = new MyLabelAnimated(this);
        setMyLabelAnimatedProperties(asignar_campos, "asignar_campos", 60, 25);

        MyLabelAnimated *nueva_tarea = new MyLabelAnimated(this);
        setMyLabelAnimatedProperties(nueva_tarea, "nueva_tarea", 60, 85);
    }
    else if (owner_name == "l_ayuda") {
        MyLabelAnimated *contactar = new MyLabelAnimated(this);
        setMyLabelAnimatedProperties(contactar, "contactar", 60, 25);

        MyLabelAnimated *acercade = new MyLabelAnimated(this);
        setMyLabelAnimatedProperties(acercade, "acercade", 60, 85);
    }
    else if (owner_name == "pb_buscar") {
        int y_pos=25;
        MyLabelMenuChildAnimated *filtrar_fecha = new MyLabelMenuChildAnimated(this);
        filtrar_fecha->setObjectName("l_filtrar_fecha");
        filtrar_fecha->setBackgroundImage("fondo_transparente");
        filtrar_fecha->setPixmap(QPixmap(":/icons/filtrar_fecha.png"));
        filtrar_fecha->setScaledContents(true);
        connect(this, SIGNAL(onHidden()),filtrar_fecha,SLOT(hideChilds()));
        connect(filtrar_fecha,SIGNAL(actionPress(QString)),this,SLOT(emitActionToOwner(QString)));
        filtrar_fecha->move(60,  y_pos);
        filtrar_fecha->show();

        y_pos +=60;

        MyLabelAnimated *direccion = new MyLabelAnimated(this);
        setMyLabelAnimatedProperties(direccion, "direccion", 60, y_pos);
        y_pos +=60;
        MyLabelAnimated *tipo_tarea = new MyLabelAnimated(this);
        setMyLabelAnimatedProperties(tipo_tarea, "tipo_tarea", 60, y_pos);
        y_pos +=60;
        MyLabelAnimated *numero_abonado = new MyLabelAnimated(this);
        setMyLabelAnimatedProperties(numero_abonado, "numero_abonado", 60, y_pos);
        y_pos +=60;
        MyLabelAnimated *titular = new MyLabelAnimated(this);
        setMyLabelAnimatedProperties(titular, "titular", 60, y_pos);
        y_pos +=60;
        MyLabelAnimated *numero_serie = new MyLabelAnimated(this);
        setMyLabelAnimatedProperties(numero_serie, "numero_serie", 60, y_pos);
        y_pos +=60;
        MyLabelAnimated *zona = new MyLabelAnimated(this);
        setMyLabelAnimatedProperties(zona, "zona", 60, y_pos);
        y_pos +=60;
        MyLabelAnimated *geolocalizacion = new MyLabelAnimated(this);
        setMyLabelAnimatedProperties(geolocalizacion, "geolocalizacion", 60, y_pos);
        y_pos +=60;

        MyLabelMenuChildAnimated *ubicacion = new MyLabelMenuChildAnimated(this);
        ubicacion->setObjectName("l_ubicacion");
        ubicacion->setBackgroundImage("fondo_transparente");
        ubicacion->setPixmap(QPixmap(":/icons/ubicacion.png"));
        ubicacion->setScaledContents(true);
        connect(this, SIGNAL(onHidden()),ubicacion,SLOT(hideChilds()));
        connect(ubicacion,SIGNAL(actionPress(QString)),this,SLOT(emitActionToOwner(QString)));
        ubicacion->move(60,  y_pos);
        ubicacion->show();

    }
    else if (owner_name == "l_ubicacion") {
        MyLabelAnimated *en_bateria = new MyLabelAnimated(this);
        setMyLabelAnimatedProperties(en_bateria, "en_bateria", 60, 25);

        MyLabelAnimated *unitarios = new MyLabelAnimated(this);
        setMyLabelAnimatedProperties(unitarios, "unitarios", 60, 80);
    }
    else if (owner_name == "l_filtrar_fecha") {
        MyLabelAnimated *filtrar_fecha_importacion = new MyLabelAnimated(this);
        setMyLabelAnimatedProperties(filtrar_fecha_importacion, "filtrar_fecha_importacion", 60, 25);

        MyLabelAnimated *filtrar_fecha_exportacion = new MyLabelAnimated(this);
        setMyLabelAnimatedProperties(filtrar_fecha_exportacion, "filtrar_fecha_exportacion", 60, 85);

        MyLabelAnimated *filtrar_fecha_devuelta = new MyLabelAnimated(this);
        setMyLabelAnimatedProperties(filtrar_fecha_devuelta, "filtrar_fecha_devuelta", 60, 145);

        MyLabelAnimated *filtrar_fecha_revision = new MyLabelAnimated(this);
        setMyLabelAnimatedProperties(filtrar_fecha_revision, "filtrar_fecha_revision", 60, 205);

        MyLabelAnimated *filtrar_fecha_modificacion = new MyLabelAnimated(this);
        setMyLabelAnimatedProperties(filtrar_fecha_modificacion, "filtrar_fecha_modificacion", 60, 265);

    }
}

void MyWidgetMenuChildAnimated::setBackgroundImage(const QString image_filename)
{
    if(QFile::exists("icons/"+ image_filename +".png")){
        this->setStyleSheet("border-image: url(:/icons/"+ image_filename +".png);");
        backgroundImage = ":/icons/"+ image_filename +".png";
    }else {
        qDebug()<<"La imagen seteada no existe";
    }
}

void MyWidgetMenuChildAnimated::setAnimationParameters(int delay, int scale, int bounce, int time, QRect start, QRect end)
{
     Q_UNUSED(delay);
    anim_scale = scale;
    bounce_scale = bounce;
    anim_time = time;
    startValue = start;
    endValue = end;
    parametersSeted = true;
}

void MyWidgetMenuChildAnimated::hideChilds()
{
    this->hide();
    emit onHidden();
}


void MyWidgetMenuChildAnimated::setSizeInit()
{
    this->setGeometry(QRect(0,0, 10, 0));
}

void MyWidgetMenuChildAnimated::showWithAnimation()
{
    if(!animationOnGoing){
        if(this->isHidden()){
            this->setFixedSize(0,0);
            this->show();
        }
        this->raise();
        setChecked(true);
        if(parametersSeted){
            startAnimation(0, anim_scale, anim_time, startValue, endValue);
        }else {
            startAnimation(0);
        }
    }
}

void MyWidgetMenuChildAnimated::startAnimation(int delay, int scale, int anim_tim, QRect start, QRect end)
{
     Q_UNUSED(delay);
    //hacer un single shot con delay
    anim_time = anim_tim;
    anim_scale = scale;
    setAnimationInit(start, end);
    animationOnGoing = true;
    connect(animation, SIGNAL(finished()), this, SLOT(setAnimationEnd()));
    animation->start();
    //    connect(animation, &QPropertyAnimation::finished, this, &MyWidgetMenuChildAnimated::setAnimationEnd);
}

void MyWidgetMenuChildAnimated::setAnimationInit(QRect start, QRect end)
{
    QString parentName = parentWidget()->objectName();
    if(start.isEmpty()){
        startValue = QRect(0,0, 0, parentWidget()->height());
    }else {
        startValue = start;
    }
    if(end.isEmpty()){
        endValue= QRect(startValue.x(),startValue.y() //posicion sinmodificar
                        ,startValue.width() + anim_scale + bounce_scale /*Ancho de icono de menu +50 (efecto rebote)*/
                        ,startValue.height()+ 0 /*El alto lo dejo como esta*/);
    }else {
        endValue = end;
    }
    midValue = QRect(startValue.x(),startValue.y() //posicion sinmodificar
                     ,startValue.width() + anim_scale /*Ancho de icono de menu*/
                     ,startValue.height()+ 0 /*El alto lo dejo como esta*/);

    this->setMaximumSize(startValue.width() + anim_scale + bounce_scale, startValue.height());
    animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(anim_time);
    animation->setStartValue(startValue);
    animation->setEndValue(endValue);
}
void MyWidgetMenuChildAnimated::setAnimationEnd()
{
    disconnect(animation, SIGNAL(finished()), this, SLOT(setAnimationEnd()));
    delete animation;
    animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration((int)((float)anim_time/2));
    animation->setStartValue(endValue);
    animation->setEndValue(midValue);
    connect(animation, SIGNAL(finished()), this, SLOT(finalizadaAnimacion()));
    animation->start();
}
void MyWidgetMenuChildAnimated::finalizadaAnimacion()
{
    disconnect(animation, SIGNAL(finished()), this, SLOT(finalizadaAnimacion()));
    animation->stop();
    animationOnGoing = false;
    delete animation;
    animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(16777215);
    animation->setStartValue(midValue);
    animation->setEndValue(midValue);
    //    connect(animation, SIGNAL(finished()), this, SLOT(finalizadaAnimacion()));
    animation->start();
    //    this->setFixedSize(midValue.size());
}

void MyWidgetMenuChildAnimated::hideMenu(){
    if(animation != nullptr){
        animation->stop();
        delete animation;
        animation = nullptr;
        animationOnGoing = false;
    }
    this->hide();
    //    for (int i=0; i < children().size();i++) { //Esto no funciono
    //      //  if(children().at(i)->isWidgetType()){
    //            connect(this, SIGNAL(hideAll()), (MyLabelAnimated*)children().at(i), SLOT(hideChilds()));
    //       // }
    //    }
    //    emit hideAll();
}











void MyWidgetMenuChildAnimated::finalizadaAnimacionEnd()
{
    disconnect(animation, SIGNAL(finished()), this, SLOT(finalizadaAnimacionEnd()));
    animation->stop();
    animationOnGoing = false;
    delete animation;
    //Aqui puedo emitir que se mostro el menu, (con una demora singleshot por supuesto)
}







void MyWidgetMenuChildAnimated::resizeWidget(){

    qDebug()<< parent()->objectName() <<" Size After:  "<< QString::number(parentWidget()->size().width()) << ", " << QString::number(parentWidget()->size().height());
    float width_ratio = (float)parentWidget()->size().width()/1920;
    float height_ratio = (float)parentWidget()->size().height()/1080;
    int width_icon = 72;
    int height_icon = 1078;
    int width_resize = width_icon * width_ratio;
    int height_resize = height_icon * height_ratio;
    this->setFixedSize(width_resize, height_resize);
    //   this->setFixedSize(72, 1000);
    this->move(0,0);
}


void MyWidgetMenuChildAnimated::mousePressEvent(QMouseEvent *ev)
{
     Q_UNUSED(ev);
    emit mouseLeftClicked();
    if(!animationOnGoing){

    }
}

void MyWidgetMenuChildAnimated::setOnIcon()
{
    if(!isChecked()){
        setChecked(true);
    }else {
        setChecked(false);
    }
}

void MyWidgetMenuChildAnimated::setChecked(bool checked){
    if(checked){
        activated_state = true;
    }else{
        activated_state = false;
    }
}
bool MyWidgetMenuChildAnimated::isChecked(){
    return activated_state;
}
//void MyWidgetMenuChildAnimated::mouseMoveEvent(QMouseEvent *ev)
//{
//    emit mouseEntered(ev->pos());
//}
