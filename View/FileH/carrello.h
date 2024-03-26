#ifndef CARRELLO_H
#define CARRELLO_H

#include <QDialog>
#include<QLabel>
#include<QScrollArea>
#include <QScrollBar>
#include<QLayout>
#include "../../Model/FileH/Utenti.h"
#include "../../Model/FileH/DoubleList.h"
#include "../../Controller/FileH/dbcontroller.h"
#include"../../Model/FileH/Item.h"
#include"../FileH/scrollWidget.h"


class Carrello : public QDialog
{
    Q_OBJECT

public:

    Carrello(Home *home, std::shared_ptr<Utenti> u, const std::string& itemType="Item", QWidget *parent = nullptr);
    double updateContent(const std::string& itemType);
    ~Carrello();

public slots:
    //void removeFrame(QFrame* frame);
    void on_buttonIndietro_clicked();
    void apriCarrello();
    void pagamento();

private:
    QLabel* labelTitle;
    std::shared_ptr<Utenti> utente;
    Home *home;
    QScrollArea* scrollArea;
    QVBoxLayout* scrollLayout;
    std::string itemType;
    DoubleList<Item*> oggetti;
    QPushButton* indietro;
    double sommatotale=0;
};

#endif // CARRELLO_H
