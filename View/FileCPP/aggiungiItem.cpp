#include "../FileH/aggiungiItem.h"
#include <QCoreApplication>

#include "../FileH/home.h"

AggiungiItem::AggiungiItem(Home* home, std::shared_ptr<Utenti> u, QWidget *parent) :
    QDialog(parent), homeWindow(home), utente(u)
{
    aggiungiButton = new QPushButton("Aggiungi");
    labelConnect2=new QLabel;
    mainLayout = new QVBoxLayout(this);

    // Layout per gli elementi sopra il form
    QHBoxLayout* controlsLayout = new QHBoxLayout();

    // Pulsante "Indietro" in alto a destra
    indietro = new QPushButton("Indietro");

    labelComboLayout = new QVBoxLayout();
    // Aggiungi il pulsante "Indietro" in alto a destra
    labelComboLayout->addWidget(indietro, 0, Qt::AlignRight);
    // Layout per la label e la combobox al centro


    QString s = QString::fromStdString("Che tipo di oggetto vuoi aggiungere?");
    labelConnect = new QLabel(s);
    comboBox = new QComboBox(this);
    comboBox->addItem(" ");
    comboBox->addItem("Casa");
    comboBox->addItem("Cibo");
    comboBox->addItem("Libri");
    comboBox->addItem("Trasporti");
    comboBox->addItem("Vestiti");

    // Imposta l'allineamento del testo al centro
    labelConnect->setAlignment(Qt::AlignCenter);

    // Aggiungi la label e la combobox al layout
    labelComboLayout->addWidget(labelConnect);
    labelComboLayout->addWidget(comboBox);

    // Imposta la politica di espansione del layout della label e della combobox
    labelComboLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    // Aggiungi il layout della label e della combobox al layout dei controlli
    controlsLayout->addLayout(labelComboLayout);

    // Aggiungi il layout dei controlli sopra a mainLayout
    mainLayout->addLayout(controlsLayout);

    // Layout per il form al centro sotto il layout dei controlli
    formContainerLayout = new QVBoxLayout();

    // Imposta la politica di espansione del formContainerLayout
    formContainerLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    labelComboLayout->addWidget(aggiungiButton, 0, Qt::AlignVCenter);
    // Aggiungi il formContainerLayout sotto al layout dei controlli
    mainLayout->addLayout(formContainerLayout);

    connect(indietro, &QPushButton::clicked, this, &AggiungiItem::goBack);
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxIndexChanged(int)));
    connect(aggiungiButton, &QPushButton::clicked, this, &AggiungiItem::aggiungiWithAdditionalData);
}


AggiungiItem::~AggiungiItem()
{
}

void AggiungiItem::goBack()
{
    this->close();
    Home *home=new Home(utente);
    home->show();
    home->raise();
}

void AggiungiItem::onComboBoxIndexChanged(int index) {
	if (index==0)
    {
    	QMessageBox::critical(this, "Errore", "Seleziona un tipo di oggetto da inserire");
    	clearFormLayouts();
        return;
    }
    enome = new QLineEdit();
    edescrizione = new QLineEdit();
    eprezzo = new QLineEdit();
    ecoloreCasa = new QLineEdit();
    ecoloreVestiti = new QLineEdit();
    egenereCasa = new QLineEdit();
    egenereVestiti = new QLineEdit();
    egenereCibo= new QLineEdit();
    egenereLibri = new QLineEdit();
    eautore = new QLineEdit();
    eisbn = new QLineEdit();
    etaglia = new QLineEdit();
    edurata = new QLineEdit();

    clearFormLayouts();
    formLayout = new QFormLayout();
    formLayouts.append(formLayout);
    formLayout->addRow("Nome:", enome);
    formLayout->addRow("Descrizione:", edescrizione);
    formLayout->addRow("Prezzo:", eprezzo);
    
    if (index==1) {
        formLayout->addRow("Colore:", ecoloreCasa);
        formLayout->addRow("Tipologia:", egenereCasa);
    } else if (index==3) {
        formLayout->addRow("Autore:", eautore);
        formLayout->addRow("ISBN:", eisbn);
        formLayout->addRow("Genere:", egenereLibri);
    } else if (index==5) {      
        formLayout->addRow("Taglia:", etaglia);
        formLayout->addRow("Colore:", ecoloreVestiti);
        formLayout->addRow("Tipo capo:", egenereVestiti);
    }
    else if (index==2) {
        formLayout->addRow("Tipo di piatto:", egenereCibo);
    }
    else if (index==4) {
        formLayout->addRow("Durata:", edurata);
    }
	
    formContainerLayout->addLayout(formLayout);
    connect(eprezzo, &QLineEdit::textChanged, this, &AggiungiItem::onPrezzoTextChanged);
}


void AggiungiItem::clearFormLayouts() {
    for (QFormLayout* layout : formLayouts) {
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != nullptr) {
            QWidget* widget = item->widget();
            if (widget) {
                layout->removeWidget(widget);
                delete widget;
            }
            delete item;
        }
        delete layout;
    }
    formLayouts.clear();
}
void AggiungiItem::aggiungi(int index) {

    QString qnome=enome->text();
    std::string nome=qnome.toStdString();

    QString qdescrizione=edescrizione->text();
    std::string descrizione=qdescrizione.toStdString();

    QString qprezzo=eprezzo->text();
    double prezzo=qprezzo.toDouble();

    QString qcoloreCasa=ecoloreCasa->text();
    std::string coloreCasa=qcoloreCasa.toStdString();

    QString qcoloreVestiti=ecoloreVestiti->text();
    std::string coloreVestiti=qcoloreVestiti.toStdString();

    QString qgenereCasa=egenereCasa->text();
    std::string genereCasa=qgenereCasa.toStdString();

    QString qgenereLibro=egenereLibri->text();
    std::string genereLibro=qgenereLibro.toStdString();

    QString qgenereVestiti=egenereVestiti->text();
    std::string tipologiaVestiti=qgenereVestiti.toStdString();

    QString qgenereCibo=egenereCibo->text();
    std::string genereCibo=qgenereCibo.toStdString();

    QString qautore=eautore->text();
    std::string autore=qautore.toStdString();

    QString qisbn=eisbn->text();
    std::string isbn=qisbn.toStdString();

    QString qtaglia=etaglia->text();
    std::string taglia=qtaglia.toStdString();

    QString qdurata=edurata->text();
    std::string durata=qdurata.toStdString();

    bool agg = false;
    DbController dbcontroller;
    if (index==1)
    {
        agg=dbcontroller.addToCasa(nome,descrizione,prezzo,genereCasa,coloreCasa);
    }
    else if (index==2)
    {
        agg=dbcontroller.addToCibo(nome,descrizione,prezzo,genereCibo);
    }
    else if (index==3)
    {
        agg=dbcontroller.addToLibri(nome,descrizione,prezzo,genereLibro,autore,isbn);
    }
    else if (index==4)
    {
        agg=dbcontroller.addToTrasporti(nome,descrizione,prezzo,durata);
    }
    else if (index==5)
    {
        agg=dbcontroller.addToVestiti(nome,descrizione,prezzo,tipologiaVestiti,taglia,coloreVestiti);
    }
    if (agg)
    {
        labelConnect2->setText("Elemento aggiunto al catalogo");
        labelComboLayout->addWidget(labelConnect2, 0, Qt::AlignVCenter);
        labelConnect2->setVisible(true);
        QTimer::singleShot(1500, this, &AggiungiItem::hideAggiuntoLabel);
    }
    else
    {
        labelConnect2->setText("Elemento non aggiunto al catalogo");
        labelComboLayout->addWidget(labelConnect2, 0, Qt::AlignVCenter);
        labelConnect2->setVisible(true);
        QTimer::singleShot(1500, this, &AggiungiItem::hideAggiuntoLabel);
    }

}

void AggiungiItem::aggiungiWithAdditionalData() {
    if (comboBox->currentIndex()==0) {
        QMessageBox::critical(this, "Errore", "Seleziona un tipo di oggetto da inserire");
        return;
    }
    QString prezzoStr = eprezzo->text();
    prezzoStr = prezzoStr.replace(",", ".").trimmed();
    bool isDouble;
    prezzoStr.toDouble(&isDouble);

    if (enome->text().isEmpty() ||
        edescrizione->text().isEmpty() ||
        eprezzo->text().isEmpty() ||
        (comboBox->currentIndex()==1 && (ecoloreCasa->text().isEmpty() || egenereCasa->text().isEmpty())) ||
        (comboBox->currentIndex()==3 && (eautore->text().isEmpty() || eisbn->text().isEmpty() || egenereLibri->text().isEmpty())) ||
        (comboBox->currentIndex()==5 && (etaglia->text().isEmpty() || ecoloreVestiti->text().isEmpty() || egenereVestiti->text().isEmpty())) ||
        (comboBox->currentIndex()==2 && egenereCibo->text().isEmpty()) ||
        (comboBox->currentIndex()==4 && edurata->text().isEmpty())) {
        QMessageBox::critical(this, "Errore", "Tutti i campi devono essere riempiti");
        return;
    }
    if (!isDouble) {

        QMessageBox::critical(this, "Errore", "Il prezzo dev'essere un valore numerico");
        return;
    }

    aggiungi(comboBox->currentIndex());
}


void AggiungiItem::hideAggiuntoLabel()
{
    labelConnect2->setVisible(false);
}

void AggiungiItem::onPrezzoTextChanged(const QString &text) {

   QString prezzoText = text.trimmed().replace(',', '.');

    eprezzo->setText(prezzoText);
}


