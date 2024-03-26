#include <iostream>
#include "../FileH/Libri.h"
using namespace std;
    Libri::Libri(){}
    Libri:: Libri(string n, string d, double p, string i, string a, string g, int id, int quantità):Item(n,d,p, id, quantità), isbn(i), autore(a), genere(g){}

    string Libri:: getIsbn()const {return isbn;}
    void Libri::setIsbn(string i){isbn=i;}
    string Libri::getAutore()const{return autore;}
    void Libri::setAutore(string a){autore=a;}

string Libri::getGenere()const{return genere;}
void Libri::setGenere(string g){genere=g;}

void Libri::toString(ostream& os) const{
    Item::toString(os);
    os << "ISBN: " << isbn << endl;
    os << "Autore: " << autore<< endl;
    os << "Genere: " << genere<< endl;
    os << "-----" << endl;

}

void Libri::accept(VisitorItemInterface& visitor){
    visitor.visitLibri(*this);
}

Libri:: ~Libri(){delete this;}
