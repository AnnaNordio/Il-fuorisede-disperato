#include "../FileH/home.h"
#include<QString>
#include <QCoreApplication>
#include<QApplication>
#include <string>


Home::Home(std::shared_ptr<Utenti> u, const std::string& itemType, QWidget *parent) :
    QMainWindow(parent), utente(u), itemType(itemType)
{
    QWidget::setWindowTitle ("Il fuorisede disperato");

    QWidget* mainWidget=new QWidget();
    QVBoxLayout* mainLayout=new QVBoxLayout(mainWidget);

    QWidget* menuWidget =new QWidget();
    QHBoxLayout* menuLayout= new QHBoxLayout(menuWidget);

    QWidget* layoutWidget=new QWidget();
    QHBoxLayout* layout= new QHBoxLayout(layoutWidget);

    layout->setAlignment(Qt::AlignLeft);
    scrollLayout=new QVBoxLayout();
    layout->setAlignment(Qt::AlignLeft);
    hamburgermenu= new HamburgerMenu(this, u);
    layout->addWidget(hamburgermenu);

    scrollArea= new QScrollArea();
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setWidgetResizable(true);


    bool admin= u->getIsAdmin();
    this->updateContent(itemType, admin);

    QWidget* scrollContent = new QWidget();
    scrollContent->setLayout(scrollLayout);
    scrollArea->setWidget(scrollContent);
    layout->addWidget(scrollArea);

    QString s = QString::fromStdString("Ciao ") + QString::fromStdString(u->getUser()) + QString::fromStdString("!");
    labelTitle = new QLabel(s);
    menuLayout->addWidget(labelTitle);
    labelTitle->setAlignment(Qt::AlignCenter);
    profile= new Profile(this, u);
    layout->addWidget(profile);

    mainLayout->addWidget(menuWidget);
    mainLayout->addWidget(layoutWidget);

    setCentralWidget(mainWidget);

}

Home::~Home()
{
}

void Home::updateContent(const std::string& itemType, bool admin) {
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

    oggetti = dbcontroller.stampa(itemType);
    // Imposta l'allineamento del scrollLayout
    scrollLayout->setAlignment(Qt::AlignTop);

    for (DoubleList<Item*>::const_iterator cit = oggetti.begin(); cit != oggetti.end(); ++cit) {
        QFrame* frame = new QFrame;
        frame->setFrameShape(QFrame::Box);
        frame->setLineWidth(1);
        frame->setMinimumWidth(frameWidth); // Imposta la larghezza minima dei frame

        ScrollWidget* q = new ScrollWidget(oggetti, *cit, admin, utente);

        connect(q, &ScrollWidget::removeRequested, this, &Home::removeFrame);

        QVBoxLayout* frameLayout = new QVBoxLayout(frame);
        frameLayout->addWidget(q);

        scrollLayout->addWidget(frame);
    }
}

void Home::removeFrame(QFrame* frame) {
    scrollLayout->removeWidget(frame);

    delete frame;
}
