#ifndef REGISTRAZIONE_H
#define REGISTRAZIONE_H

#include <QDialog>
#include<QtSql>
#include<QDebug>
#include<QFileInfo>
#include "loginForm.h"
#include "../../Model/FileH/Utenti.h"
#include "../../Controller/FileH/dbcontroller.h"
#include "../../Database/database.h"

class Home;
class Login;

class Registrazione : public QDialog
{
    Q_OBJECT

public:
    Registrazione(Home* home, QWidget* parent, bool modifica, std::shared_ptr<Utenti> u);
    ~Registrazione();


private slots:

    void on_buttonConfermaReg_clicked();
    void on_buttonIndietro_clicked();

private:

    QLabel* labelConnect;
    QPushButton* buttonIndietro;
    QPushButton* buttonLogin;
    LoginForm* form;
    Home* homeWindow;
    Login* loginWindow;
    DbController dbController;
    std::shared_ptr<Utenti> utente;
    bool modifica=false;
    std::string username;
    std::string password;
    std::string password2;
};

#endif // REGISTRAZIONE_H
