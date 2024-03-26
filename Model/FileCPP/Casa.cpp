#include <iostream>
#include "../FileH/Casa.h"
using namespace std;

    Casa::Casa(){};
    Casa:: Casa(string n, string d, double p, string c, string g, int id, int quantità):Item(n,d,p, id, quantità), colore(c), genere(g){}

    string Casa:: getColore()const {return colore;}
    void Casa:: setColore(string c){colore=c;}

    string Casa::getGenere()const{return genere;}
    void Casa::setGenere(string g){genere=g;}

void Casa::toString(ostream& os) const{
    Item::toString(os);
    os << "Genere: " << genere << endl;
    os << "Colore: " << colore<< endl;
    os << "-----" << endl;
}
void Casa::accept(VisitorItemInterface& visitor){
    visitor.visitCasa(*this);
}
Casa:: ~Casa(){delete this;}


