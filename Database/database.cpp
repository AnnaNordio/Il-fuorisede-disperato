#include "database.h"
#include<string>
#include <QDebug>
#include <QtSql>

const QString nomedb="/home/anna/Scrivania/uni/ifd/Il_fuorisede_disperato/Database/DatabasePAO.db";

 Database::Database() {
        // Inizializza il driver del database (ad esempio, SQLite)
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(nomedb);
    }

 bool Database::connect() {
        if (!db.open()) {
            qDebug() << "Errore nell'apertura del database:" << db.lastError().text();
            return false;
        } else {
            return true;
        }
    }

void Database::disconnect() {
    db.close();
    db.QSqlDatabase::removeDatabase("QSQLITE");
}

bool Database::userExists(const std::string& username, const std::string& password) {
        QSqlQuery query;
        query.prepare("SELECT * FROM Utenti WHERE User = :username AND Password = :password");
        query.bindValue(":username", QString::fromStdString(username));
        query.bindValue(":password", QString::fromStdString(password));

        if (!query.exec()) {
            qDebug() << "Errore nella query:" << query.lastError().text();
            return false;
        }

        return query.next();
}

bool Database::usernameExists(const std::string& username)
{
        QSqlQuery query;
        query.prepare("SELECT * FROM Utenti WHERE User = :username");
        query.bindValue(":username", QString::fromStdString(username));

        if (!query.exec()) {
            qDebug() << "Errore nella query:" << query.lastError().text();
            return false;
        }

        return query.next();
}


bool Database::addUser(const std::string& username, const std::string& password) {
        QSqlQuery query;
        query.prepare("INSERT INTO Utenti (User, Password) VALUES (:username, :password)");
        query.bindValue(":username", QString::fromStdString(username));
        query.bindValue(":password", QString::fromStdString( password));

        if (!query.exec()) {
            qDebug() << "Errore nell'inserimento dell'utente:" << query.lastError().text();
            return false;
        }

        return true;
}

////////////////////////////////

bool Database::isAdmin(const std::string& username, const std::string& password) {
    QSqlQuery query;
    query.prepare("SELECT isAdmin FROM Utenti WHERE User = :username AND Password = :password");
    query.bindValue(":username", QString::fromStdString( username));
    query.bindValue(":password", QString::fromStdString(password));

    if (!query.exec()) {
        qDebug() << "Errore nella query:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        int isAdminValue = query.value(0).toInt();
        return (isAdminValue == 1);
    }

    return false;
}

bool Database::modifyUser(const std::string& newUsername, const std::string& newPassword, const std::string& oldUsername, const std::string& oldPassword)
{
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM Utenti WHERE User = :newUsername");
    checkQuery.bindValue(":newUsername", QString::fromStdString(newUsername));

    if (!checkQuery.exec() || !checkQuery.next()) {
        qDebug() << "Errore nella query di verifica dell'username:" << checkQuery.lastError().text();
        return false;
    }

    int usernameCount = checkQuery.value(0).toInt();

    QSqlQuery existingUserQuery;
    existingUserQuery.prepare("SELECT COUNT(*) FROM Utenti WHERE User = :oldUsername AND Password = :oldPassword");
    existingUserQuery.bindValue(":oldUsername", QString::fromStdString(oldUsername));
    existingUserQuery.bindValue(":oldPassword", QString::fromStdString(oldPassword));

    if (!existingUserQuery.exec() || !existingUserQuery.next()) {
        qDebug() << "Errore nella query di verifica dell'utente esistente:" << existingUserQuery.lastError().text();
        return false;
    }

    int existingUserCount = existingUserQuery.value(0).toInt();

    if (existingUserCount == 0) {
        qDebug() << "L'utente con username '" << QString::fromStdString(oldUsername) << "' e password fornita non esiste nel database. Impossibile aggiornare.";
        return false;
    }

    if (usernameCount > 0 && newUsername != oldUsername) {
        qDebug() << "L'username '" << QString::fromStdString(newUsername) << "' è già presente nel database. Impossibile aggiornare l'utente.";
        return false;
    }

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE Utenti SET User = :newUsername, Password = :newPassword WHERE User = :oldUsername");
    updateQuery.bindValue(":newUsername", QString::fromStdString(newUsername));
    updateQuery.bindValue(":newPassword", QString::fromStdString(newPassword));
    updateQuery.bindValue(":oldUsername", QString::fromStdString(oldUsername));

    if (!updateQuery.exec()) {
        qDebug() << "Errore nell'esecuzione della query di aggiornamento:" << updateQuery.lastError().text();
        return false;
    }

    QSqlQuery updateCartQuery;
    updateCartQuery.prepare("UPDATE Carrello SET Utente = :newUsername WHERE Utente = :oldUsername");
    updateCartQuery.bindValue(":newUsername", QString::fromStdString(newUsername));
    updateCartQuery.bindValue(":oldUsername", QString::fromStdString(oldUsername));

    if (!updateCartQuery.exec()) {
        qDebug() << "Errore nell'esecuzione della query di aggiornamento del carrello:" << updateCartQuery.lastError().text();
        return false;
    }

    qDebug() << "Utente aggiornato con successo.";
    return true;
}


bool Database::retrieveVestitiDetails(int id, std::string& genereVestiti, std::string& tagliaVestiti, std::string& coloreVestiti) {
    QSqlQuery query;
    query.prepare("SELECT Genere, Taglia, Colore FROM Vestiti WHERE ID = :id LIMIT 1");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Errore nella query:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        genereVestiti = query.value(0).toString().toStdString();
        tagliaVestiti = query.value(1).toString().toStdString();
        coloreVestiti = query.value(2).toString().toStdString();
        return true;
    }

    return false;
}

bool Database::retrieveCasaDetails(int id, std::string& coloreCasa, std::string& genereCasa)
{
    QSqlQuery query;
    query.prepare("SELECT Colore, Genere FROM Casa WHERE ID = :id LIMIT 1");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Errore nella query:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        coloreCasa = query.value(0).toString().toStdString();
        genereCasa = query.value(1).toString().toStdString();
        return true;
    }

    return false;
}

bool Database::retrieveCiboDetails(int id, std::string& genereCibo)
{
    QSqlQuery query;
    query.prepare("SELECT Genere FROM Cibo WHERE ID = :id LIMIT 1");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Errore nella query:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        genereCibo = query.value(0).toString().toStdString();
        return true;
    }

    return false;
}

bool Database::retrieveLibriDetails(int id, std::string& autoreLibro, std::string& genereLibro, std::string& isbnLibro)
{
    QSqlQuery query;
    query.prepare("SELECT Autore, Genere, ISBN FROM Libri WHERE ID = :id LIMIT 1");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Errore nella query:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        autoreLibro = query.value(0).toString().toStdString();
        genereLibro = query.value(1).toString().toStdString();
        isbnLibro = query.value(2).toString().toStdString();
        return true;
    }

    return false;
}

bool Database::retrieveTrasportiDetails(int id, std::string& durataTrasporto)
{
    QSqlQuery query;
    query.prepare("SELECT Durata FROM Trasporti WHERE ID = :id LIMIT 1");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Errore nella query:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        durataTrasporto = query.value(0).toString().toStdString();
        return true;
    }

    return false;
}
///////////////////////////////////////////////
DoubleList<Item*> Database::retrieveItems(const std::string& itemType) {
    DoubleList<Item*> itemList;
    //connect();
    if (!db.isValid()) {
        std::cerr << "Errore nell'apertura del database: " << db.lastError().text().toStdString() << std::endl;
        return itemList;
    }

    QSqlQuery query(db);
    query.prepare("SELECT * FROM Items");

    if (!query.exec()) {
        std::cerr << "Errore nell'esecuzione della query: " << query.lastError().text().toStdString() << std::endl;
        return itemList;
    }

    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString desc = query.value(2).toString();
        double price = query.value(3).toDouble();
        int quantity = query.value(4).toInt();

        std::string nameStr = name.toStdString();
        std::string descStr = desc.toStdString();

        std::string genereVestiti, tagliaVestiti,coloreVestiti,coloreCasa,genereCasa, genereCibo,autoreLibro,isbnLibro,genereLibro ,durataTrasporto;

        if (retrieveVestitiDetails(id, genereVestiti, tagliaVestiti, coloreVestiti) && (itemType == "Vestiti" || itemType == "Item")) {

            Item* item = new Vestiti(nameStr, descStr, price, genereVestiti, tagliaVestiti, coloreVestiti, id, quantity);
            itemList.insertBack(item);
        }
        else if (retrieveCasaDetails(id, coloreCasa, genereCasa) && (itemType == "Casa" || itemType == "Item")) {

            Item* item = new Casa(nameStr, descStr, price, coloreCasa, genereCasa, id, quantity);
            itemList.insertBack(item);
        }
        else if (retrieveCiboDetails(id, genereCibo) && (itemType == "Cibo" || itemType == "Item")) {

            Item* item = new Cibo(nameStr, descStr, price, genereCibo, id, quantity);
            itemList.insertBack(item);
        }
        else if (retrieveLibriDetails(id, autoreLibro, genereLibro, isbnLibro) && (itemType == "Libri" || itemType == "Item")) {

            Item* item = new Libri(nameStr, descStr, price, isbnLibro, autoreLibro, genereLibro, id, quantity);
            itemList.insertBack(item);
        }
        else if (retrieveTrasportiDetails(id, durataTrasporto) && (itemType == "Trasporto" || itemType == "Item")) {

            Item* item = new Trasporto(nameStr, descStr, price, durataTrasporto, id, quantity);
            itemList.insertBack(item);
        }
    }

    return itemList;
}

/////////////////////////////////
bool Database::addVestiti(const std::string& nome, const std::string& descrizione,const double& prezzo, const std::string& genere, const std::string& taglia, const std::string& colore) {
   //connect();

    QSqlQuery query;
    query.prepare("INSERT INTO Items (Nome, Descrizione, Prezzo, QuantitàMagazzino) VALUES (?, ?, ?, ?)");
    query.addBindValue(QString::fromStdString(nome));
    query.addBindValue(QString::fromStdString(descrizione));
    query.addBindValue(prezzo);
    query.addBindValue(rand() % 100 + 1);

    if (!query.exec()) {
        qDebug() << "Errore nell'inserimento dei dati nella tabella 'items':" << query.lastError().text();
        //db.close();
        return false;
    }

    int lastItemId = query.lastInsertId().toInt();

    query.prepare("INSERT INTO Vestiti (ID, Genere, Taglia, Colore) VALUES (?, ?, ?, ?)");
    query.addBindValue(lastItemId);
    query.addBindValue(QString::fromStdString(genere));
    query.addBindValue(QString::fromStdString(taglia));
    query.addBindValue(QString::fromStdString(colore));

    if (!query.exec()) {
        qDebug() << "Errore nell'inserimento dei dati nella tabella 'vestiti':" << query.lastError().text();
        //db.close();
        return false;
    }

    //db.close();
    return true;
}

bool Database::addLibri(const std::string& nome, const std::string& descrizione,const double& prezzo, const std::string& genere, const std::string& autore, const std::string& isbn) {
  // connect();

    QSqlQuery query;
    query.prepare("INSERT INTO Items (Nome, Descrizione, Prezzo, QuantitàMagazzino) VALUES (?, ?, ?, ?)");
    query.addBindValue(QString::fromStdString(nome));
    query.addBindValue(QString::fromStdString(descrizione));
    query.addBindValue(prezzo);
    query.addBindValue(rand() % 100 + 1);

    if (!query.exec()) {
        qDebug() << "Errore nell'inserimento dei dati nella tabella 'items':" << query.lastError().text();
        //db.close();
        return false;
    }

    int lastItemId = query.lastInsertId().toInt();

    query.prepare("INSERT INTO Libri (ID, Autore, ISBN, Genere) VALUES (?, ?, ?, ?)");
    query.addBindValue(lastItemId);
    query.addBindValue(QString::fromStdString(autore));
    query.addBindValue(QString::fromStdString(isbn));
    query.addBindValue(QString::fromStdString(genere));

    if (!query.exec()) {
        qDebug() << "Errore nell'inserimento dei dati nella tabella 'libri':" << query.lastError().text();
       // db.close();
        return false;
    }

   // db.close();
    return true;
}

bool Database::addTrasporti(const std::string& nome, const std::string& descrizione, const double& prezzo, const std::string& durata) {

   // connect();

    QSqlQuery query;
    query.prepare("INSERT INTO Items (Nome, Descrizione, Prezzo, QuantitàMagazzino) VALUES (?, ?, ?, ?)");
    query.addBindValue(QString::fromStdString(nome));
    query.addBindValue(QString::fromStdString(descrizione));
    query.addBindValue(prezzo);
    query.addBindValue(rand() % 100 + 1);

    if (!query.exec()) {
        qDebug() << "Errore nell'inserimento dei dati nella tabella 'items':" << query.lastError().text();
        //db.close();
        return false;
    }

    int lastItemId = query.lastInsertId().toInt();

    query.prepare("INSERT INTO Trasporti (ID, Durata) VALUES (?, ?)");
    query.addBindValue(lastItemId);
    query.addBindValue(QString::fromStdString(durata));

    if (!query.exec()) {
        qDebug() << "Errore nell'inserimento dei dati nella tabella 'trasporti':" << query.lastError().text();
        //db.close();
        return false;
    }

   // db.close();
    return true;
}
///////////////////////////////////////

bool Database::addCibo(const std::string& nome, const std::string& descrizione,const double& prezzo, const std::string& genere) {
    //connect();

    QSqlQuery query;
    query.prepare("INSERT INTO Items (Nome, Descrizione, Prezzo, QuantitàMagazzino) VALUES (?, ?, ?, ?)");
    query.addBindValue(QString::fromStdString(nome));
    query.addBindValue(QString::fromStdString(descrizione));
    query.addBindValue(prezzo);
    query.addBindValue(rand() % 100 + 1);

    if (!query.exec()) {
        qDebug() << "Errore nell'inserimento dei dati nella tabella 'items':" << query.lastError().text();
        //db.close();
        return false;
    }

    int lastItemId = query.lastInsertId().toInt();

    query.prepare("INSERT INTO Cibo (ID, Genere) VALUES (?, ?)");
    query.addBindValue(lastItemId);
    query.addBindValue(QString::fromStdString(genere));

    if (!query.exec()) {
        qDebug() << "Errore nell'inserimento dei dati nella tabella 'cibo':" << query.lastError().text();
        //db.close();
        return false;
    }

   // db.close();
    return true;
}

bool Database::addCasa(const std::string& nome, const std::string& descrizione, const double& prezzo, const std::string& genere, const std::string& colore) {
    //connect();

    QSqlQuery query;
    query.prepare("INSERT INTO Items (Nome, Descrizione, Prezzo, QuantitàMagazzino) VALUES (?, ?, ?, ?)");
    query.addBindValue(QString::fromStdString(nome));
    query.addBindValue(QString::fromStdString(descrizione));
    query.addBindValue(prezzo);
    query.addBindValue(rand() % 100 + 1);

    if (!query.exec()) {
        qDebug() << "Errore nell'inserimento dei dati nella tabella 'items':" << query.lastError().text();
        //db.close();
        return false;
    }

    int lastItemId = query.lastInsertId().toInt();

    query.prepare("INSERT INTO Casa (ID, Genere, Colore) VALUES (?, ?, ?)");
    query.addBindValue(lastItemId);
    query.addBindValue(QString::fromStdString(genere));
    query.addBindValue(QString::fromStdString(colore));

    if (!query.exec()) {
        qDebug() << "Errore nell'inserimento dei dati nella tabella 'casa':" << query.lastError().text();
        //db.close();
        return false;
    }

   // db.close();
    return true;
}
/////////////////////////////////////////////////

bool Database::deleteFromDatabase(int id) {
    //connect();

    QSqlQuery query;
    bool item = false;

    // Controlla se l'ID è presente nella tabella 'vestiti'
    query.prepare("SELECT ID FROM Vestiti WHERE ID = ?");
    query.addBindValue(id);
    if (!query.exec()) {
        qDebug() << "Errore nella preparazione della query per la tabella 'vestiti':" << query.lastError().text();
        //db.close();
        return false;
    }

    if (query.next()) {
        // L'ID è presente nella tabella 'vestiti', quindi eliminiamo la riga
        query.prepare("DELETE FROM Vestiti WHERE ID = ?");
        query.addBindValue(id);
        if (!query.exec()) {
            qDebug() << "Errore nell'eliminazione dalla tabella 'vestiti':" << query.lastError().text();
            //db.close();
            return false;
        }
        item = this->removeItem(id);
        if (!item) {
           // db.close();
            return false;
        }
    }

    query.prepare("SELECT ID FROM Trasporti WHERE ID = ?");
    query.addBindValue(id);
    if (!query.exec()) {
        qDebug() << "Errore nella preparazione della query per la tabella 'vestiti':" << query.lastError().text();
        //db.close();
        return false;
    }

    if (query.next()) {
        // L'ID è presente nella tabella 'trasporti', quindi eliminiamo la riga
        query.prepare("DELETE FROM Trasporti WHERE ID = ?");
        query.addBindValue(id);
        if (!query.exec()) {
            qDebug() << "Errore nell'eliminazione dalla tabella 'trasporti':" << query.lastError().text();
           // db.close();
            return false;
        }
        item = this->removeItem(id);
        if (!item) {
           // db.close();
            return false;
        }
    }

    query.prepare("SELECT ID FROM Cibo WHERE ID = ?");
    query.addBindValue(id);
    if (!query.exec()) {
        qDebug() << "Errore nella preparazione della query per la tabella 'cibo':" << query.lastError().text();
        //db.close();
        return false;
    }

    if (query.next()) {
        // L'ID è presente nella tabella 'cibo', quindi eliminiamo la riga
        query.prepare("DELETE FROM Cibo WHERE ID = ?");
        query.addBindValue(id);
        if (!query.exec()) {
            qDebug() << "Errore nell'eliminazione dalla tabella 'vestiti':" << query.lastError().text();
            //db.close();
            return false;
        }
        item = this->removeItem(id);
        if (!item) {
           // db.close();
            return false;
        }
    }
    query.prepare("SELECT ID FROM Casa WHERE ID = ?");
    query.addBindValue(id);
    if (!query.exec()) {
        qDebug() << "Errore nella preparazione della query per la tabella 'casa':" << query.lastError().text();
        //db.close();
        return false;
    }

    if (query.next()) {
        // L'ID è presente nella tabella 'casa', quindi eliminiamo la riga
        query.prepare("DELETE FROM Casa WHERE ID = ?");
        query.addBindValue(id);
        if (!query.exec()) {
            qDebug() << "Errore nell'eliminazione dalla tabella 'vestiti':" << query.lastError().text();
           // db.close();
            return false;
        }
        item = this->removeItem(id);
        if (!item) {
            //db.close();
            return false;
        }
    }
    query.prepare("SELECT ID FROM Libri WHERE ID = ?");
    query.addBindValue(id);
    if (!query.exec()) {
        qDebug() << "Errore nella preparazione della query per la tabella 'libri':" << query.lastError().text();
        //db.close();
        return false;
    }

    if (query.next()) {
        // L'ID è presente nella tabella 'libri', quindi eliminiamo la riga
        query.prepare("DELETE FROM Libri WHERE ID = ?");
        query.addBindValue(id);
        if (!query.exec()) {
            qDebug() << "Errore nell'eliminazione dalla tabella 'vestiti':" << query.lastError().text();
           // db.close();
            return false;
        }
        item = this->removeItem(id);
        if (!item) {
           // db.close();
            return false;
        }
    }


    //db.close();
    return true;
}

bool Database::modifyItem(Item* oggetto, const std::string tipo) {
   // connect();

    QSqlQuery query;
    QString nome = QString::fromStdString(oggetto->getName());
    QString descrizione =QString::fromStdString( oggetto->getDesc());
    double prezzo = oggetto->getPrice();
    int id = oggetto->getID();

    // Aggiorna l'oggetto nella tabella principale
    query.prepare("UPDATE Items SET Nome = ?, Descrizione = ?, Prezzo = ? WHERE ID = ?");
    query.addBindValue(nome);
    query.addBindValue(descrizione);
    query.addBindValue(prezzo);
    query.addBindValue(id);

    if (!query.exec()) {
        qDebug() << "Errore nell'aggiornamento dei dati nella tabella 'Items':" << query.lastError().text();
       // db.close();
        return false;
    }

    // Se il tipo è "Trasporti", aggiorna la durata nella tabella "trasporti"
    if (tipo == "Trasporti") {
        Trasporto* t = dynamic_cast<Trasporto*>(oggetto);
        QString durata = QString::fromStdString(t->getDurata());

        query.prepare("UPDATE Trasporti SET Durata = ? WHERE ID = ?");
        query.addBindValue(durata);
        query.addBindValue(id);

        if (!query.exec()) {
            qDebug() << "Errore nell'aggiornamento della durata nella tabella 'trasporti':" << query.lastError().text();
            //db.close();
            return false;
        }
    }
    // Se il tipo è "Vestiti", aggiorna la durata nella tabella "trasporti"
    if (tipo == "Vestiti") {
        Vestiti* v = dynamic_cast<Vestiti*>(oggetto);
        QString genere = QString::fromStdString(v->getGenere());
        QString taglia = QString::fromStdString(v->getTaglia());
        QString colore = QString::fromStdString(v->getColore());


        query.prepare("UPDATE Vestiti SET Genere = ? , Taglia= ? , Colore= ? WHERE ID = ?");
        query.addBindValue(genere);
        query.addBindValue(taglia);
        query.addBindValue(colore);
        query.addBindValue(id);

        if (!query.exec()) {
            qDebug() << "Errore nell'aggiornamento della durata nella tabella 'trasporti':" << query.lastError().text();
            //db.close();
            return false;
        }
    }
    // Se il tipo è "Libri", aggiorna la durata nella tabella "trasporti"
    if (tipo == "Libri") {
        Libri* l = dynamic_cast<Libri*>(oggetto);
        QString autore = QString::fromStdString(l->getAutore());
        QString isbn = QString::fromStdString(l->getIsbn());
        QString genere = QString::fromStdString(l->getGenere());

        query.prepare("UPDATE Libri SET Autore = ? , ISBN=?, Genere=? WHERE ID = ?");
        query.addBindValue(autore);
        query.addBindValue(isbn);
        query.addBindValue(genere);
        query.addBindValue(id);

        if (!query.exec()) {
            qDebug() << "Errore nell'aggiornamento della durata nella tabella 'trasporti':" << query.lastError().text();
            //db.close();
            return false;
        }
    }
    // Se il tipo è "Trasporti", aggiorna la durata nella tabella "trasporti"
    if (tipo == "Cibo") {
        Cibo* c = dynamic_cast<Cibo*>(oggetto);
        QString genere = QString::fromStdString(c->getGenere());

        query.prepare("UPDATE Cibo SET Genere = ? WHERE ID = ?");
        query.addBindValue(genere);
        query.addBindValue(id);

        if (!query.exec()) {
            qDebug() << "Errore nell'aggiornamento della durata nella tabella 'trasporti':" << query.lastError().text();
            //db.close();
            return false;
        }
    }
    // Se il tipo è "Casa", aggiorna la durata nella tabella "trasporti"
    if (tipo == "Casa") {
        Casa* c = dynamic_cast<Casa*>(oggetto);
        QString genere = QString::fromStdString(c->getGenere());
        QString colore = QString::fromStdString(c->getColore());

        query.prepare("UPDATE Casa SET Genere = ? Colore=? WHERE ID = ?");
        query.addBindValue(genere);
        query.addBindValue(colore);
        query.addBindValue(id);

        if (!query.exec()) {
            qDebug() << "Errore nell'aggiornamento della durata nella tabella 'trasporti':" << query.lastError().text();
            //db.close();
            return false;
        }
    }
   // db.close();
    return true;
}
///////////////////////////////////////////////////////////////////

DoubleList<Item*> Database::retrieveItemsFromCart(const std::string& itemType, const std::string& user) {
    DoubleList<Item*> itemList;

    //connect();
    if(!db.isValid()){
        std::cerr<<"Errore nell'apertura del database: "<<db.lastError().text().toStdString();
        return itemList;
    }

    QSqlQuery query(db);
    query.prepare("SELECT * FROM Items WHERE ID IN (SELECT ID FROM Carrello WHERE Utente = ?)");
    query.addBindValue(QString::fromStdString(user));

    if (!query.exec()) {
        qDebug() << "Errore nell'esecuzione della query:" << query.lastError().text();
        //db.close();
        return itemList;
    }


    while (query.next()) {
        int id = query.value(0).toInt();
        std::string name = query.value(1).toString().toStdString();
        std::string desc = query.value(2).toString().toStdString();
        double price = query.value(3).toDouble();
        int quantity = query.value(4).toInt();


        if (itemType == "Casa" || itemType == "Item") {
            std::string coloreCasa, genereCasa;
            if (retrieveCasaDetails(id, coloreCasa, genereCasa)) {
               Item* item = new Casa(name, desc, price, coloreCasa, genereCasa, id, quantity);
               itemList.insertBack(item);
            }
        }
        if (itemType == "Cibo" || itemType == "Item") {
            std::string genereCibo;
            if (retrieveCiboDetails(id, genereCibo)) {
               Item* item = new Cibo(name, desc, price, genereCibo, id, quantity);
               itemList.insertBack(item);
            }
        }
        if (itemType == "Vestiti" || itemType == "Item") {
            std::string genereVestiti, tagliaVestiti, coloreVestiti;
            if (retrieveVestitiDetails(id, genereVestiti, tagliaVestiti, coloreVestiti)) {
                Item* item = new Vestiti(name, desc, price, genereVestiti, tagliaVestiti, coloreVestiti, id, quantity);
                itemList.insertBack(item);
            }
        }
        if (itemType == "Libri" || itemType == "Item") {
            std::string autoreLibro, isbnLibro, genereLibro;
            if (retrieveLibriDetails(id, autoreLibro, genereLibro, isbnLibro)) {
               Item* item = new Libri(name, desc, price, isbnLibro, autoreLibro, genereLibro, id, quantity);
               itemList.insertBack(item);
            }
        }
        if (itemType == "Trasporto" || itemType == "Item") {
            std::string durataTrasporto;
            if (retrieveTrasportiDetails(id, durataTrasporto)) {
               Item* item = new Trasporto(name, desc, price, durataTrasporto, id, quantity);
               itemList.insertBack(item);
            }
        }

    }

   // db.close();
    return itemList;
}

bool Database::removeItem(int id) {
   //connect();

    QSqlQuery cartQuery(db);
    cartQuery.prepare("DELETE FROM Carrello WHERE ID = ?");
    cartQuery.addBindValue(id);

    if (!cartQuery.exec()) {
        qDebug() << "Errore nell'esecuzione della query per rimuovere dal carrello:" << cartQuery.lastError().text();
       // db.close();
        return false;
    }

    QSqlQuery itemQuery(db);
    itemQuery.prepare("DELETE FROM Items WHERE ID = ?");
    itemQuery.addBindValue(id);

    if (!itemQuery.exec()) {
        qDebug() << "Errore nell'esecuzione della query per rimuovere dagli item:" << itemQuery.lastError().text();
        //db.close();
        return false;
    }

    //db.close();
    return true;
}

int Database::quantiOggetti(Item* oggetto) {
    int id = oggetto->getID();
    int q = -1;

   // connect();

    QSqlQuery query(db);
    query.prepare("SELECT Quantità FROM Carrello WHERE ID = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        qDebug() << "Errore nell'esecuzione della query:" << query.lastError().text();
        //db.close();
        return -1;
    }

    if (query.next()) {
        q = query.value(0).toInt();
    }

   // db.close();
    return q;
}

////////////////////////////////

bool Database::aggiungiCarrelloDb(Item* oggetto, const std::string user, int quantità) {

    int id = oggetto->getID();

   // connect();

    QSqlQuery query(db);
    query.prepare("SELECT Quantità FROM Carrello WHERE ID = ? AND Utente = ?");
    query.addBindValue(id);
    query.addBindValue(QString::fromStdString(user));

    if (!query.exec()) {
        qDebug() << "Errore nell'esecuzione della query SELECT:" << query.lastError().text();
        //db.close();
        return false;
    }

    if (query.next()) {
        // La riga esiste, effettua l'aggiornamento della quantità
        int quantitaCorrente = query.value(0).toInt();
        int q = quantitaCorrente + quantità;
        query.prepare("UPDATE Carrello SET Quantità = ? WHERE ID = ? AND Utente = ?");
        query.addBindValue(q);
        query.addBindValue(id);
        query.addBindValue(QString::fromStdString(user));

        if (!query.exec()) {
            qDebug() << "Errore nell'esecuzione della query UPDATE:" << query.lastError().text();
            //db.close();
            return false;
        }

        //db.close();
        return true; // Quantità aggiornata con successo
    } else {
        // La riga non esiste, inserisci una nuova riga nel carrello
        query.prepare("INSERT INTO Carrello (ID, Utente, Quantità) VALUES (?, ?, ?)");
        query.addBindValue(id);
        query.addBindValue(QString::fromStdString(user));
        query.addBindValue(quantità);

        if (!query.exec()) {
            qDebug() << "Errore nell'inserimento della riga nel carrello:" << query.lastError().text();
            //db.close();
            return false;
        }

        //db.close();
        return true; // Riga inserita con successo nel carrello
    }
}

bool Database::removeFromCart(int id, const std::string user, int quantità) {
    connect();

    QSqlQuery query(db);
    query.prepare("UPDATE Carrello SET Quantità = Quantità - ? WHERE ID = ? AND Utente = ?");
    query.addBindValue(quantità);
    query.addBindValue(id);
    query.addBindValue(QString::fromStdString(user));

    if (!query.exec()) {
        qDebug() << "Errore nell'esecuzione della query UPDATE:" << query.lastError().text();
        //db.close();
        return false;
    }

    int rowsAffected = query.numRowsAffected();

    if (rowsAffected > 0) {
       // db.close();
        return true; // L'aggiornamento è avvenuto con successo
    } else {
        qDebug() << "Nessuna riga corrispondente trovata per l'aggiornamento.";
        //db.close();
        return false;
    }
}

void Database::deleteFromCart(Item* oggetto, const std::string user) {
    int id = oggetto->getID();
//connect();

    QSqlQuery query(db);
    query.prepare("DELETE FROM Carrello WHERE ID = ? AND Utente = ?");
    query.addBindValue(id);
    query.addBindValue(QString::fromStdString(user));

    if (!query.exec()) {
        qDebug() << "Errore nell'esecuzione della query DELETE:" << query.lastError().text();
        //db.close();
        return;
    }

    qDebug() << "Riga eliminata con successo dal carrello.";
    //db.close();
}
int Database::quantiOggettiUser(Item* oggetto, const std::string user)
{
    int id = oggetto->getID();
    int q = -1;

    // connect();

    QSqlQuery query(db);
    query.prepare("SELECT Quantità FROM Carrello WHERE ID = ? and Utente=?");
        query.addBindValue(id);
    query.addBindValue(QString::fromStdString(user));

    if (!query.exec()) {
        qDebug() << "Errore nell'esecuzione della query:" << query.lastError().text();
        //db.close();
        return -1;
    }

    if (query.next()) {
        q = query.value(0).toInt();
    }

    // db.close();
    return q;
}
