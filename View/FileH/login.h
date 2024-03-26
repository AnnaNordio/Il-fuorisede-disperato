#ifndef LOGIN_H
#define LOGIN_H

#include<QtSql>
#include<QDebug>
#include<QLineEdit>
#include<QLabel>
#include<QPushButton>
#include <QSqlDatabase>
#include<QFileInfo>
#include "registrazione.h"
#include "loginForm.h"
#include <QMainWindow>
#include "../../Controller/FileH/dbcontroller.h"
#include "../../Model/FileH/Utenti.h"


class Login : public QMainWindow
{
    Q_OBJECT

public:

    Login(QWidget* parent = nullptr);
    ~Login();

private slots:

    void on_buttonLogin();
    void on_buttonRegistrati();


private:

    QLabel* labelConnect;
    QPushButton* buttonLogin;
    QPushButton* buttonRegistrati;
    LoginForm* form;
    Home* home;
    DbController dbController;
};

#endif // LOGIN_H
