
#include "../FileH/Utenti.h"

Utenti::Utenti(){}

Utenti:: Utenti(string u, string p, bool a):user(u), password(p), isAdmin(a){}

string Utenti::getUser() const{return user;}
void Utenti::setUser(string s){user=s;}

string Utenti::getPassword()const{return password;}
void Utenti::setPassword(string p){password=p;}

bool Utenti::getIsAdmin()const{return isAdmin;}
void Utenti::setAdmin(){isAdmin=true;}
void Utenti::setNotAdmin(){isAdmin=false;}

Utenti::~Utenti(){}


