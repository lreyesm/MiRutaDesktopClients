#include "login_screen.h"
#include "ui_login_screen.h"

#include <QMessageBox>
#include <QUrlQuery>

login_screen::login_screen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login_screen),
    database_com()
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint);
//    ui->lb_foto->setPixmap(QPixmap(":/User_Big.png"));
//    ui->lb_foto->setScaledContents(true);
}

login_screen::~login_screen()
{
    delete ui;
}

void login_screen::serverAnswer(QByteArray reply, database_comunication::serverRequestType tipo)
{

    QString respuesta = QString::fromUtf8(reply);
    if(tipo == database_comunication::LOGIN)
//    if(tipo == database_comunication::TEST_DB_CONNECTION)
    {
        disconnect(&database_com, SIGNAL(alredyAnswered(QByteArray, database_comunication::serverRequestType)),this, SLOT(serverAnswer(QByteArray, database_comunication::serverRequestType)));
//        ui->plainTextEdit->setPlainText(respuesta);
        if(respuesta.contains("login not success"))
        {
            QMessageBox::warning(this,"Error de autenticación","Nombre de Usuario o contraseña incorrectos.");
        }
        else
        {
            if(respuesta.contains("login success"))
            {
                mainwindow = new MainWindow();
                mainwindow->show();
                this->close();
            }
        }
    }
}

void login_screen::on_pb_login_clicked()
{
    QStringList keys, values;
    keys << "user_name" << "password";
//    values << ui->le_username->text() << ui->le_password->text();
    values << "kaizoku" << "pass";
    connect(&database_com, SIGNAL(alredyAnswered(QByteArray, database_comunication::serverRequestType)),this, SLOT(serverAnswer(QByteArray, database_comunication::serverRequestType)));
    database_com.serverRequest(database_comunication::serverRequestType::LOGIN,keys,values);
//    database_com.serverRequest(database_comunication::serverRequestType::TEST_DB_CONNECTION,keys,values);
}

void login_screen::on_pb_close_clicked()
{
    this->close();
}
