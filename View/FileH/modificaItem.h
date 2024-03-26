#ifndef MODIFICAITEM_H
#define MODIFICAITEM_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <QMessageBox>
#include "../../Model/FileH/Item.h"
#include "../../Model/FileH/Trasporto.h"
#include "../../Model/FileH/Casa.h"
#include "../../Model/FileH/Cibo.h"
#include "../../Model/FileH/Vestiti.h"
#include "../../Model/FileH/Libri.h"
#include "../../Controller/FileH/dbcontroller.h"


class ScrollWidget;

class ModificaItem : public QDialog
{
    Q_OBJECT

public:

    ModificaItem(Item* oggetto, ScrollWidget* scrollWidget, QWidget *parent=nullptr);
    ~ModificaItem();

signals:
    void itemUpdated(Item* updatedItem);
public slots:
    void salvaModifiche();

private:
    Item* oggettoDaModificare;
    ScrollWidget* scrollWidget;
    std::string tipo;
    QLineEdit* nameEdit;
    QLineEdit* priceEdit;
    QTextEdit* descriptionEdit;
    QLineEdit* durata;
    QLineEdit* taglia;
    QLineEdit* coloreCasa;
    QLineEdit* coloreVestiti;
    QLineEdit* genereCasa;
    QLineEdit* genereVestiti;
    QLineEdit* genereCibo;
    QLineEdit* genereLibri;
    QLineEdit* autore;
    QLineEdit* isbn;


};

#endif // MODIFICAITEM_H


