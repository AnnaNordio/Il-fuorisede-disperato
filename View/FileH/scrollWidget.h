#ifndef SCROLLWIDGET_H
#define SCROLLWIDGET_H
#include <QWidget>
#include<QLabel>
#include<QPushButton>
#include <QTimer>
#include <QSpinBox>
#include"../../Model/FileH/Item.h"
#include"../../Model/FileH/DoubleList.h"
#include"../../Controller/FileH/dbcontroller.h"
#include <QGridLayout>
class Carrello;
class ScrollWidget:public QWidget{
    Q_OBJECT
public:
    ScrollWidget(DoubleList <Item*> lista, Item* item, bool admin, shared_ptr<Utenti>user=nullptr, bool createdFromItemWidget=false, bool createdFromCart=false, QWidget *parent=nullptr, Carrello* carrello=nullptr);

private slots:
    void openModificaItem();
    void openItemWidget();
    void addToCart();
    void hideAggiuntoLabel();
    void removeFromCataloge();
    void removeFromCart();
    void itemUpdated(Item* updatedItem);


signals:
    void clickWidget();
    void viewItem();
    void removeRequested(QFrame* frame);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    QLabel* titolo;
    QLabel* prezzo;
    QLabel* descrizione;
    QLabel *aggiuntoLabel;
    QLabel *quantità;
    QSpinBox* spinBox;
    QSpinBox* spinBoxCarrello;
    QPushButton* modifica;
    QPushButton* rimuovi;
    QPushButton* rimuoviCarrello;
    QPushButton* aggiungi;
    DoubleList <Item*> lista;
    Item* oggetto;
    bool admin;
    DbController *dbc;
    shared_ptr<Utenti>utente;
    Carrello* carrello;
};

#endif // SCROLLWIDGET_H
