#include "../FileH/profile.h"
#include "../FileH/home.h"

Profile::Profile(Home* home, std::shared_ptr<Utenti> u, QWidget *parent)
    : QWidget(parent), profileVisible(false), homeWindow(home), registrazioneWindow(nullptr), utente(u)
{
    mainLayout = new QVBoxLayout(this);
    profileLayout = new QVBoxLayout();
    profileButton = new QPushButton(this);
    profileButton->setIcon(QIcon(":Immagini/profile.png"));
    profileWidget = new QWidget(this);
    itemsLayout = new QVBoxLayout(profileWidget);
    profileAnimation = new QPropertyAnimation(profileWidget, "maximumWidth", this);
    buttonCarrello = new QPushButton("Carrello", profileWidget);
    buttonCarrello->setIcon(QIcon(":Immagini/carrello.png"));
    if (utente->getIsAdmin())
    {
        buttonCarrello->setVisible(false);
    }
    buttonModifica = new QPushButton("Modifica profilo", profileWidget);
    buttonModifica->setIcon(QIcon(":Immagini/modifica.png"));
    buttonLogout = new QPushButton("Logout", profileWidget);
    buttonLogout->setIcon(QIcon(":Immagini/exit.png"));

    itemsLayout->addWidget(buttonCarrello);
    itemsLayout->addWidget(buttonModifica);
    itemsLayout->addWidget(buttonLogout);
    profileButton->setFixedSize(40, 40);
    profileButton->setStyleSheet("font-size: 24px;");

    profileWidth = width() / 4;
    profileWidget->setMaximumWidth(0);
    profileWidget->setStyleSheet("background-color: #d1d1d1;");
    profileAnimation->setDuration(300);

    connect(profileButton, &QPushButton::clicked, this, &Profile::toggleMenu);
    connect(buttonLogout, &QPushButton::clicked, this, &Profile::on_buttonLogout_clicked);
    connect(buttonCarrello, &QPushButton::clicked, this, &Profile::on_buttonCarrello_clicked);
    connect(buttonModifica, &QPushButton::clicked, this, &Profile::on_buttonModifica_clicked);

    profileLayout->addWidget(profileButton);
    profileLayout->addWidget(profileWidget);
    mainLayout->addLayout(profileLayout);
}

void Profile::toggleMenu()
{
    if (profileVisible) {
        profileAnimation->setEndValue(0);
    } else {
        profileAnimation->setEndValue(profileWidth);
    }
    profileAnimation->start();
    profileVisible = !profileVisible;
}

void Profile::on_buttonLogout_clicked()
{
    if (homeWindow) {
        homeWindow->close();
    }
    Login *login = new Login;
    login->show();

}

void Profile::on_buttonCarrello_clicked()
{
    if (homeWindow) {
        homeWindow->hide();
    }
    Carrello *carrello = new Carrello(homeWindow, utente);
    carrello->show();

}

void Profile::on_buttonModifica_clicked()
{
    if (homeWindow)
    {
        homeWindow->hide();
    }
    if (registrazioneWindow) {
        delete registrazioneWindow;
    }

    registrazioneWindow = new Registrazione(homeWindow, nullptr, true, utente);
    registrazioneWindow->show();
}

Profile::~Profile()
{

}
