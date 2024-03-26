#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include<QLabel>
#include<QScrollArea>
#include <QScrollBar>
#include<QLayout>
#include "../../Model/FileH/Utenti.h"
#include "../../Model/FileH/DoubleList.h"
#include "../../Controller/FileH/dbcontroller.h"
#include"../../Model/FileH/Item.h"
#include"../FileH/scrollWidget.h"
#include "hamburgermenu.h"
#include "profile.h"


class Home : public QMainWindow
{
    Q_OBJECT

public:
    Home(std::shared_ptr<Utenti> u, const std::string& itemType="Item", QWidget *parent = nullptr);
    void updateContent(const std::string& itemType, bool admin);
    ~Home();

public slots:
    void removeFrame(QFrame* frame);

private:
    HamburgerMenu* hamburgermenu;
    Profile* profile;
    QLabel* labelTitle;
    QScrollArea* scrollArea;
    QVBoxLayout* scrollLayout;
    QVBoxLayout* scrollVBoxLayout;
    std::shared_ptr<Utenti> utente;
    std::string itemType;
    DoubleList<Item*> oggetti;
};

#endif // HOME_H
