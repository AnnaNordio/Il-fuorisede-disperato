#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <cstdio>
#include <string>
#include <stdio.h>
#include <ostream>
#include <iostream>
#include <fstream>
#include <vector>
#include "../Model/FileH/Item.h"
#include "../Model/FileH/Trasporto.h"
#include "../Model/FileH/Libri.h"
#include "../Model/FileH/Casa.h"
#include "../Model/FileH/Cibo.h"
#include "../Model/FileH/Vestiti.h"

#include "../Model/FileH/DoubleList.h"


class Database {
public:
    Database();
    bool connect();
    void disconnect();
    bool userExists(const std::string& username, const std::string& password);
    bool usernameExists(const std::string& username);
    bool addUser(const std::string& username, const std::string& password);
    bool isAdmin(const std::string& username, const std::string& password);
    bool modifyUser(const std::string& newUsername, const std::string& newPassword, const std::string& oldUsername, const std::string& oldPassword);
    DoubleList<Item*> retrieveItems(const std::string& itemType);

    //recupera gli oggetti
    bool retrieveVestitiDetails(int id, std::string& genereVestiti, std::string& tagliaVestiti, std::string& coloreVestiti);
    bool retrieveCasaDetails(int id, std::string& coloreCasa, std::string& genereCasa);
    bool retrieveCiboDetails(int id, std::string& genereCibo);
    bool retrieveLibriDetails(int id, std::string& autoreLibro, std::string& genereLibro, std::string& isbnLibro);
    bool retrieveTrasportiDetails(int id, std::string& durataTrasporto);

    //aggiunge al database
    bool addVestiti(const std::string& nome, const std::string& descrizione, const double& prezzo, const std::string& genere,const std::string& taglia, const std::string& colore);
    bool addLibri(const std::string& nome, const std::string& descrizione, const double& prezzo, const std::string& genere,const std::string& autore, const std::string& isbn);
    bool addTrasporti(const std::string& nome, const std::string& descrizione, const double& prezzo, const std::string& durata);
    bool addCibo(const std::string& nome, const std::string& descrizione, const double& prezzo, const std::string& genere);
    bool addCasa(const std::string& nome, const std::string& descrizione, const double& prezzo, const std::string& genere, const std::string& colore);

    bool deleteFromDatabase(int id);
    bool removeItem(int id);
    bool modifyItem(Item* oggetto, const std::string tipo);

    DoubleList<Item*> retrieveItemsFromCart(const std::string& itemType, const std::string& user);
    int quantiOggettiUser(Item* oggetto, const std::string user);
    int quantiOggetti(Item* oggetto);
    bool aggiungiCarrelloDb(Item* oggetto, const std::string user, int quantità);
    bool removeFromCart (int id, const std::string user, int quantità);
    void deleteFromCart (Item* oggetto, const std::string user);

private:
    QSqlDatabase db;
    int rc;
};

#endif // DATABASE_H
