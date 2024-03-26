#ifndef HAMBURGERMENU_H
#define HAMBURGERMENU_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QLabel>
#include "../../Controller/FileH/dbcontroller.h"
#include "../../Model/FileH/Utenti.h"
#include "aggiungiItem.h"

class Home;

class HamburgerMenu : public QWidget
{
    Q_OBJECT

public:
    HamburgerMenu(Home* home, std::shared_ptr<Utenti> u, QWidget *parent=nullptr);

private slots:
    void toggleMenu();
    void on_buttonCatalogo_clicked();
    void on_buttonCibo_clicked();
    void on_buttonCasa_clicked();
    void on_buttonVestiti_clicked();
    void on_buttonTrasporti_clicked();
    void on_buttonLibri_clicked();
    void addElement();

private:
    QVBoxLayout *mainLayout;
    QVBoxLayout *menuLayout;
    QPushButton *hamburgerButton;
    QWidget *menuWidget;
    QVBoxLayout *itemsLayout;
    QPropertyAnimation *menuAnimation;
    QPushButton* vestiti;
    QPushButton* casa;
    QPushButton* trasporti;
    QPushButton* libri;
    QPushButton* cibo;
    QPushButton* catalogo;
    QPushButton* aggiungiAlCatalogo;

    bool menuVisible;
    int menuWidth;
    DbController dbController;
    Home* homeWindow;
    std::shared_ptr<Utenti> utente;
};

#endif // HAMBURGERMENU_H

