#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonArray>
#include <QJsonObject>
#include <QStandardItemModel>
#include "database_comunication.h"

#include <operator_selection_screen.h>
#include <counter.h>
#include <QTimer>
#include <QDesktopWidget>
#include <QAxWidget>

#include "tabla.h"
#include "screen_tabla_tareas.h"
#include "screen_tabla_contadores.h"
#include "screen_table_itacs.h"
#include "screen_table_marcas.h"
#include "screen_table_piezas.h"
#include "screen_table_zonas.h"
#include "screen_table_causas_intervenciones.h"
#include "screen_table_resultado_intervenciones.h"
#include "screen_table_emplazamientos.h"
#include "screen_table_clases.h"
#include "screen_table_tipos.h"
#include "screen_table_observaciones.h"
#include "screen_table_calibres.h"
#include "screen_table_longitudes.h"
#include "screen_table_ruedas.h"
#include "screen_table_rutas.h"
#include "screen_table_infos.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
//        static int lastIDSAT;

        static void readVariablesInDB(QDataStream &in);

        void descargarTablas();
public slots:
    void updateModelFromData();
    void login_request();

    void on_pb_cargar_txt_clicked(QString dir);
    void on_pb_cargar_xls_clicked(QString order);
    void on_pb_cargar_dat_clicked(QString order);
    void show_loading(QWidget *parent, QPoint pos, QColor color, int w, int h, bool show_white_background);
    void show_loading();
    void hide_loading();
signals:
    void sendData(QJsonObject);
    void download_user_image_signal();
    void script_excecution_result(int);
    void upload_finished();
    void mouse_pressed();
    void mouse_Release();
    void hidingLoading();


protected slots:
    void closeEvent(QCloseEvent *event);
private slots:
    void serverAnswer(QByteArray, database_comunication::serverRequestType);

    void on_pb_lupa_clicked();
    void on_pb_punta_flecha_clicked();
    void on_pb_cruz_clicked();

    void get_user_selected(QString);
    void on_pb_login_clicked();
    void download_user_image();
    void conection_timeout()
    {
        Script_excecution_result = database_comunication::script_result::timeout;
    }

    void on_drag_screen();
    void on_drag_screen_released();
    void on_start_moving_screen_timeout();

    void mousePressEvent(QMouseEvent *e) ///al reimplementar esta funcion deja de funcionar el evento pressed
    {
         Q_UNUSED(e);
        emit mouse_pressed();
    }

    void mouseReleaseEvent(QMouseEvent *e) ///al reimplementar esta funcion deja de funcionar el evento pressed
    {
         Q_UNUSED(e);
        emit mouse_Release();
    }
    void on_pb_web_browser_clicked();
    void on_pb_tabla_contadores_clicked();
    void get_order_selected(QString o);

    void updateTableInfoWithServer(database_comunication::serverRequestType type);
    void jsonArrayToEraseInServer(QJsonArray jsonArray);
    void on_pb_tabla_contadores_clicked(bool showTable);

    void on_pb_correo_clicked();
    void on_pb_nombre_website_clicked();
    void hideThisWindow();
    void getFilesFromServer();
    void on_pb_tabla_itacs_clicked();

private:
    Ui::MainWindow *ui;
    database_comunication database_com;

    Screen_Table_ITACs *tablaITACsScreen = nullptr;
    Screen_tabla_contadores *tabla_contadores = nullptr;
    screen_tabla_tareas *tablaTareasScreen = nullptr;
    Tabla *myTable = nullptr;
    Screen_Table_Causas_Intervenciones *tablaCausasScreen = nullptr;
    Screen_Table_Marcas *tablaMarcasScreen = nullptr;
    Screen_Table_Zonas *tablaZonasScreen = nullptr;
    Screen_Table_Calibres *tablaCalibresScreen = nullptr;
    Screen_Table_Longitudes *tablaLongitudesScreen = nullptr;
    Screen_Table_Rutas *tablaRutasScreen = nullptr;
    Screen_Table_Piezas *tablaPiezasScreen = nullptr;
    Screen_Table_Emplazamientos *tablaEmplazamientosScreen = nullptr;
    Screen_Table_Clases *tablaClasesScreen = nullptr;
    Screen_Table_Tipos *tablaTiposScreen = nullptr;
    Screen_Table_Ruedas *tablaRuedasScreen = nullptr;
    Screen_Table_Resultado_Intervenciones *tablaResultadosScreen = nullptr;
    Screen_Table_Observaciones *tablaObservacionesScreen = nullptr;

    int Script_excecution_result;

    QJsonArray jsonArray, jsonArrayDoneTasks;
    QStandardItemModel* model;
    bool serverAlredyAnswered;
    QString selected_user;
    QString selected_order;

    QTimer start_moving_screen;
    int init_pos_x;
    int init_pos_y;
    bool first_move = true;
    Navegador *web_browser;


    void conectarSignalsDeTabla(bool conexion = true);
    bool checkVersions(QString serverVersion);
    void callUpdater();
    void iniciateFiles();
    QString empresa = empresa_de_aplicacion;
    QString gestor = gestor_de_aplicacion;
};

#endif // MAINWINDOW_H
