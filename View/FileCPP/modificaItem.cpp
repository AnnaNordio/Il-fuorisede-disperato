#include "../FileH/modificaItem.h"
#include <QCoreApplication>
#include <QLayout>
#include <QPushButton>
#include "../FileH/scrollWidget.h"

ModificaItem::ModificaItem(Item* oggetto, ScrollWidget* scrollWidget, QWidget *parent) :
    QDialog(parent), oggettoDaModificare(oggetto), scrollWidget(scrollWidget)
{
    QLabel* label = new QLabel(QString::fromStdString(oggetto->getName()));
    label->setStyleSheet("font-weight: bold;");
    QGridLayout* layout = new QGridLayout(this);

    // Etichette per i campi
    QLabel* nameLabel = new QLabel("Nome:");
    QLabel* priceLabel = new QLabel("Prezzo:");
    QLabel* descriptionLabel = new QLabel("Descrizione:");

    QLabel* durataLabel = nullptr;
    QLabel* tagliaLabel = nullptr;
    QLabel* coloreCasaLabel = nullptr;
    QLabel* coloreVestitiLabel = nullptr;
    QLabel* genereCasaLabel = nullptr;
    QLabel* genereVestitiLabel = nullptr;
    QLabel* genereCiboLabel = nullptr;
    QLabel* genereLibriLabel = nullptr;
    QLabel* autoreLabel = nullptr;
    QLabel* isbnLabel = nullptr;

    // Campi di input
    nameEdit = new QLineEdit(QString::fromStdString(oggetto->getName()));
    priceEdit = new QLineEdit(QString::number(oggetto->getPrice()));
    descriptionEdit = new QTextEdit(QString::fromStdString(oggetto->getDesc()));
    layout->addWidget(label);
    layout->addWidget(nameLabel);
    layout->addWidget(nameEdit);
    layout->addWidget(priceLabel);
    layout->addWidget(priceEdit);
    layout->addWidget(descriptionLabel);
    layout->addWidget(descriptionEdit);

    if (Trasporto* trasporti = dynamic_cast<Trasporto*>(oggetto)) {
        durataLabel = new QLabel("Durata:");
        durata = new QLineEdit(QString::fromStdString(trasporti->getDurata()));
        layout->addWidget(durataLabel);
        layout->addWidget(durata);
        tipo="Trasporti";
    }
    else if (Vestiti* vestiti = dynamic_cast<Vestiti*>(oggetto)) {
        tagliaLabel = new QLabel("Taglia:");
        taglia = new QLineEdit(QString::fromStdString(vestiti->getTaglia()));
        coloreVestitiLabel = new QLabel("Colore:");
        coloreVestiti = new QLineEdit(QString::fromStdString(vestiti->getColore()));
        genereVestitiLabel= new QLabel("Tipo capo:");
        genereVestiti = new QLineEdit(QString::fromStdString(vestiti->getGenere()));
        layout->addWidget(tagliaLabel);
        layout->addWidget(taglia);
        layout->addWidget(coloreVestitiLabel);
        layout->addWidget(coloreVestiti);
        layout->addWidget(genereVestitiLabel);
        layout->addWidget(genereVestiti);
        tipo="Vestiti";
    }
    else if (Libri* libri = dynamic_cast<Libri*>(oggetto)) {
        autoreLabel = new QLabel("Autore:");
        autore = new QLineEdit(QString::fromStdString(libri->getAutore()));
        genereLibriLabel = new QLabel("Genere:");
        genereLibri = new QLineEdit(QString::fromStdString(libri->getGenere()));
        isbnLabel= new QLabel("ISBN:");
        isbn = new QLineEdit(QString::fromStdString(libri->getIsbn()));
        layout->addWidget(autoreLabel);
        layout->addWidget(autore);
        layout->addWidget(genereLibriLabel);
        layout->addWidget(genereLibri);
        layout->addWidget(isbnLabel);
        layout->addWidget(isbn);
        tipo="Libri";
    }
    else if (Casa* casa = dynamic_cast<Casa*>(oggetto)) {
        genereCasaLabel = new QLabel("Tipologia:");
        genereCasa = new QLineEdit(QString::fromStdString(casa->getGenere()));
        coloreCasaLabel = new QLabel("Colore:");
        coloreCasa = new QLineEdit(QString::fromStdString(casa->getColore()));
        layout->addWidget(genereCasaLabel);
        layout->addWidget(genereCasa);
        layout->addWidget(coloreCasaLabel);
        layout->addWidget(coloreCasa);
        tipo="Casa";
    }
    else if (Cibo* cibo = dynamic_cast<Cibo*>(oggetto)) {
        genereCiboLabel = new QLabel("Tipo piatto:");
        genereCibo = new QLineEdit(QString::fromStdString(cibo->getGenere()));
        layout->addWidget(genereCiboLabel);
        layout->addWidget(genereCibo);
        tipo="Cibo";
    }

    // Pulsante di conferma
    QPushButton* confermaButton = new QPushButton("Conferma");
    layout->addWidget(confermaButton);

    // Connetti il pulsante di conferma alla funzione di salvataggio
    connect(confermaButton, &QPushButton::clicked, this, &ModificaItem::salvaModifiche);
}


void ModificaItem::salvaModifiche() {
    QString prezzoStr = priceEdit->text().trimmed();

    prezzoStr.replace(',', '.');

    bool conversionOk;
    double newPrice = prezzoStr.toDouble(&conversionOk);

    if (!conversionOk) {
        // Se la conversione fallisce, mostra un messaggio di errore
        QMessageBox::critical(this, "Errore", "Il prezzo dev'essere un valore numerico");
        return;
    }

    // Recupera i dati modificati dai campi di input e aggiornali nell'oggetto Item
    QString newName = nameEdit->text();
    QString newDescription = descriptionEdit->toPlainText();

    oggettoDaModificare->setName(newName.toStdString());
    oggettoDaModificare->setPrice(newPrice);
    oggettoDaModificare->setDesc(newDescription.toStdString());
    if (Trasporto* trasporti = dynamic_cast<Trasporto*>(oggettoDaModificare)) {
        QString newdurata=durata->text();
        trasporti->setDurata(newdurata.toStdString());
    }
    else if (Vestiti* vestiti = dynamic_cast<Vestiti*>(oggettoDaModificare)) {
        QString newtaglia=taglia->text();
        vestiti->setTaglia(newtaglia.toStdString());
        QString newcolore=coloreVestiti->text();
        vestiti->setColore(newcolore.toStdString());
        QString newtipologia=genereVestiti->text();
        vestiti->setGenere(newtipologia.toStdString());
    }
    else if (Libri* libri = dynamic_cast<Libri*>(oggettoDaModificare)) {
        QString newautore=autore->text();
        libri->setAutore(newautore.toStdString());
        QString newisbn=isbn->text();
        libri->setIsbn(newisbn.toStdString());
        QString newgenere=genereLibri->text();
        libri->setGenere(newgenere.toStdString());
    }
    else if (Casa* casa = dynamic_cast<Casa*>(oggettoDaModificare)) {
        QString newtipologia=genereCasa->text();
        casa->setGenere(newtipologia.toStdString());
        QString newcolore=coloreCasa->text();
        casa->setColore(newcolore.toStdString());
    }
    else if (Cibo* cibo = dynamic_cast<Cibo*>(oggettoDaModificare)) {
        QString newgenere=genereCibo->text();
        cibo->setGenere(newgenere.toStdString());
    }

    DbController dbc;
    dbc.modifica(oggettoDaModificare,tipo);
    emit itemUpdated(oggettoDaModificare);
    accept();
}



ModificaItem::~ModificaItem()
{
}


