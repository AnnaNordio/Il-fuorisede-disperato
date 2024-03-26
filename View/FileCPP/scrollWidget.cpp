#include "../FileH/scrollWidget.h"
#include <iostream>
#include <string>
#include <sstream>
#include "../FileH/itemWidget.h"
#include "../FileH/modificaItem.h"
#include "../FileH/carrello.h"
#include <QMouseEvent>

ScrollWidget::ScrollWidget(DoubleList <Item*> lista, Item* item, bool admin, shared_ptr<Utenti>user, bool createdFromItemWidget, bool createdFromCart, QWidget *parent, Carrello* carrello) : QWidget(parent),  lista(lista), oggetto(item), admin(admin), utente(user), carrello(carrello)
{
    dbc= new DbController();
    QGridLayout* layout = new QGridLayout(this);
    titolo = new QLabel(QString::fromStdString(oggetto->getName()));
    titolo->setStyleSheet("font-weight: bold;");
    aggiuntoLabel = new QLabel("Aggiornamento carrello...", this);
    aggiuntoLabel->setAlignment(Qt::AlignCenter);
    aggiuntoLabel->setVisible(false);

    int quanti=dbc->howmanybyUser(oggetto, user->getUser());
    quantità=new QLabel("Quantità: "+QString::number(quanti));
    quantità->setVisible(createdFromCart);
    modifica=new QPushButton("Modifica");
    modifica->setVisible(!createdFromItemWidget&&admin);
    rimuovi=new QPushButton("Rimuovi");
    rimuovi->setVisible(!createdFromItemWidget&&admin);
    aggiungi = new QPushButton("Aggiungi al carrello");
    aggiungi->setVisible(!createdFromItemWidget&&!admin);
    rimuoviCarrello = new QPushButton("Rimuovi");
    rimuoviCarrello->setVisible(!createdFromItemWidget);
    rimuoviCarrello->setVisible(createdFromCart);
    spinBox = new QSpinBox();
    spinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spinBox->setVisible(!createdFromItemWidget&&!admin);
    spinBox->setValue(1);
    spinBox->setMinimum(1);
    spinBox->setMaximum(oggetto->getQuantity());
    spinBox->setReadOnly(true);
    QPushButton* increaseButton = new QPushButton("+");
    QPushButton* decreaseButton = new QPushButton("-");
    increaseButton->setFixedSize(20, 20);
    decreaseButton->setFixedSize(20, 20);
    increaseButton->setVisible(!createdFromItemWidget&&!admin);
    decreaseButton->setVisible(!createdFromItemWidget&&!admin);
    spinBoxCarrello = new QSpinBox();
    spinBoxCarrello->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spinBoxCarrello->setVisible(!createdFromItemWidget);
    spinBoxCarrello->setVisible(createdFromCart);
    spinBoxCarrello->setValue(1);
    spinBoxCarrello->setMinimum(1);
    spinBoxCarrello->setMaximum(dbc->howmanybyUser(oggetto, user->getUser()));
    spinBoxCarrello->setReadOnly(true);
    QPushButton* increaseButtonCarrello = new QPushButton("+");
    increaseButtonCarrello->setStyleSheet("QSpinBox {margin-right: 0px;}");
    QPushButton* decreaseButtonCarrello = new QPushButton("-");
    increaseButtonCarrello->setFixedSize(20, 20);
    decreaseButtonCarrello->setFixedSize(20, 20);
    increaseButtonCarrello->setVisible(!createdFromItemWidget);
    increaseButtonCarrello->setVisible(createdFromCart);
    decreaseButtonCarrello->setVisible(!createdFromItemWidget);
    decreaseButtonCarrello->setVisible(createdFromCart);


    double doubleValue = oggetto->getPrice();
    std::stringstream ss;
    ss << doubleValue;

    prezzo = new QLabel("Prezzo: "+QString::fromStdString(ss.str() + "€"));
    descrizione = new QLabel(QString::fromStdString(oggetto->getDesc()));

    layout->addWidget(titolo, 1, 1, 1, 4);
    layout->addWidget(descrizione, 2, 1, 1, 4);
    layout->addWidget(aggiuntoLabel, 1, 5, Qt::AlignTop);
    layout->addWidget(quantità, 1, 5, Qt::AlignTop);
    layout->addWidget(prezzo, 3, 1, 1, 4, Qt::AlignLeft);
    layout->addWidget(increaseButton, 2, 6, Qt::AlignLeft);
    layout->addWidget(spinBox, 2, 5, Qt::AlignTop);
    layout->addWidget(decreaseButton, 2, 4, Qt::AlignRight);
    layout->addWidget(increaseButtonCarrello, 2, 6, Qt::AlignLeft);
    layout->addWidget(spinBoxCarrello, 2, 5, Qt::AlignTop);
    layout->addWidget(decreaseButtonCarrello, 2, 4, Qt::AlignRight);


    layout->addWidget(modifica, 2, 5, Qt::AlignTop);
    layout->addWidget(rimuovi, 1, 5, Qt::AlignTop);
    layout->addWidget(aggiungi, 3, 5, Qt::AlignTop);
    layout->addWidget(rimuoviCarrello, 3, 5, Qt::AlignTop);

    connect(this, &ScrollWidget::clickWidget, this, &ScrollWidget::openItemWidget);

    connect(modifica, &QPushButton::clicked, this, &ScrollWidget::openModificaItem);
    connect(rimuovi, &QPushButton::clicked, this, &ScrollWidget::removeFromCataloge);

    connect(aggiungi, &QPushButton::clicked, this, &ScrollWidget::addToCart);
    connect(rimuoviCarrello, &QPushButton::clicked, this, &ScrollWidget::removeFromCart);

    connect(increaseButton, &QPushButton::clicked, spinBox, &QSpinBox::stepUp);
    connect(decreaseButton, &QPushButton::clicked, spinBox, &QSpinBox::stepDown);

    connect(increaseButtonCarrello, &QPushButton::clicked, spinBoxCarrello, &QSpinBox::stepUp);
    connect(decreaseButtonCarrello, &QPushButton::clicked, spinBoxCarrello, &QSpinBox::stepDown);
    delete dbc;
}



void ScrollWidget::openModificaItem(){
    ModificaItem detailItem(oggetto, this);
    detailItem.setModal(true);
    connect(&detailItem, &ModificaItem::itemUpdated, this, &ScrollWidget::itemUpdated);
    detailItem.exec();
}

void ScrollWidget::itemUpdated(Item* updatedItem) {
    oggetto = updatedItem;
    double doubleValue = oggetto->getPrice();
    std::stringstream ss;
    ss << doubleValue;
    titolo->setText(QString::fromStdString(oggetto->getName()));
    prezzo->setText("Prezzo: "+QString::fromStdString(ss.str() + "€"));;
    descrizione->setText(QString::fromStdString(oggetto->getDesc()));
    update();
}


void ScrollWidget::openItemWidget(){
    ItemWidget detailItem(lista, oggetto, admin, nullptr, utente);
    detailItem.setModal(true);
    detailItem.exec();
}

void ScrollWidget::mousePressEvent(QMouseEvent* event){
    if (event->button() == Qt::LeftButton) {
        emit clickWidget();
    }
}

void ScrollWidget::addToCart()

{
    DbController *dbc=new DbController();
    int quantità=spinBox->value();
    if (quantità+dbc->howmany(oggetto)>oggetto->getQuantity())
    {
        QMessageBox::critical(this, "Errore","La somma degli oggetti di questo tipo in tutti i carrelli supera la disponibilità in magazzino");
            return;
    }
    else
    {
        int oldQ=oggetto->getQuantity();
            dbc->aggiungiAlCarrello(oggetto ,utente->getUser(), quantità);
        aggiuntoLabel->setVisible(true);
        oggetto->setQuantity(oldQ-quantità);
        QTimer::singleShot(1250, this, &ScrollWidget::hideAggiuntoLabel);
    }

}

void ScrollWidget::hideAggiuntoLabel()
{
    aggiuntoLabel->setVisible(false);
}

void ScrollWidget::removeFromCataloge()
{
    DbController *dbc=new DbController();
    std::cout<< "Hai rimosso \n";
    (*(lista.search(oggetto)))->toString(std::cout); //cerca nella lista e stampa l'oggetto rimosso per essere sicuri
    lista.remove(oggetto);
    std::cout<<"La lista degli oggetti nella schermata ora e': \n";
    lista.print(); //stampa da terminale la lista di puntatori Item* rimasti in catalogo
    dbc->remove(oggetto);
    QFrame* frame = qobject_cast<QFrame*>(parentWidget());
    emit removeRequested(frame);
}

void ScrollWidget::removeFromCart()
{
    DbController *dbc=new DbController();
    int quantità = spinBoxCarrello->value();

    if (dbc->rimuoviDalCarrello(oggetto, utente->getUser(), quantità))
    {
        if(dbc->howmanybyUser(oggetto, utente->getUser())==0)
        {
            dbc->destroy(oggetto, utente->getUser());
        }
        QMessageBox::StandardButton reply = QMessageBox::warning(this, "Aggiornamento Carrello", "Carrello aggiornato", QMessageBox::Ok);

        if (reply == QMessageBox::Ok) {
            carrello->apriCarrello();
        }
    }
}




