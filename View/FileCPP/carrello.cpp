#include "../FileH/home.h"
#include<QString>
#include <QCoreApplication>
#include<QApplication>
#include <string>

Carrello::Carrello(Home *home, std::shared_ptr<Utenti> u, const std::string& itemType,  QWidget *parent):QDialog(parent), utente(u), home(home)
{
    setWindowTitle("Carrello");
    setFixedSize(650, 550);

    labelTitle = new QLabel("Carrello di " + QString::fromStdString(utente->getUser()));
    labelTitle->setStyleSheet("font-weight: bold;");


    indietro = new QPushButton("Indietro");
    QPushButton *paga = new QPushButton("Effettua pagamento");

    QVBoxLayout* layout = new QVBoxLayout(this);

    // Posiziona labelTitle in alto a sinistra
    QHBoxLayout* titleLayout = new QHBoxLayout();
    titleLayout->addWidget(labelTitle);
    titleLayout->addStretch();  // Aggiunge uno spazio vuoto per separare da indietro
    titleLayout->addWidget(indietro);
    layout->addLayout(titleLayout);

    scrollLayout = new QVBoxLayout();
    scrollArea = new QScrollArea;
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setWidgetResizable(true);


    double somma=this->updateContent(itemType);
    QLabel* sommatot = new QLabel("Totale: " + QString::number(somma) + "€");
    sommatot->setStyleSheet("font-weight: bold;");

    QWidget* scrollContent = new QWidget();
    scrollContent->setLayout(scrollLayout);
    scrollArea->setWidget(scrollContent);
    layout->addWidget(scrollArea);

    QHBoxLayout* bottomLayout = new QHBoxLayout();
    bottomLayout->addStretch();
    bottomLayout->addWidget(sommatot);
    bottomLayout->addWidget(paga);
    layout->addLayout(bottomLayout);

    connect(indietro, &QPushButton::clicked, this, &Carrello::on_buttonIndietro_clicked);
    connect(paga, &QPushButton::clicked, this, &Carrello::pagamento);

}


Carrello::~Carrello()
{
}

double Carrello::updateContent(const std::string& itemType) {
    QLayoutItem* item;
    while ((item = scrollLayout->takeAt(0)) != nullptr) {
        QWidget* widget = item->widget();
        if (widget) {
            scrollLayout->removeWidget(widget);
            delete widget;
        }
        delete item;
    }

    // Calcola la dimensione dei frame in base alla dimensione della finestra
    QSize windowSize = scrollArea->viewport()->size();
    int frameWidth = windowSize.width(); // Imposta la larghezza dei frame uguale alla larghezza della finestra

    DbController dbcontroller;

    oggetti = dbcontroller.stampaCarrello(itemType, utente);
    // Imposta l'allineamento del scrollLayout
    scrollLayout->setAlignment(Qt::AlignTop);

    for (DoubleList<Item*>::const_iterator cit = oggetti.begin(); cit != oggetti.end(); ++cit) {
        QFrame* frame = new QFrame;
        frame->setFrameShape(QFrame::Box);
        frame->setLineWidth(1);
        frame->setMinimumWidth(frameWidth);
        DbController dbcontroller;

        int quantità=dbcontroller.howmanybyUser(*cit, utente->getUser());
        sommatotale=sommatotale+((*cit)->getPrice()*quantità);
        ScrollWidget* q = new ScrollWidget(oggetti, *cit, false, utente, true, true, nullptr, this);

        QVBoxLayout* frameLayout = new QVBoxLayout(frame);
        frameLayout->addWidget(q);

        scrollLayout->addWidget(frame);
    }
    return sommatotale;
}


void Carrello::on_buttonIndietro_clicked()
{
    this->hide();
    home->show();
    home->raise();

}

void Carrello::apriCarrello() {
    this->close();
    Carrello* carrello=new Carrello(home, utente);
    carrello->show();
}

void Carrello::pagamento()
{
    QMessageBox::information(this, "Pagamento", "Purtroppo non siamo in grado di raccogliere soldi.\nTuttavia se ne avessimo la possibilità li useremmo per una meritata vacanza. Grazie  mille per essere arrivati fin qui.\nSabrina e Anna");
    return;
}
