#include "../FileH/dbcontroller.h"
#include "../../Database/database.h"
#include <QCoreApplication>

DbController::DbController()
{
    db = new Database();
    db->connect();
}

bool DbController::checkLogin(const std::string& username, const std::string& password)
{

        if (db->userExists(username, password)) {
            return 1;
        }
        else
        {
            return 0;
        }

}

bool DbController::checkUtente(const std::string& username)
{

        if (db->usernameExists(username)) {
            return 1;
        }
        else
        {
            return 0;
        }

}

bool DbController::aggiungiUser(const std::string& username, const std::string& password)
{
     if (db->addUser(username, password))
        {
            return 1;
        }
        else
        {
            return 0;
        }

}

bool DbController::checkAdmin(const std::string& username, const std::string& password)
{
        if (db->isAdmin(username, password)) {
            return 1;
        }
        else
        {

            return 0;
        }

}

DoubleList<Item*> DbController::stampa(const std::string& itemType)
{
    DoubleList<Item*> items;

        items=db->retrieveItems(itemType);

        return items;

}


bool DbController::modificaUser(const std::string& insertusername, const std::string& insertpassword, const std::string& username, const std::string& password)
{

        if (db->modifyUser(insertusername, insertpassword, username, password))
        {
            return 1;
        }
        else
        {
            return 0;
        }

}

bool DbController::addToVestiti(const std::string& nome, const std::string& descrizione, const double& prezzo, const std::string& genere,const std::string& taglia, const std::string& colore)
{

        if (db->addVestiti(nome,descrizione,prezzo,genere,taglia,colore))
        {
            return 1;
        }
        else
        {
            return 0;
        }

}

bool DbController::addToLibri(const std::string& nome, const std::string& descrizione, const double& prezzo, const std::string& genere,const std::string& autore, const std::string& isbn)
{

        if (db->addLibri(nome,descrizione,prezzo,genere,autore,isbn))
        {
            return 1;
        }
        else
        {
            return 0;
        }

}

bool DbController::addToTrasporti(const std::string& nome, const std::string& descrizione, const double& prezzo, const std::string& durata)
{

        if (db->addTrasporti(nome,descrizione,prezzo,durata))
        {
            return 1;
        }
        else
        {
            return 0;
        }

}

bool DbController::addToCibo(const std::string& nome, const std::string& descrizione, const double& prezzo, const std::string& genere)
{

        if (db->addCibo(nome,descrizione,prezzo,genere))
        {
            return 1;
        }
        else
        {
            return 0;
        }

}

bool DbController::addToCasa(const std::string& nome, const std::string& descrizione, const double& prezzo, const std::string& genere, const std::string& colore)
{

        if (db->addCasa(nome,descrizione,prezzo,genere,colore))
        {
            return 1;
        }
        else
        {
            return 0;
        }

}


bool DbController::remove(Item* oggetto)
{

        if (db->deleteFromDatabase(oggetto->getID()))
        {
            return 1;
        }
        else
        {
            return 0;
        }

}

bool DbController::modifica (Item* oggetto, const std::string& tipo)
{

        if (db->modifyItem(oggetto, tipo))
        {
            return 1;
        }
        else
        {
            return 0;
        }

}

DoubleList<Item*> DbController::stampaCarrello(const std::string& itemType, std::shared_ptr<Utenti> utente)
{
    DoubleList<Item*> items;

        items=db->retrieveItemsFromCart(itemType, utente->getUser());

        return items;

}


DbController::~DbController()
{
    db->disconnect();
    delete db;
}

int DbController::howmany(Item* oggetto)
{
    double quantitàCarrello;

        quantitàCarrello=db->quantiOggetti(oggetto);

        return quantitàCarrello;

}

bool DbController::aggiungiAlCarrello(Item* oggetto, const std::string user, int quantità)
{

        if (db->aggiungiCarrelloDb(oggetto, user, quantità))
        {
            return 1;
        }
        else
        {
            return 0;
        }

}
bool DbController::rimuoviDalCarrello(Item* oggetto, const std::string user, int quantità)
{

        int id=oggetto->getID();
        if(db->removeFromCart(id, user, quantità))
        {
            return true;
        }
        return false;

}

void DbController::destroy (Item* oggetto, const std::string utente)
{

        db->deleteFromCart(oggetto, utente);



}

int DbController::howmanybyUser(Item* oggetto, const std::string& utente)
{
    double quantitàCarrello;
        quantitàCarrello=db->quantiOggettiUser(oggetto, utente);
        return quantitàCarrello;

}
