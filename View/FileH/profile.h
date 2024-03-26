#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QLabel>
#include "login.h"
#include "carrello.h"

class Profile : public QWidget
{
    Q_OBJECT

public:
    Profile(Home* home, std::shared_ptr<Utenti> u, QWidget *parent = nullptr);
    ~Profile();


private slots:
    void toggleMenu();
    void on_buttonLogout_clicked();
    void on_buttonCarrello_clicked();
    void on_buttonModifica_clicked();
private:
    QVBoxLayout *mainLayout;
    QVBoxLayout *profileLayout;
    QPushButton *profileButton;
    QPushButton* buttonCarrello;
    QPushButton* buttonModifica;
    QPushButton* buttonLogout;
    QWidget *profileWidget;
    QVBoxLayout *itemsLayout;
    QPropertyAnimation *profileAnimation;

    bool profileVisible;
    int profileWidth;
    int profileHeight;
    Home* homeWindow;
    Registrazione* registrazioneWindow;
    std::shared_ptr<Utenti> utente;

};

#endif // PROFILE_H
