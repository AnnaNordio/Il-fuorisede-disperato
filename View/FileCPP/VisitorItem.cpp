#include "../FileH/VisitorItem.h"
#include <QLabel>
#include <QWidget>
#include<QLayout>

QWidget* VisitorItem:: getWidget() const{

    return widget;
}
void VisitorItem::visitCasa(Casa& casa){

    QLabel* genere= new QLabel("Tipologia: " + QString::fromStdString(casa.getGenere()));
    QLabel* colore= new QLabel("Colore: " + QString::fromStdString(casa.getColore()));

    widget= new QWidget();
    QVBoxLayout* layout= new QVBoxLayout(widget);
    layout->addWidget(genere);
    layout->addWidget(colore);

}

void VisitorItem::visitCibo(Cibo& cibo){

    QLabel* genere= new QLabel("Tipo di piatto: " + QString::fromStdString(cibo.getGenere()));

    widget= new QWidget();
    QVBoxLayout* layout= new QVBoxLayout(widget);
    layout->addWidget(genere);

}

void VisitorItem::visitVestiti(Vestiti& vestito){

    QLabel* genere= new QLabel("Tipo capo: " + QString::fromStdString(vestito.getGenere())+"\n");
    QLabel* colore= new QLabel("Colore: " + QString::fromStdString(vestito.getColore())+"\n");
    QLabel* taglia= new QLabel("Taglia: " + QString::fromStdString(vestito.getTaglia())+"\n");


    widget= new QWidget();
    QVBoxLayout* layout= new QVBoxLayout(widget);
    layout->addWidget(genere);
    layout->addWidget(colore);
    layout->addWidget(taglia);

}

void VisitorItem::visitTrasporto(Trasporto& trasporto){

    QLabel* durata= new QLabel("Durata: " + QString::fromStdString(trasporto.getDurata()));
    widget= new QWidget();
    QVBoxLayout* layout= new QVBoxLayout(widget);
    layout->addWidget(durata);
}

void VisitorItem::visitLibri(Libri& libro){

    QLabel* autore= new QLabel("Autore: " + QString::fromStdString(libro.getAutore())+"\n");
    QLabel* genere= new QLabel("Genere: " + QString::fromStdString(libro.getGenere()) +"\n");
    QLabel* isbn= new QLabel("ISBN: " + QString::fromStdString(libro.getIsbn()));


    widget= new QWidget();
    QVBoxLayout* layout= new QVBoxLayout(widget);
    layout->addWidget(genere);
    layout->addWidget(autore);
    layout->addWidget(isbn);


}
