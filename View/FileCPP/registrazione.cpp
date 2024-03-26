#include "../FileH/registrazione.h"
#include <QCoreApplication>
#include "../FileH/login.h"
#include <QLayout>
#include <QDebug>
#include "../FileH/home.h"
Registrazione::Registrazione(Home* home, QWidget* parent, bool modifica, std::shared_ptr<Utenti> u) :
    QDialog(parent), homeWindow(home), dbController(), utente(u), modifica(modifica)
{
	
	setFixedSize(650, 550);
    QWidget::setWindowTitle ("Registrazione");
    //QWidget* mainWidget= new QWidget();
    QGridLayout* layout=new QGridLayout(this);

    labelConnect = new QLabel();
    form = new LoginForm(true,modifica);

    buttonLogin= new QPushButton("Conferma");

    buttonIndietro=new QPushButton("Indietro");

    layout->setVerticalSpacing(100);
    layout->addWidget(buttonIndietro, 1,3,Qt::AlignLeft);
    layout->addWidget(form, 2,2);
    layout->addWidget(buttonLogin,3,2);
    layout->setHorizontalSpacing(100);
    layout->addWidget(labelConnect, 4,1,1,3 ,Qt::AlignLeft);

    connect(buttonIndietro, &QPushButton::clicked, this, &Registrazione::on_buttonIndietro_clicked);

    connect(buttonLogin, &QPushButton::clicked, this, &Registrazione::on_buttonConfermaReg_clicked);

}


Registrazione::~Registrazione()
{
}


void Registrazione::on_buttonConfermaReg_clicked()
{
    QString qusername,qpassword, qpassword2;
    qusername=form->getUser();
    qpassword=form->getPassword();
    qpassword2=form->getConfirmPassword();
    username = qusername.toStdString();
    password = qpassword.toStdString();
    password2 = qpassword2.toStdString();


    if (username=="")
    {
        this->labelConnect->setText("Username non valido");
    }

    else if (password!=password2||(password==""&&password2==""))
    {
        this->labelConnect->setText("Password non valida");
    }

    else if (modifica)
    
    {
    	if(dbController.checkLogin(username, password)&&username==utente->getUser()&&password==utente->getPassword())
    	{
    		this->labelConnect->setText("Utente non modificato");
    	}
    	if(dbController.checkUtente(username)&&username!=utente->getUser())
    	{
    		this->labelConnect->setText("Utente già presente nel database");
    	}
    
        else if(dbController.modificaUser(username, password, utente->getUser(), utente->getPassword()))
        {
        
            this->close();

            utente->setUser(username);
            utente->setPassword(password);
		
            Home *home=new Home(utente);
            home->show();
            home->raise();

        }
    }
    else
    {
        if(dbController.aggiungiUser(username, password))
        {
            this->hide();
            Login *login = new Login;
            login->show();
        }
        else
        {
            this->labelConnect->setText("Username già in uso");
        }
    }

}


void Registrazione::on_buttonIndietro_clicked()
{
    if (modifica)
    {
        this->close();
        homeWindow->show();
        homeWindow->raise();

    }
    else
    {
        this->close();
        Login *login = new Login;
        login->show();

    }
}

