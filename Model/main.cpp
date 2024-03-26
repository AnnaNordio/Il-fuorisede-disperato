#include <iostream>
#include "FileH/DoubleList.h"
#include "FileH/Item.h"
#include "FileH/Libri.h"

int main() {

    // Crea oggetti Item e inseriscili nella lista
    Item item1("Prodotto 1", "Descrizione 1", 10.99, 3);
    Item item2("Prodotto 2", "Descrizione 2", 15.99);
    Item item3("Prodotto 3", "Descrizione 3", 18.06);
    Libri l("Libro 1", "Descrizione 1", 16.00, "1234567890", "Noi", "Thriller");
    Item* libro= &l;

    DoubleList<Item*> itemList(&item1);  // Crea una lista per oggetti Item

    //itemList.insertFront(item1);
    itemList.insertBack(&item2);
    itemList.insertFront(&item3);
    itemList.insertBack(libro);


    for (DoubleList<Item*>::const_iterator it = itemList.begin(); it != itemList.end(); ++it) {
        (*it)->toString();
    }

    return 0;
}

