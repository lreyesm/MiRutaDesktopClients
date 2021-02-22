#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QBuffer>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QUrlQuery>
#include "database_comunication.h"
#include <QFile>
#include <QList>
#include <QtXlsx>
#include "selectionorder.h"
#include <QDesktopWidget>
#include "global_variables.h"
#include "processesclass.h"
#include "screen_upload_itacs.h"
#include "QProgressIndicator.h"
#include "new_table_structure.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    database_com()
{
    ui->setupUi(this);

    ui->statusBar->setStyleSheet("font: 63 10pt \"Segoe UI Semibold\";color: rgb(100, 100, 100)");

    this->setMaximumSize(500, 165);

    iniciateFiles();

    model = nullptr;
    serverAlredyAnswered = false;
    selected_user = "";

    ui->pb_tareas_equipo->setEnabled(false);
    ui->pb_tareas_operario->setEnabled(false);
    ui->pb_tabla_operarios->setEnabled(false);
    ui->pb_tareas_equipo->setEnabled(false);
    ui->pb_cargar_dat->setEnabled(false);
    ui->pb_load_done_tasks->setEnabled(false);
    ui->pb_cargar_xls->setEnabled(false);
    ui->pb_tabla_contadores->setEnabled(false);

    setWindowFlags(Qt::CustomizeWindowHint);

    connect(this, SIGNAL(download_user_image_signal()), this, SLOT(download_user_image()));

    //    getOperariosFromServer();
    connect(this,SIGNAL(mouse_pressed()),this,SLOT(on_drag_screen()));
    connect(this,SIGNAL(mouse_Release()),this,SLOT(on_drag_screen_released()));
    connect(&start_moving_screen,SIGNAL(timeout()),this,SLOT(on_start_moving_screen_timeout()));

    //    web_browser = new Navegador();
    ui->pb_web_browser->hide();

    ui->statusBar->showMessage(QString("Mi Ruta Clientes ") + versionMiRuta, 2000);

    //*********************************Añadido en app de Clientes***********************************************
    QTimer::singleShot(2000, this, &MainWindow::on_pb_login_clicked);
    show_loading();
    QTimer::singleShot(2000, this, &MainWindow::hide_loading);
    descargarTablas();
    //*********************************End Añadido en app de Clientes***********************************************
}

///Nuevo---------------------------------------------------------------------------------------------
bool MainWindow::checkVersions(QString serverVersion){ //true si la version en servidor es mayor
    serverVersion.remove("Mi"); //Ej: Mi Ruta Beta 1.66.exe
    serverVersion.remove("Ruta");
    serverVersion.remove("Beta");
    serverVersion.remove(".exe");
    serverVersion = serverVersion.trimmed();
    QString thisVersion = versionMiRuta; //Ej: "V1.66 Servidor Oficial"
    thisVersion.remove("Servidor Oficial");
    thisVersion.remove("V");
    thisVersion = thisVersion.trimmed();
    if(thisVersion < serverVersion){
        QString n = "Actualizar a version: " + serverVersion + "  actual: " + thisVersion;
        qDebug()<<n;
        return true;
    }else{
        QString n = "No actualizar a version: " + serverVersion + "  actual: " + thisVersion;
        qDebug()<<n;
        return false;
    }
}
void MainWindow::callUpdater(){
    if(QMessageBox::question(this, "Actualización disponible", "Desea actualizar Mi Ruta?",
                             QMessageBox::Ok, QMessageBox::No) == QMessageBox::Ok){
        QDir dir = QDir::current();
        QFile file(dir.path()+"/Updater.exe");
        qDebug()<<"Abriendo updater" + file.fileName();
        QString result = ProcessesClass::executeProcess(this, file.fileName(),
                                                        ProcessesClass::WINDOWS,1000, false);
        this->on_pb_cruz_clicked();
    }
}
void MainWindow::getFilesFromServer()
{
    QStringList keys, values;
    keys << "GESTOR";
    values << gestor_de_aplicacion;
    connect(&database_com, SIGNAL(alredyAnswered(QByteArray, database_comunication::serverRequestType)),
            this, SLOT(serverAnswer(QByteArray, database_comunication::serverRequestType)));
    database_com.serverRequest(database_comunication::serverRequestType::GET_FILES_TO_UPDATE,keys,values);

}
//----------------------------------------------------------------------------------------------------

void MainWindow::iniciateFiles(){

    QDir dir;
    dir.setPath(QDir::currentPath() +"/Respaldos");
    if(!dir.exists()){
        dir.mkpath(dir.path());
    }
    dir.setPath(QDir::currentPath() +"/BD");
    if(!dir.exists()){
        dir.mkpath(dir.path());
    }
    ///Nuevo---------------------------------------------------------------------------------------
    dir = QDir::current();
    QFile file(dir.path()+"/Updater.exe");
    if(file.exists()){
        getFilesFromServer();
        qDebug()<<"Existe updater" + file.fileName();
    }else{
        QTimer::singleShot(4000, this, SLOT(hideThisWindow()));
        qDebug()<<"No existe updater";
    }
    //---------------------------------------------------------------------------------------------

    QFile data_base_download_itacs(itacs_descargadas); // ficheros .dat se puede utilizar formato txt tambien
    if(!data_base_download_itacs.exists()){
        if(data_base_download_itacs.open(QIODevice::WriteOnly)){

            QDataStream out(&data_base_download_itacs);
            data_base_download_itacs.close();
        }
    }
    QFile data_base_download_infos(infos_descargadas); // ficheros .dat se puede utilizar formato txt tambien
    if(!data_base_download_infos.exists()){
        if(data_base_download_infos.open(QIODevice::WriteOnly)){

            QDataStream out(&data_base_download_infos);
            data_base_download_infos.close();
        }
    }
    QFile data_base_download_calibres(calibres_descargadas); // ficheros .dat se puede utilizar formato txt tambien
    if(!data_base_download_calibres.exists()){
        if(data_base_download_calibres.open(QIODevice::WriteOnly)){

            QDataStream out(&data_base_download_calibres);
            data_base_download_calibres.close();
        }
    }
    QFile data_base_download_longitudes(longitudes_descargadas); // ficheros .dat se puede utilizar formato txt tambien
    if(!data_base_download_longitudes.exists()){
        if(data_base_download_longitudes.open(QIODevice::WriteOnly)){

            QDataStream out(&data_base_download_longitudes);
            data_base_download_longitudes.close();
        }
    }
    QFile data_base_download_ruedas(ruedas_descargadas); // ficheros .dat se puede utilizar formato txt tambien
    if(!data_base_download_ruedas.exists()){
        if(data_base_download_ruedas.open(QIODevice::WriteOnly)){

            QDataStream out(&data_base_download_ruedas);
            data_base_download_ruedas.close();
        }
    }
    QFile data_base_download_rutas(rutas_descargadas); // ficheros .dat se puede utilizar formato txt tambien
    if(!data_base_download_rutas.exists()){
        if(data_base_download_rutas.open(QIODevice::WriteOnly)){

            QDataStream out(&data_base_download_rutas);
            data_base_download_rutas.close();
        }
    }
    QFile data_base_download_causas(causas_descargadas); // ficheros .dat se puede utilizar formato txt tambien
    if(!data_base_download_causas.exists()){
        if(data_base_download_causas.open(QIODevice::WriteOnly)){

            QDataStream out(&data_base_download_causas);
            data_base_download_causas.close();
        }
    }
    QFile data_base_download_resultados(resultados_descargadas); // ficheros .dat se puede utilizar formato txt tambien
    if(!data_base_download_resultados.exists()){
        if(data_base_download_resultados.open(QIODevice::WriteOnly)){

            QDataStream out(&data_base_download_resultados);
            data_base_download_resultados.close();
        }
    }
    QFile data_base_download_clases(clases_descargadas); // ficheros .dat se puede utilizar formato txt tambien
    if(!data_base_download_clases.exists()){
        if(data_base_download_clases.open(QIODevice::WriteOnly)){

            QDataStream out(&data_base_download_clases);
            data_base_download_clases.close();
        }
    }
    QFile data_base_download_emplazamientos(emplazamientos_descargadas); // ficheros .dat se puede utilizar formato txt tambien
    if(!data_base_download_emplazamientos.exists()){
        if(data_base_download_emplazamientos.open(QIODevice::WriteOnly)){

            QDataStream out(&data_base_download_emplazamientos);
            data_base_download_emplazamientos.close();
        }
    }
    QFile data_base_download_tipos(tipos_descargadas); // ficheros .dat se puede utilizar formato txt tambien
    if(!data_base_download_tipos.exists()){
        if(data_base_download_tipos.open(QIODevice::WriteOnly)){

            QDataStream out(&data_base_download_tipos);
            data_base_download_tipos.close();
        }
    }
    QFile data_base_download_observaciones(observaciones_descargadas); // ficheros .dat se puede utilizar formato txt tambien
    if(!data_base_download_observaciones.exists()){
        if(data_base_download_observaciones.open(QIODevice::WriteOnly)){

            QDataStream out(&data_base_download_observaciones);
            data_base_download_observaciones.close();
        }
    }
    QFile data_base_download_zonas(zonas_descargadas); // ficheros .dat se puede utilizar formato txt tambien
    if(!data_base_download_zonas.exists()){
        if(data_base_download_zonas.open(QIODevice::WriteOnly)){

            QDataStream out(&data_base_download_zonas);
            data_base_download_zonas.close();
        }
    }
    QFile data_base_download_piezas(piezas_descargadas); // ficheros .dat se puede utilizar formato txt tambien
    if(!data_base_download_piezas.exists()){
        if(data_base_download_piezas.open(QIODevice::WriteOnly)){

            QDataStream out(&data_base_download_piezas);
            data_base_download_piezas.close();
        }
    }
    QFile data_base_download_series(numeros_serie_descargados); // ficheros .dat se puede utilizar formato txt tambien
    if(!data_base_download_series.exists()){
        if(data_base_download_series.open(QIODevice::WriteOnly)){

            QDataStream out(&data_base_download_series);
            data_base_download_series.close();
        }
    }
    QFile data_base_download_counters(contadores_descargados); // ficheros .dat se puede utilizar formato txt tambien
    if(!data_base_download_counters.exists()){
        if(data_base_download_counters.open(QIODevice::WriteOnly)){

            QDataStream out(&data_base_download_counters);
            data_base_download_counters.close();
        }
    }
    QFile data_base_download_marks(marcas_descargadas); // ficheros .dat se puede utilizar formato txt tambien
    if(!data_base_download_marks.exists()){
        if(data_base_download_marks.open(QIODevice::WriteOnly)){

            QDataStream out(&data_base_download_marks);
            data_base_download_marks.close();
        }
    }
    QFile data_base_download_works(ficheros_comprimidos_descargados); // ficheros .dat se puede utilizar formato txt tambien
    if(!data_base_download_works.exists()){
        if(data_base_download_works.open(QIODevice::WriteOnly)){

            QDataStream out(&data_base_download_works);
            data_base_download_works.close();
        }
    }
    QFile *data_base_load_works = new QFile(trabajos_cargados); // ficheros .dat se puede utilizar formato txt tambien
    if(!data_base_load_works->exists()){
        if(data_base_load_works->open(QIODevice::WriteOnly)){

            QDataStream out(data_base_load_works);
            data_base_load_works->close();
        }
    }
    QFile *data_base_tareas = new QFile(tareas_descargadas); // ficheros .dat se puede utilizar formato txt tambien
    if(!data_base_tareas->exists()){
        if(data_base_tareas->open(QIODevice::WriteOnly)){

            QDataStream out(data_base_tareas);
            data_base_tareas->close();
        }
    }
    QFile *data_base_tasks = new QFile(tareas_sincronizadas); // ficheros .dat se puede utilizar formato txt tambien
    if(!data_base_tasks->exists()){
        if(data_base_tasks->open(QIODevice::WriteOnly)){

            QDataStream out(data_base_tasks);
            data_base_tasks->close();
        }
    }
    QFile *data_base_mod = new QFile(tareas_modificadas); // ficheros .dat se puede utilizar formato txt tambien
    if(!data_base_mod->exists()){
        if(data_base_mod->open(QIODevice::WriteOnly)){

            QDataStream out(data_base_mod);
            data_base_mod->close();
        }
    }
    QFile *data_base = new QFile(datos); // ficheros .dat se puede utilizar formato txt tambien
    if(!data_base->exists()){
        if(data_base->open(QIODevice::WriteOnly)){

            QDataStream out(data_base);
            out<<screen_tabla_tareas::lastIDSAT;
            out<<screen_tabla_tareas::lastNUMFICHERO_EXPORTACION;
            out<<screen_tabla_tareas::lastIDExp;
            out<<screen_tabla_tareas::emailPermission;
            out<<screen_tabla_tareas::lastSync;
            data_base->close();
        }
    }
    else if(data_base->open(QIODevice::ReadOnly))
    {
        QDataStream in(data_base);
        readVariablesInDB(in);
        data_base->close();
    }
}

void MainWindow::hideThisWindow(){
    showMinimized();
    myTable->setFocusPolicy(Qt::TabFocus);
    myTable->setFocus();
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    QWidget::closeEvent(event);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
}

void MainWindow::readVariablesInDB(QDataStream &in){
    in>>screen_tabla_tareas::lastIDSAT;
    in>>screen_tabla_tareas::lastNUMFICHERO_EXPORTACION;
    in>>screen_tabla_tareas::lastIDExp;
    in>>screen_tabla_tareas::emailPermission;
}


void MainWindow::on_drag_screen(){

    if(isFullScreen()){
        if(QApplication::mouseButtons()==Qt::RightButton){


        }
        return;
    }
    //ui->statusBar->showMessage("Moviendo");
    if(QApplication::mouseButtons()==Qt::LeftButton){

        start_moving_screen.start(10);
        init_pos_x = (QWidget::mapFromGlobal(QCursor::pos())).x();
        init_pos_y = (QWidget::mapFromGlobal(QCursor::pos())).y();
    }
    else if(QApplication::mouseButtons()==Qt::RightButton){

    }
}

void MainWindow::on_start_moving_screen_timeout(){

    int x_pos = (int)this->pos().x()+((QWidget::mapFromGlobal(QCursor::pos())).x() - init_pos_x);
    int y_pos = (int)this->pos().y()+((QWidget::mapFromGlobal(QCursor::pos())).y() - init_pos_y);
    x_pos = (x_pos < 0)?0:x_pos;
    y_pos = (y_pos < 0)?0:y_pos;

    x_pos = (x_pos > QApplication::desktop()->width()-100)?QApplication::desktop()->width()-100:x_pos;
    y_pos = (y_pos > QApplication::desktop()->height()-180)?QApplication::desktop()->height()-180:y_pos;

    this->move(x_pos,y_pos);

    init_pos_x = (QWidget::mapFromGlobal(QCursor::pos())).x();
    init_pos_y = (QWidget::mapFromGlobal(QCursor::pos())).y();
}

void MainWindow::on_drag_screen_released()
{
    if(isFullScreen()){

        return;
    }
    start_moving_screen.stop();
    init_pos_x = 0;
    init_pos_y = 0;
    //current_win_Pos = QPoint(this->pos().x()-200,this->pos().y()-200);
}

void MainWindow::updateModelFromData()
{
    int rows = jsonArray.count();
    //comprobando que no exista un modelo anterior
    if(model!=nullptr)
        delete model;

    model = new QStandardItemModel(rows, 4);
    QStringList listHeaders;

    listHeaders << "Nombre" << "Apellidos" << "Edad" << "Tareas";
    model->setHorizontalHeaderLabels(listHeaders);
    //insertando los datos
    QStandardItem *item;
    for(int i = 0; i < rows; i++)
    {
        item = new QStandardItem();
        item->setData(jsonArray[i].toObject().value("nombre").toString(),Qt::EditRole);
        model->setItem(i, 0, item);
        item = new QStandardItem();
        item->setData(jsonArray[i].toObject().value("apellidos").toString(),Qt::EditRole);
        model->setItem(i, 1, item);
        item = new QStandardItem();
        item->setData(jsonArray[i].toObject().value("edad").toString(),Qt::EditRole);
        model->setItem(i, 2, item);
        item = new QStandardItem();
        item->setData(jsonArray[i].toObject().value("tareas").toString(),Qt::EditRole);
        model->setItem(i, 3, item);
    }

}

void MainWindow::login_request()
{
    QStringList keys, values;
    keys << "user_name" << "password";
    values << ui->le_username->text() << ui->le_password->text();
    connect(&database_com, SIGNAL(alredyAnswered(QByteArray,database_comunication::serverRequestType)),this, SLOT(serverAnswer(QByteArray,database_comunication::serverRequestType)));
    database_com.serverRequest(database_comunication::serverRequestType::LOGIN,keys,values);
}

void MainWindow::serverAnswer(QByteArray reply, database_comunication::serverRequestType tipo)
{
    QString respuesta = QString::fromUtf8(reply);
    int result = -1;
    if(tipo == database_comunication::LOGIN)
    {
        disconnect(&database_com, SIGNAL(alredyAnswered(QByteArray, database_comunication::serverRequestType)),this, SLOT(serverAnswer(QByteArray, database_comunication::serverRequestType)));
        //        ui->plainTextEdit->setPlainText(respuesta);
        if(respuesta.contains("login not success"))
        {
            QMessageBox::warning(this,"Error de autenticación","Nombre de Usuario o contraseña incorrectos.");

            ui->lb_foto->setPixmap((QPixmap("User_Big.png")));
            result = database_comunication::script_result::login_failed;
        }
        else
        {
            if(respuesta.contains("login success"))
            {
                result = database_comunication::script_result::ok;
            }
        }
    }
    ///Nuevo---------------------------------------------------------------------------------------------
    if(tipo == database_comunication::GET_FILES_TO_UPDATE)
    {
        reply.chop(2);
        disconnect(&database_com, SIGNAL(alredyAnswered(QByteArray, database_comunication::serverRequestType)),this, SLOT(serverAnswer(QByteArray, database_comunication::serverRequestType)));
        QString str = QString::fromUtf8(reply).replace("\n","");
        QStringList files;
        if(str.contains(" -- ")){
            files = str.split(" -- ");
        }
        QString file;
        foreach(file, files){
            if(file.contains("Mi") && file.contains("Ruta")
                    && file.contains(".exe")){
                if(checkVersions(file)){
                    callUpdater();
                }
                break;
            }
        }
        QTimer::singleShot(2000, this, SLOT(hideThisWindow()));
    }
    ///---------------------------------------------------------------------------------------------

    if(tipo == database_comunication::DOWNLOAD_USER_IMAGE)
    {
        QString foto = QString::fromUtf8(reply);
        QImage temp_img = database_comunication::getImageFromString(foto);
        if(temp_img.isNull())
        {
            ui->lb_foto->setPixmap((QPixmap("User_Big.png")));
        }
        else
        {
            ui->lb_foto->setPixmap(QPixmap::fromImage(temp_img));
            ui->lb_foto->setScaledContents(true);
        }

        disconnect(&database_com, SIGNAL(alredyAnswered(QByteArray,database_comunication::serverRequestType)),this, SLOT(serverAnswer(QByteArray,database_comunication::serverRequestType)));

        ui->pb_tareas_equipo->setEnabled(true);
        ui->pb_tareas_operario->setEnabled(true);
        ui->pb_tabla_operarios->setEnabled(true);
        ui->pb_tareas_equipo->setEnabled(true);
        ui->pb_cargar_dat->setEnabled(true);
        ui->pb_load_done_tasks->setEnabled(true);
        ui->pb_cargar_xls->setEnabled(true);
        ui->pb_tabla_contadores->setEnabled(true);

        ui->statusBar->showMessage("Bienvenido "+ui->le_username->text(),2000);

        ui->pb_login->setEnabled(true);
        if(myTable == nullptr){
            myTable = new Tabla(nullptr, empresa);
            myTable->showMaximized();
            myTable->getTareas();

            conectarSignalsDeTabla();
        }
    }

    emit script_excecution_result(result);

}

void MainWindow::descargarTablas(){

    tablaTiposScreen = new Screen_Table_Tipos(nullptr, false);
    tablaClasesScreen = new Screen_Table_Clases(nullptr, false);
    tablaEmplazamientosScreen = new Screen_Table_Emplazamientos(nullptr, false);
    tablaPiezasScreen = new Screen_Table_Piezas(nullptr, false);
    tablaMarcasScreen = new Screen_Table_Marcas(nullptr, false);
    tablaCausasScreen = new Screen_Table_Causas_Intervenciones(nullptr, false);
    tablaCalibresScreen = new Screen_Table_Calibres(nullptr, false);
    tablaLongitudesScreen = new Screen_Table_Longitudes(nullptr, false);
    tablaRutasScreen = new Screen_Table_Rutas(nullptr, false);

    tablaZonasScreen = new Screen_Table_Zonas(nullptr, false, empresa);
    tablaITACsScreen = new Screen_Table_ITACs(nullptr, false, empresa);
    tablaTareasScreen = new screen_tabla_tareas(nullptr, empresa);
}

void MainWindow::conectarSignalsDeTabla(bool conexion)
{
    Q_UNUSED(conexion);
    connect(myTable, &Tabla::closing, this, &MainWindow::close);
    connect(myTable, &Tabla::gestorSelected, tablaITACsScreen, &Screen_Table_ITACs::setGestor);
    connect(myTable, &Tabla::updateITACsInfo, tablaITACsScreen, &Screen_Table_ITACs::updateItacsInTable);
    connect(myTable, &Tabla::openITACsTable, this, &MainWindow::on_pb_tabla_itacs_clicked);

    connect(myTable, SIGNAL(importarTXT(QString)), this, SLOT(on_pb_cargar_txt_clicked(QString)));
    connect(myTable, SIGNAL(importarExcel(QString)), this, SLOT(on_pb_cargar_xls_clicked(QString)));
    connect(myTable, SIGNAL(importarDAT(QString)), this, SLOT(on_pb_cargar_dat_clicked(QString)));
    connect(myTable, SIGNAL(eraseJsonArrayInServer(QJsonArray)), this, SLOT(jsonArrayToEraseInServer(QJsonArray)));

    connect(tablaTareasScreen, &screen_tabla_tareas::updateOtherTable,
            myTable, &Tabla::updateTareasInTable);
    connect(tablaITACsScreen, &Screen_Table_ITACs::updateTableTareas,
            myTable, &Tabla::updateTareasInTable);
}


void MainWindow::on_pb_cargar_dat_clicked(QString order)
{
    if(order == "buscar_fichero_en_PC"){
        tablaTareasScreen->set_file_type(4);
        tablaTareasScreen->setRutaFile(order);
    }
    else if(order == "DIARIAS" || order == "MASIVAS" || order == "ESPECIALES"){
        selected_order = order;
        tablaTareasScreen->set_file_type(1);
        tablaTareasScreen->set_tipo_orden(order);
    }
    else{
        QString ruta = order;
        tablaTareasScreen->set_file_type(4);
        tablaTareasScreen->setRutaFile(ruta);
    }
    tablaTareasScreen->showMaximized();
}
void MainWindow::on_pb_cargar_txt_clicked(QString dir)
{
    if(dir.contains("itacs", Qt::CaseInsensitive)){
        Screen_Upload_Itacs *itacs = new Screen_Upload_Itacs(nullptr, empresa);
        itacs->getITACsFromFile(dir);
        itacs->show();
        return;
    }
    tablaTareasScreen->set_file_type(3);
    tablaTareasScreen->setRutaFile(dir);
    tablaTareasScreen->showMaximized();
}

void MainWindow::on_pb_cargar_xls_clicked(QString order)
{
    selected_order = order;
    tablaTareasScreen->set_file_type(2);
    tablaTareasScreen->set_tipo_orden(order);
    tablaTareasScreen->showMaximized();
}


void MainWindow::on_pb_tabla_itacs_clicked()
{
    if(tablaITACsScreen==nullptr){
        tablaITACsScreen = new Screen_Table_ITACs(
                    nullptr, true, empresa_de_aplicacion, gestor_de_aplicacion);
    }else{
        tablaITACsScreen->getITACs();
    }
    tablaITACsScreen->showMaximized();
}
void MainWindow::updateTableInfoWithServer(database_comunication::serverRequestType type)
{
    Q_UNUSED(type);
    ui->statusBar->showMessage("Tareas cargadas", 3000);
    //    ui->statusBar->showMessage(screen_tabla_tareas::lastSync);
    if(myTable!= nullptr){
        if(myTable->isHidden()){
            myTable->showMaximized();
        }
        myTable->setJsonArrayAll(tablaTareasScreen->getAllTask());
    }
}

void MainWindow::jsonArrayToEraseInServer(QJsonArray jsonArray)
{
    QJsonObject o;
    QJsonDocument d;
    int result = -1;
    //    int total = jsonArray.size();
    int total= jsonArray.size();
    for(int i=0, reintentos = 0; i< jsonArray.size(); i++)
    {
        myTable->on_posicionBorrado(i, total);
        o = jsonArray[i].toObject();
        QEventLoop *q = new QEventLoop();

        if(tablaTareasScreen==nullptr){
            tablaTareasScreen= new screen_tabla_tareas();
        }
        connect(tablaTareasScreen, &screen_tabla_tareas::task_delete_excecution_result,q,&QEventLoop::exit);

        QTimer *timer;
        timer = new QTimer();
        //            timer->setInterval(DELAY);
        timer->setSingleShot(true);

        tablaTareasScreen->keys.clear();//este es para delete_tarea - estoy usando delete_tarea.php
        tablaTareasScreen->keys << numero_interno << numero_abonado << GESTOR << ANOMALIA
                                << numero_serie_contador_devuelto << "empresa";
        tablaTareasScreen->values.clear();
        tablaTareasScreen->values << o.value(numero_interno).toString().trimmed()
                                  << o.value(numero_abonado).toString().trimmed()
                                  << o.value(GESTOR).toString().trimmed()
                                  << o.value(ANOMALIA).toString().trimmed()
                                  << o.value(numero_serie_contador_devuelto).toString().trimmed()
                                  << empresa;

        connect(&tablaTareasScreen->database_com, SIGNAL(alredyAnswered(QByteArray,database_comunication::serverRequestType)),
                tablaTareasScreen, SLOT(serverAnswer(QByteArray,database_comunication::serverRequestType)));

        connect(timer,SIGNAL(timeout()),tablaTareasScreen,SLOT(delete_one_task()));
        timer->start(DELAY);

        switch(q->exec())
        {
        case database_comunication::script_result::timeout:
            i--;
            reintentos++;
            if(reintentos == RETRIES)
            {
                result = database_comunication::script_result::timeout;
                i = jsonArray.size();
            }
            break;
        case database_comunication::script_result::ok:
            result = database_comunication::script_result::ok;
            reintentos = 0;
            break;
        case database_comunication::script_result::delete_task_failed:
            i--;
            reintentos++;
            if(reintentos == RETRIES)
            {
                result = database_comunication::script_result::delete_task_failed;
                i = jsonArray.size();
            }
            break;
        }
        delete timer;
        delete q;


    }
    myTable->resultado_Eliminacion_Tareas(result);
}

void MainWindow::on_pb_lupa_clicked()
{

}

void MainWindow::on_pb_punta_flecha_clicked()
{
    this->setWindowState(Qt::WindowMinimized);
}

void MainWindow::on_pb_cruz_clicked()
{
    if(myTable!=nullptr){
        myTable->close();
    }
    this->close();
}

void MainWindow::get_user_selected(QString u)
{
    selected_user = u;
}

void MainWindow::get_order_selected(QString o)
{
    selected_order = o;
}


void MainWindow::on_pb_login_clicked()
{
    if(myTable != nullptr){
        myTable->close();
        myTable->deleteLater();
        myTable = nullptr;
    }

    if(database_com.checkConnection()){
        myTable = new Tabla(nullptr, empresa);
        myTable->showMaximized();
        myTable->getTareas();

        conectarSignalsDeTabla();

        hide_loading();
    }
    this->showMinimized();
}

void MainWindow::show_loading(QWidget *parent, QPoint pos, QColor color, int w, int h, bool show_white_background){
    emit hidingLoading();

    int border = 1;
    pos.setX(pos.x()-w/2);
    pos.setY(pos.y()-h/2);
    if(show_white_background){
        QLabel *label_back = new QLabel(parent);
        connect(this, &MainWindow::hidingLoading, label_back, &QLabel::hide);
        connect(this, &MainWindow::hidingLoading, label_back, &QLabel::deleteLater);
        label_back->setFixedSize(w + border, h + border);
        label_back->move(pos);
        QString circle_radius_string = QString::number(static_cast<int>((w+border)/2));
        //    QString colorRBG = getColorString(color);
        label_back->setStyleSheet("background-color: #FFFFFF;"
                                  "border-radius: "+circle_radius_string+"px;");
        label_back->show();
    }

    QProgressIndicator *pi = new QProgressIndicator(parent);
    connect(this, &MainWindow::hidingLoading, pi, &QProgressIndicator::stopAnimation);
    connect(this, &MainWindow::hidingLoading, pi, &QProgressIndicator::deleteLater);
    pi->setColor(color);
    pi->setFixedSize(w, h);
    pi->startAnimation();
    pos.setX(pos.x()+border/2 + 1);
    pos.setY(pos.y()+border/2 + 1);
    pi->move(pos);
    pi->show();
}
void MainWindow::show_loading(){
    emit hidingLoading();

    QProgressIndicator *pi = new QProgressIndicator(ui->widget_loading);
    connect(this, &MainWindow::hidingLoading, pi, &QProgressIndicator::stopAnimation);
    connect(this, &MainWindow::hidingLoading, pi, &QProgressIndicator::deleteLater);
    pi->setColor(color_blue_app);
    pi->setFixedSize(ui->widget_loading->size());
    pi->startAnimation();
    pi->move(0,0);
    pi->show();
}

void MainWindow::hide_loading(){
    emit hidingLoading();
}


void MainWindow::download_user_image()
{
    QStringList keys, values;
    keys << "user_name";
    values << ui->le_username->text();

    connect(&database_com, SIGNAL(alredyAnswered(QByteArray,database_comunication::serverRequestType)),this, SLOT(serverAnswer(QByteArray,database_comunication::serverRequestType)));
    database_com.serverRequest(database_comunication::serverRequestType::DOWNLOAD_USER_IMAGE,keys,values);

}




void MainWindow::on_pb_web_browser_clicked()
{

    web_browser = new Navegador();
    web_browser->show();
}

void MainWindow::on_pb_tabla_contadores_clicked(bool showTable)
{
    if(tabla_contadores == nullptr){
        tabla_contadores = new Screen_tabla_contadores();
    }else{
        tabla_contadores->getContadores();
    }
    if(showTable){
        tabla_contadores->show();
    }else{
        connect(tabla_contadores,SIGNAL(filledContadores()),this,SLOT(fillContadoresInOneTarea()));
    }
}

void MainWindow::on_pb_tabla_contadores_clicked()
{
    if(tabla_contadores == nullptr){
        tabla_contadores = new Screen_tabla_contadores();
    }
    tabla_contadores->show();
}

void MainWindow::on_pb_correo_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(ui->pb_correo->text());

    QString link = "https://mail.google.com/mail/u/0/#inbox?compose=new";//el valor /*GTvVlcSKjRFJlPwmRNMHnPsKPZldpQhZkLVHlFVXMqRKQlMxHZGnKpkGwfcLTjThvpJLsfRqnmBbh*/ parece que cambia cada vez que abro
    QDesktopServices::openUrl(QUrl(link));

    ui->statusBar->showMessage("Dirección de correo copiada", 3000);
}

void MainWindow::on_pb_nombre_website_clicked()
{
    QString link = "http://mraguas.com/";//el valor /*GTvVlcSKjRFJlPwmRNMHnPsKPZldpQhZkLVHlFVXMqRKQlMxHZGnKpkGwfcLTjThvpJLsfRqnmBbh*/ parece que cambia cada vez que abro
    QDesktopServices::openUrl(QUrl(link));

    ui->statusBar->showMessage("Abriento sitio...", 3000);
}
