#include <iostream>
#include "../FileH/Cibo.h"
using namespace std;
    Cibo::Cibo(){}
    Cibo:: Cibo(string n, string d, double p, string g, int id, int quantità):Item(n,d,p, id, quantità), genere(g){}

    string Cibo::getGenere()const{return genere;}
    void Cibo::setGenere(string g){genere=g;}

void Cibo::toString(ostream& os) const{
    Item::toString(os);
    os << "Genere: " << genere << endl;

}
void Cibo::accept(VisitorItemInterface& visitor){
    visitor.visitCibo(*this);
}
Cibo:: ~Cibo(){delete this;}



