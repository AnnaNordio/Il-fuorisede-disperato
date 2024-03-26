#include <iostream>
#include "../FileH/Vestiti.h"
using namespace std;

Vestiti::Vestiti(){}

Vestiti:: Vestiti(string n, string d, double p, string g, string t, string c, int id, int quantità):Item(n,d,p,id, quantità), genere(g), taglia(t), colore(c){}

string Vestiti::getGenere()const{return genere;}
void Vestiti::setGenere(string g){genere=g;}

string Vestiti:: getTaglia()const {return taglia;}
void Vestiti::setTaglia(string t){taglia=t;}

string Vestiti:: getColore()const{return colore;}
void Vestiti::setColore(string c){colore= c;}

void Vestiti::toString(ostream& os) const{
    Item::toString(os);
    os << "Genere: " << genere << endl;
    os << "Taglia: " << taglia<< endl;
    os << "Colore: " << colore<< endl;
    os << "-----" << endl;
}
void Vestiti::accept(VisitorItemInterface& visitor){
    visitor.visitVestiti(*this);
}
Vestiti:: ~Vestiti(){delete this;}


