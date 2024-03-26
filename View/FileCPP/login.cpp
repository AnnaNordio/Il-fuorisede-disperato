#include "../FileH/login.h"
#include <QCoreApplication>
#include <QLayout>
#include "../../Database/database.h"
#include "../../Model/FileH/Utenti.h"
#include"../FileH/home.h"


Login::Login(QWidget* parent)
    : QMainWindow(parent), home(nullptr)
{
    QWidget::setWindowTitle ("Login");
    QWidget* mainWidget= new QWidget();
    QGridLayout* layout=new QGridLayout(mainWidget);

    labelConnect = new QLabel();
    form = new LoginForm();

    buttonLogin= new QPushButton("Login");

    buttonRegistrati=new QPushButton("Registrazione");

    layout->setVerticalSpacing(100);
    layout->addWidget(buttonRegistrati, 1,3,Qt::AlignLeft);
    layout->addWidget(form, 2,2);
    layout->addWidget(buttonLogin,3,2);
    layout->setHorizontalSpacing(100);
    layout->addWidget(labelConnect, 4,1,1,3 ,Qt::AlignLeft);
    setCentralWidget(mainWidget);

    connect(buttonRegistrati, &QPushButton::clicked, this, &Login::on_buttonRegistrati);
    connect(buttonLogin, &QPushButton::clicked, this, &Login::on_buttonLogin);

}

Login::~Login()
{
}

void Login::on_buttonLogin(){

    QString qusername,qpassword;
    qusername=form->getUser();
    qpassword=form->getPassword();
    std::string username = qusername.toStdString();
    std::string password = qpassword.toStdString();

    DbController dbController;
    if (username=="")
    {
        this->labelConnect->setText("Username non valido");
    }
    else if (password=="")
    {
        this->labelConnect->setText("Password non valida");
    }
    if(dbController.checkLogin(username, password))
    {

        bool admin=dbController.checkAdmin(username, password);
        this->hide();
        std::shared_ptr<Utenti> u = std::make_shared<Utenti>(username, password, admin);
        Home* home = new Home(u);
        home->resize(900, 800);
        home->show();
        home->raise();

    }
    else
    {
        this->labelConnect->setText("Username o password errati");
    }
}

void Login::on_buttonRegistrati()
{
    this->hide();
    Registrazione registrazione(home, nullptr, false, nullptr);
    registrazione.setModal(true);
    registrazione.exec();
}


