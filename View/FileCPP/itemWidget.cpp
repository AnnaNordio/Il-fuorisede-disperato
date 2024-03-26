#include <QCoreApplication>
#include <QLayout>
#include "../FileH/itemWidget.h"
#include "../FileH/scrollWidget.h"
#include "../FileH/VisitorItem.h"


ItemWidget::ItemWidget(DoubleList<Item*> lista, Item* oggetto,bool admin, QWidget *parent, shared_ptr<Utenti> user) :
    QDialog(parent), item(oggetto), utente(user), lista(lista)
{
    setFixedSize(600, 250);
    QVBoxLayout* layout=new QVBoxLayout(this);

    ScrollWidget* scroll= new ScrollWidget(lista, item, admin, utente, true, false, nullptr, nullptr);

    VisitorItem visitor;

    layout->addWidget(scroll);

    item->accept(visitor);

    layout->addWidget(visitor.getWidget());
}


ItemWidget::~ItemWidget()
{
}


