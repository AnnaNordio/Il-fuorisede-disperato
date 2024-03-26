#include "../FileH/hamburgermenu.h"
#include "../FileH/home.h"

HamburgerMenu::HamburgerMenu(Home* home, std::shared_ptr<Utenti> u, QWidget *parent)
    : QWidget(parent), menuVisible(false), homeWindow(home), utente(u)
{
    mainLayout = new QVBoxLayout(this);
    menuLayout = new QVBoxLayout();
    hamburgerButton = new QPushButton("☰", this);
    menuWidget = new QWidget(this);
    itemsLayout = new QVBoxLayout(menuWidget);
    menuAnimation = new QPropertyAnimation(menuWidget, "maximumWidth", this);

    aggiungiAlCatalogo=new QPushButton("\tNuovo elemento", menuWidget);
    aggiungiAlCatalogo->setIcon(QIcon(":Immagini/add.png"));
    aggiungiAlCatalogo->setHidden(!u->getIsAdmin());
    vestiti = new QPushButton("\tVestiti", menuWidget);
    vestiti->setIcon(QIcon(":Immagini/maglia.png"));
    cibo = new QPushButton("\tCibo", menuWidget);
    cibo->setIcon(QIcon(":Immagini/panino.png"));
    trasporti = new QPushButton("\tTrasporti", menuWidget);
    trasporti->setIcon(QIcon(":Immagini/bus.png"));
    casa = new QPushButton("\tCasa", menuWidget);
    casa->setIcon(QIcon(":Immagini/casa.png"));
    libri = new QPushButton("\tLibri", menuWidget);
    libri->setIcon(QIcon(":Immagini/libro.png"));
    catalogo = new QPushButton("\tCatalogo", menuWidget);
    catalogo->setIcon(QIcon(":Immagini/catalogo.png"));
    itemsLayout->addWidget(aggiungiAlCatalogo);
    itemsLayout->addWidget(catalogo);
    itemsLayout->addWidget(vestiti);
    itemsLayout->addWidget(cibo);
    itemsLayout->addWidget(trasporti);
    itemsLayout->addWidget(casa);
    itemsLayout->addWidget(libri);

    hamburgerButton->setFixedSize(40, 40);
    hamburgerButton->setStyleSheet("font-size: 24px;");

    menuWidth = width() / 4;

    menuWidget->setMaximumWidth(0);
    menuWidget->setStyleSheet("background-color: #d1d1d1;");

    menuAnimation->setDuration(300);

    connect(hamburgerButton, &QPushButton::clicked, this, &HamburgerMenu::toggleMenu);
    connect(catalogo, &QPushButton::clicked, this, &HamburgerMenu::on_buttonCatalogo_clicked);
    connect(libri, &QPushButton::clicked, this, &HamburgerMenu::on_buttonLibri_clicked);
    connect(casa, &QPushButton::clicked, this, &HamburgerMenu::on_buttonCasa_clicked);
    connect(cibo, &QPushButton::clicked, this, &HamburgerMenu::on_buttonCibo_clicked);
    connect(vestiti, &QPushButton::clicked, this, &HamburgerMenu::on_buttonVestiti_clicked);
    connect(trasporti, &QPushButton::clicked, this, &HamburgerMenu::on_buttonTrasporti_clicked);
    connect(aggiungiAlCatalogo, &QPushButton::clicked, this, &HamburgerMenu::addElement);

    menuLayout->addWidget(hamburgerButton);
    menuLayout->addWidget(menuWidget);

    mainLayout->addLayout(menuLayout);
}

void HamburgerMenu::toggleMenu()
{
    if (menuVisible) {
        menuAnimation->setEndValue(0);
    } else {
        menuAnimation->setEndValue(menuWidth);
    }
    menuAnimation->start();
    menuVisible = !menuVisible;
}

void HamburgerMenu::on_buttonCatalogo_clicked()
{
    homeWindow->updateContent("Item", utente->getIsAdmin());
}
void HamburgerMenu::on_buttonCibo_clicked(){
    homeWindow->updateContent("Cibo", utente->getIsAdmin());
}
void HamburgerMenu::on_buttonCasa_clicked()
{
    homeWindow->updateContent("Casa", utente->getIsAdmin());
}
void HamburgerMenu::on_buttonVestiti_clicked()
{
    homeWindow->updateContent("Vestiti", utente->getIsAdmin());
}
void HamburgerMenu::on_buttonTrasporti_clicked()
{
    homeWindow->updateContent("Trasporto", utente->getIsAdmin());
}
void HamburgerMenu::on_buttonLibri_clicked()
{
    homeWindow->updateContent("Libri", utente->getIsAdmin());
}
void HamburgerMenu::addElement()
{
    if (homeWindow) {
        homeWindow->close();
    }
    AggiungiItem *addItem=new AggiungiItem(homeWindow, utente, nullptr);
    addItem->resize(600, 512);
    addItem->show();
}
