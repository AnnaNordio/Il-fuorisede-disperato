#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <string>
#include <QMainWindow>
#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QSqlDatabase>
#include <QFileInfo>
#include "../../Model/FileH/Item.h"
#include "../../Model/FileH/DoubleList.h"
#include "../../Model/FileH/Utenti.h"

class Database;
class Login;
class Registrazione;
class Home;

class DbController: public QObject
{

protected:
    Database *db;

public:
    DbController();

    ~DbController();
    bool checkLogin(const std::string& username, const std::string& password);
    bool checkUtente(const std::string& username);
    bool checkAdmin(const std::string& username, const std::string& password);
    bool aggiungiUser(const std::string& username, const std::string& password);
    DoubleList<Item*> stampa(const std::string& itemType);
    bool modificaUser(const std::string& insertusername, const std::string& insertpassword, const std::string& username, const std::string& password);
    bool addToVestiti(const std::string& nome, const std::string& descrizione, const double& prezzo, const std::string& genere,const std::string& taglia, const std::string& colore);
    bool addToLibri(const std::string& nome, const std::string& descrizione, const double& prezzo, const std::string& genere,const std::string& autore, const std::string& isbn);
    bool addToTrasporti(const std::string& nome, const std::string& descrizione, const double& prezzo, const std::string& durata);
    bool addToCibo(const std::string& nome, const std::string& descrizione, const double& prezzo, const std::string& genere);
    bool addToCasa(const std::string& nome, const std::string& descrizione, const double& prezzo, const std::string& genere, const std::string& colore);
    bool modifica (Item* oggetto, const std::string& tipo);
    bool remove(Item* oggetto);
    DoubleList<Item*> stampaCarrello(const std::string& itemType, std::shared_ptr<Utenti> utente);
    int howmany(Item* oggetto);
    bool aggiungiAlCarrello(Item* oggetto, const std::string user, int quantità);
    bool rimuoviDalCarrello(Item* oggetto, const std::string user, int quantità);
    int howmanybyUser(Item* oggetto, const std::string& utente);
    void destroy (Item* oggetto, const std::string utente);
};

#endif // DBCONTROLLER_H

