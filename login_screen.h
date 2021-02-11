#ifndef LOGIN_SCREEN_H
#define LOGIN_SCREEN_H

#include <QDialog>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include "mainwindow.h"
#include <database_comunication.h>


namespace Ui {
class login_screen;
}

class login_screen : public QDialog
{
    Q_OBJECT

public:

    enum serverRequestType
    {
     LOGIN
    };

    explicit login_screen(QWidget *parent = 0);
    ~login_screen();

private:
    Ui::login_screen *ui;
    database_comunication database_com;
//    QNetworkAccessManager *nam;
//    QNetworkReply *respuesta;
    MainWindow *mainwindow;

//    void serverRequest(serverRequestType type, QStringList keys, QStringList values);

private slots:
    void serverAnswer(QByteArray, database_comunication::serverRequestType);
    void on_pb_login_clicked();
    void on_pb_close_clicked();
};

#endif // LOGIN_SCREEN_H
