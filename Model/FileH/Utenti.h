//
// Created by canai on 14/08/2023.
//

#ifndef UTENTI_H
#define UTENTI_H

#include <iostream>

using namespace std;

class Utenti {
    private:
        string user;
        string password;
        bool isAdmin;

    public:
        Utenti();
        Utenti(string user, string password, bool isAdmin=false);

        string getUser() const;
        void setUser(string s);

        string getPassword() const;
        void setPassword(string p);

        bool getIsAdmin() const;
        void setAdmin();
        void setNotAdmin();

        ~Utenti();

};


#endif //PROGETTO_UTENTI_H
