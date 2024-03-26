#include <iostream>
#include "../FileH/Trasporto.h"
using namespace std;

    Trasporto::Trasporto(){}
    Trasporto:: Trasporto(string n, string d, double p, string du, int id, int quantità):Item(n,d,p,id,quantità), durata(du){}

    string Trasporto:: getDurata()const {return durata;}
    void Trasporto::setDurata(string du){durata=du;}

void Trasporto::toString(ostream& os) const{
    Item::toString(os);
    os << "Durata: " << durata << endl;
}

void Trasporto::accept(VisitorItemInterface& visitor){
    visitor.visitTrasporto(*this);
}
Trasporto:: ~Trasporto(){delete this;}



