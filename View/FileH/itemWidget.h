#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H
#include <QDialog>
#include<QLabel>
#include "../../Model/FileH/Item.h"
#include "../../Model/FileH/Utenti.h"
#include "../../Model/FileH/DoubleList.h"

class ItemWidget : public QDialog
{
    Q_OBJECT

public:
    ItemWidget(DoubleList <Item*> lista, Item* oggetto,bool admin, QWidget *parent, shared_ptr<Utenti> user);
    ~ItemWidget();

private slots:

private:

    Item* item;
    shared_ptr<Utenti> utente;
    QLabel* labelConnect;
    DoubleList <Item*> lista;
};

#endif // ITEMWIDGET_H
